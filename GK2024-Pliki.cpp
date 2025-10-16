// funkcje do operacji na plikach
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"


void zapiszPlik6(string nazwaObrazka, int opcja) {
    SDL_Color kolorZbior[8];
    Uint8 kolor6bitZbior[8];
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    Uint8 tryb;
    Uint8 dithering;
    Uint8 ileBitow = 6;
    char identyfikator[] = "22";

    cout<<"Zapisujemy plik " + nazwaObrazka + " uzywajac metody write()"<<endl;
    ofstream wyjscie(nazwaObrazka + ".z22", ios::binary);

    switch (opcja) {
    case 1:
        tryb = 1; // paleta narzucona
        dithering = 0; // brak ditheringu
        break;
    case 2:
        tryb = 1; // paleta narzucona
        dithering = 1; // dithering tablica Bayera 4x4
        break;
    case 3:
        tryb = 2; // narzucona skala szarosci
        dithering = 0; // brak ditheringu
        break;
    case 4:
        tryb = 2; // narzucona skala szarosci
        dithering = 1; // dithering tablica Bayera 4x4
        break;
    case 5:
        tryb = 3; // paleta dedykowana
        dithering = 0; // brak ditheringu
        break;
    case 6:
        tryb = 3; // paleta dedykowana
        dithering = 2; // dithering Floyda-Steinberga
        break;
    case 7:
        tryb = 4; // dedykowana skala szarosci
        dithering = 0; // brak ditheringu
        break;
    case 8:
        tryb = 4; // dedykowana skala szarosci
        dithering = 2; // dithering Floyda-Steinberga
        break;
    case 9:
        tryb = 5; // paleta wykryta
        dithering = 0; // brak ditheringu
        break;
    }

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&tryb, sizeof(Uint8));
    wyjscie.write((char*)&dithering, sizeof(Uint8));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    if (tryb == 1 || tryb == 3) {
        zapiszPalete6(wyjscie, paleta6k, 64);
    }
    else if (tryb == 2 || tryb == 4) {
        zapiszPalete6(wyjscie, paleta6s, 64);
    }
    else if (tryb == 5) {
        zapiszPalete6(wyjscie, paleta6, ileKolorow);
    }

    zapiszObraz6(wyjscie);

    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}

void zapiszObraz6(ofstream& wyjscie) {
    int bity[8];
    Uint8 bajtDoZapisu;

    for (int i=0; i < wysokosc*szerokosc/4-8; i+=8) {
        for (int m=0; m<6; m++){
            for (int j=0; j<8; j++) {
                bity[j] = ((obrazekDoZapisu[i+j] >> (5-m)) & 0x01);
            }
            bajtDoZapisu =(bity[0]<<7) | (bity[1]<<6) | (bity[2]<<5) | (bity[3]<<4) | (bity[4]<<3) |
            (bity[5]<<2) | (bity[6]<<1) | (bity[7]);
            wyjscie.write((char*)&bajtDoZapisu, sizeof(Uint8));
        }
    }
}

void zapiszPalete6(ofstream& wyjscie, SDL_Color paleta[], int rozmiar) {
    Uint8 zeroByte = 0;
    for (int i=0; i < rozmiar; i++) {
        wyjscie.write((char*)&paleta[i].r, sizeof(Uint8));
        wyjscie.write((char*)&paleta[i].g, sizeof(Uint8));
        wyjscie.write((char*)&paleta[i].b, sizeof(Uint8));
    }
    for (int i = rozmiar; i < 64; i++) {
        for (int j=0; j<3; j++)
            wyjscie.write((char*)&zeroByte, sizeof(Uint8));
    }
}

void odczytajObraz6(ifstream& wejscie, Uint16 szerokoscObrazka, Uint16 wysokoscObrazka, int opcja) {
    SDL_Color kolor;
    Uint8 kolor6bit;
    int bity[6];
    Uint8 bajtyOdczytane[6];

    int k = wysokoscObrazka / 8; // liczba wierszy kolumn po 8 pikseli
    for (int i=0; i<k; i++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            // wczytaj 6 bajtow
            for (int m=0; m<6; m++){
                wejscie.read((char*)&bajtyOdczytane[m], sizeof(Uint8));
            }

            for (int m=0; m<8; m++) {
                for (int j=0; j<6; j++)
                    bity[j] = ((bajtyOdczytane[j] >> (7-m)) & 0x01);
                kolor6bit= 0x00 | (bity[0]<<5) | (bity[1]<<4) | (bity[2]<<3) | (bity[3]<<2) | (bity[4]<<1) |
                (bity[5]);
                if (opcja == 0)
                    kolor = z6Kdo24K(kolor6bit);
                else if (opcja == 1)
                    kolor = z6Sdo24S(kolor6bit);
                else if (opcja == 2)
                    kolor = paletaOdczytana[kolor6bit];
                setPixel(x+(szerokosc/2), 8*i+m, kolor.r, kolor.g, kolor.b);
            }
        }
    }

    SDL_UpdateWindowSurface(window);
}

void odczytajPalete6(ifstream& wejscie) {
    SDL_Color kolor;
    for (int i=0; i<64; i++) {
        wejscie.read((char*)&kolor.r, sizeof(Uint8));
        wejscie.read((char*)&kolor.g, sizeof(Uint8));
        wejscie.read((char*)&kolor.b, sizeof(Uint8));
        paletaOdczytana[i] = kolor;
    }
}

void odczytajPlik6(string nazwaObrazka) {
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = " ";
    Uint8 tryb;
    Uint8 dithering;

    char opcja;
    cout << "Czy wyswietlic palete? (t/n) ";
    cin >> opcja;

    cout << "Odczytujemy plik " + nazwaObrazka + " uzywajac metody read()"<<endl;
    ifstream wejscie(nazwaObrazka + ".z22", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&tryb, sizeof(Uint8));
    wejscie.read((char*)&dithering, sizeof(Uint8));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout<<"id: "<<identyfikator<<endl;
    cout<<"szerokosc: "<<szerokoscObrazka<<endl;
    cout<<"wysokosc: "<<wysokoscObrazka<<endl;
    cout<<"tryb: "<<(int)tryb<<endl;
    cout<<"dithering (0 - brak, 1 - Bayera 4x4, 2 - Floyda-Steinberga): "<<(int)dithering<<endl;
    cout<<"ile bitow: "<<(int)ileBitow<<endl;

    if (tryb == 1) {
        odczytajPalete6(wejscie);
        odczytajObraz6(wejscie, szerokoscObrazka, wysokoscObrazka, 0); // 0 -- paleta narzucona
    }
    else if (tryb == 2) {
        odczytajPalete6(wejscie);
        odczytajObraz6(wejscie, szerokoscObrazka, wysokoscObrazka, 1); // 1 -- skala szarosci narzucona
    }
    else if (tryb == 3 || tryb == 4 || tryb == 5) {
        odczytajPalete6(wejscie);
        odczytajObraz6(wejscie, szerokoscObrazka, wysokoscObrazka, 2); // 2 -- wedlug indeksow zadanej palety
    }
    else {
        cout << "Nieznany tryb" << endl;
        return;
    }

    if (opcja == 't') {
        if (tryb == 1 || tryb == 3) {
            narysujPalete(0, 210, paletaOdczytana);
        } else if (tryb == 2 || tryb == 4) {
            narysujPalete6b(0, 210, paletaOdczytana);
        }
    }

    wejscie.close();
}

string getFileName(const string& filePath) {
    size_t lastSlashPos = filePath.find_last_of("\\/"); // Znajdz ostatni slash
    size_t lastDotPos = filePath.find_last_of("."); // Znajdz ostatnia kropke

    if (lastSlashPos != string::npos) {
        if (lastDotPos != string::npos && lastDotPos > lastSlashPos) {
            return filePath.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1);
        } else {
            return filePath.substr(lastSlashPos + 1);
        }
    }
    return filePath;
}

string getFileExtension(const string& filePath) {
    cout << filePath << endl;
    size_t dotPos = filePath.find_last_of(".");
    if (dotPos != string::npos) {
        return filePath.substr(dotPos);
    }
    return "";
}

/*void zapiszJakoBMP(const string& fileName, SDL_Surface* surface) {
    if (SDL_SaveBMP(surface, fileName.c_str()) != 0) {
        cout << "Error podczas zapisu BMP: " << SDL_GetError() << endl;
    } else {
        cout << "Obrazek poprawnie zapisano jako BMP: " << fileName << endl;
    }
}*/

/*void konwertujZ22doBMP(const string& fileName) {
    ifstream wejscie(fileName + ".z22", ios::binary);
    if (!wejscie.is_open()) {
        cout << "Error podczas otwierania pliku .z22!" << endl;
        return;
    }

    // Zczytaj dane z naglowka
    char identyfikator[2];
    Uint16 szerokoscObrazka, wysokoscObrazka;
    Uint8 tryb, dithering, ileBitow;
    wejscie.read((char*)&identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&tryb, sizeof(Uint8));
    wejscie.read((char*)&dithering, sizeof(Uint8));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout << "File identifier: " << identyfikator << endl;
    cout << "Width: " << szerokoscObrazka << endl;
    cout << "Height: " << wysokoscObrazka << endl;
    cout << "Mode: " << (int)tryb << endl;
    cout << "Dithering: " << (int)dithering << endl;
    cout << "Bit depth: " << (int)ileBitow << endl;

    // Zczytaj palete kolorow
    SDL_Color palette[64];
    for (int i = 0; i < 64; i++) {
        wejscie.read((char*)&palette[i].r, sizeof(Uint8));
        wejscie.read((char*)&palette[i].g, sizeof(Uint8));
        wejscie.read((char*)&palette[i].b, sizeof(Uint8));
    }

    // Stworz SDL_Surface dla obrazka
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, szerokoscObrazka, wysokoscObrazka, 32, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        cout << "Error tworzenia SDL_Surface: " << SDL_GetError() << endl;
        return;
    }

    // Zczytaj dane pikselowe
    int bity[6];
    Uint8 bajtyOdczytane[6];
    int k = wysokoscObrazka / 8;
    for (int i = 0; i < k; i++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            for (int m = 0; m < 6; m++) {
                wejscie.read((char*)&bajtyOdczytane[m], sizeof(Uint8));
            }

            for (int m = 0; m < 8; m++) {
                for (int j = 0; j < 6; j++) {
                    bity[j] = ((bajtyOdczytane[j] >> (7 - m)) & 0x01);
                }
                Uint8 kolor6bit = (bity[0] << 5) | (bity[1] << 4) | (bity[2] << 3) |
                                  (bity[3] << 2) | (bity[4] << 1) | bity[5];

                SDL_Color kolor = palette[kolor6bit];

                Uint32 pixelColor = SDL_MapRGB(surface->format, kolor.r, kolor.g, kolor.b);
                ((Uint32*)surface->pixels)[(i * 8 + m) * szerokoscObrazka + x] = pixelColor;
            }
        }
    }

    // Zapisz obrazek jako bmp
    string outputFileName = getFileName(fileName) + ".bmp";
    zapiszJakoBMP(outputFileName, surface);

    SDL_FreeSurface(surface);
    wejscie.close();
}*/
