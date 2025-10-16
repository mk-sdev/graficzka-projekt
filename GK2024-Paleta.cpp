// funkcje do redukcji kolorów i tworzenia palet
#include "GK2024-Paleta.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Funkcje.h"


Uint8 z24Kdo6K(SDL_Color kolor) {
    Uint8 kolor6bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;
    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R*3.0/255.0); // 0-3
    nowyG = round(G*3.0/255.0); // 0-3
    nowyB = round(B*3.0/255.0); // 0-3

    kolor6bit = 0b00 | (nowyR<<4) | (nowyG<<2) | nowyB; // 00RRGGBB
    return kolor6bit;
}

SDL_Color z6Kdo24K(Uint8 kolor6bit) {
    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    nowyR = (kolor6bit&(0b00110000))>>4;
    nowyG = (kolor6bit&(0b00001100))>>2;
    nowyB = (kolor6bit&(0b00000011));

    R = nowyR*255.0/3.0;
    G = nowyG*255.0/3.0;
    B = nowyB*255.0/3.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;
}

Uint8 z24Kdo6S(SDL_Color kolor) {
    Uint8 kolor6bit;
    int R, G, B;
    int szary;
    int nowyS;
    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    szary = 0.299*R + 0.587*G + 0.114*B;
    nowyS = round(szary*63.0/255.0); // 0-63

    kolor6bit = nowyS; // SSSSSS
    return kolor6bit;
}

SDL_Color z6Sdo24S(Uint8 kolor6bit) {
    SDL_Color kolor;
    int szary;
    int nowyS;

    nowyS = (kolor6bit&(0b111111));

    szary = nowyS*255.0/63.0;


    kolor.r = szary;
    kolor.g = szary;
    kolor.b = szary;

    return kolor;
}

void paletaNarzuconaBW() {
    Uint8 szary6bit;
    SDL_Color kolor, nowySzary;

    // narysuj obrazek
    int indeks; // indeks piksela do zapisu
    int y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++) {
                kolor = getPixel(x, y);
                szary6bit = z24Kdo6S(kolor);
                obrazekDoZapisu[indeks] = szary6bit;
                indeks++;
            }
        }
        y_start += 8;
    }

    for (int k = 0; k < 64; k++) {
        paleta6s[k] = z6Sdo24S(k);
    }
}

void paletaNarzuconaKolor() {
    Uint8 kolor6bit;
    SDL_Color kolor, nowyKolor;

    // narysuj obrazek
    int y_start=0;
    int indeks=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                kolor6bit = z24Kdo6K(kolor);
                obrazekDoZapisu[indeks] = kolor6bit;
                indeks++;
            }
        }
        y_start += 8;
    }

    for (int k=0; k<64; k++) {
        paleta6k[k] = z6Kdo24K(k);
    }
}

void narysujPalete(int px, int py, SDL_Color pal6[]) {
    int x, y;
    for (int k=0; k<64; k++) {
        y = k / 16;
        x = k % 16;

        for (int xx=0; xx<20; xx++) {
            for (int yy=0; yy<20; yy++) {
                setPixel(x*20+xx+px, y*20+yy+py, pal6[k].r, pal6[k].g, pal6[k].b);
            }
        }
    }
}

int sprawdzKolor(SDL_Color kolor) {
    if (ileKolorow > 0) {
        for (int k=0; k<ileKolorow; k++) {
            if (porownajKolory(kolor, paleta6[k]))
                return k;
        }
    }
    return dodajKolor(kolor);
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2) {
    if (kolor1.r != kolor2.r)
        return false;
    if (kolor1.g != kolor2.g)
        return false;
    if (kolor1.b != kolor2.b)
        return false;

    return true;
}

int dodajKolor(SDL_Color kolor) {
    int aktualnyKolor = ileKolorow;
    paleta6[aktualnyKolor] = kolor;
    if (ileKolorow<64) {
        cout<<aktualnyKolor<<": [";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}

void wymazPalete() {
    for (int i = 0; i < szerokosc/2; i++) {
        for (int j = 0; j < wysokosc/2; j++) {
            setPixel(i, j+wysokosc/2, 0, 0, 0);
        }
    }
}

void czyscPalete() {
    for (int k=0;k<ileKolorow; k++)
        paleta6[k] = {0, 0, 0};
    ileKolorow = 0;
    for (int k=0;k<64; k++) {
        paleta6s[k] = {0, 0, 0};
        paleta6k[k] = {0, 0, 0};
    }
}

bool paletaWykryta() {
    czyscPalete();
    int indexKoloru;
    SDL_Color kolor;

    int indeks = 0;
    int y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                indexKoloru = sprawdzKolor(kolor);
                obrazekDoZapisu[indeks] = indexKoloru;
                indeks++;
            }
        }
        y_start += 8;
    }

    cout << endl<<"ile kolorow: "<<ileKolorow<<endl;
    if (ileKolorow > 64) {
        cout<<"Paleta przekracza ograniczenia 6-bit / piksel"<<endl;
        return false;
    }

    cout<<"Paleta spelnia ograniczenia 6-bit / piksel"<<endl;
    narysujPalete(0, 210, paleta6);
    return true;
}

void zaktualizujTabliceBayera4(int zakres) {
    int rozmiar = 4;
    float podzial = zakres*1.0 / (rozmiar*rozmiar);
    for (int y=0; y<rozmiar; y++) {
        for (int x=0; x<rozmiar; x++) {
            zaktualizowanaTablicaBayera4[y][x] =
            (tablicaBayera4[y][x]*podzial)-podzial/2;
        }
    }
    for (int y=0; y<rozmiar; y++) {
        for (int x=0; x<rozmiar; x++) {
            cout<<tablicaBayera4[y][x]<<" ";
        }
        cout << endl;
    }

    cout << endl;

    for (int y=0; y<rozmiar; y++) {
        for (int x=0; x<rozmiar; x++) {
            cout<<zaktualizowanaTablicaBayera4[y][x]<<" ";
        }
        cout << endl;
    }
}

void paletaNarzuconaDith() {
    int rozmiar = 4;

    int przesuniecieR = 0;
    int przesuniecieG = 0;
    int przesuniecieB = 0;

    zaktualizujTabliceBayera4(86);
    SDL_Color kolor;
    Uint8 newR, newG, newB;
    Uint8 piksel;
    float tablica;

    int indeks = 0;
    int y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                tablica = zaktualizowanaTablicaBayera4[y % rozmiar][x % rozmiar];

                if (kolor.r > 170)
                    przesuniecieR = 2;
                else if (kolor.r > 85)
                    przesuniecieR = 1;
                else
                    przesuniecieR = 0;

                if (kolor.g > 170)
                    przesuniecieG = 2;
                else if (kolor.g > 85)
                    przesuniecieG = 1;
                else
                    przesuniecieG = 0;

                if (kolor.b > 170)
                    przesuniecieB = 2;
                else if (kolor.b > 85)
                    przesuniecieB = 1;
                else
                    przesuniecieB = 0;


                if ((kolor.r - przesuniecieR*85) > tablica)
                    newR = 85 + 85*przesuniecieR;
                else
                    newR = 0 + 85*przesuniecieR;

                if ((kolor.g - przesuniecieG*85) > tablica)
                    newG = 85 + 85*przesuniecieG;
                else
                    newG = 0 + 85*przesuniecieG;

                if ((kolor.b - przesuniecieB*85) > tablica)
                    newB = 85 + 85*przesuniecieB;
                else
                    newB = 0 + 85*przesuniecieB;

                obrazekDoZapisu[indeks] = z24Kdo6K({newR, newG, newB});
                indeks++;
            }
        }
        y_start += 8;
    }

    for (int k=0; k<64; k++) {
        paleta6k[k] = z6Kdo24K(k);
    }
}

void narzuconaSzaraDith() {
    int rozmiar = 4;
    zaktualizujTabliceBayera4(5);

    SDL_Color kolor;
    int szary;
    int newSzary;
    float tablica;

    // iteracja po pikselach w lewym górnym rogu
    int indeks = 0;
    int y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                tablica = zaktualizowanaTablicaBayera4[y % rozmiar][x % rozmiar];

                Uint8 szary = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;

                int przesuniecie = szary / 4;

                if ((szary % 4) > tablica)
                    newSzary = min(255, 4 * (przesuniecie + 1));
                else
                    newSzary = 4 * przesuniecie;

                obrazekDoZapisu[indeks] = z24Kdo6S({newSzary, newSzary, newSzary});
                indeks++;
            }
        }
        y_start += 8;
    }

    for (int k = 0; k < 64; k++) {
        paleta6s[k] = z6Sdo24S(k);
    }
}

void narysujPalete6b(int px, int py, SDL_Color pal6b[]) {
    int x, y;
    for (int k=0; k<64; k++) {
        y = k / 16;
        x = k % 16;

        for (int xx=0; xx<20; xx++) {
            for (int yy=0; yy<20; yy++) {
                setPixel(x*20+xx+px, y*20+yy+py, pal6b[k].r, pal6b[k].g, pal6b[k].b);
            }
        }
    }
}
