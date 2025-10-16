// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2024-MedianCut.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Funkcje.h"
#include "GK2024-Paleta.h"

using namespace std;

// CZESC SZARA ------------------------------
void paletaMedianCutBW() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary = 0;
    int numer = 0;
    int indeks = 0;

    int y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                szary=0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
                obrazekS[numer] = szary;
                setPixel(x + szerokosc/2, y, szary, szary, szary);
                numer++;
            }
        }
        y_start += 8;
    }
    MedianCutBw(0, numer-1, 6);

    int indeksPiksela = 0;
    y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                szary=getPixel(x + szerokosc/2, y).r;
                indeks = znajdzSasiadaBW(szary);
                //setPixel(x + szerokosc/2, y + wysokosc/2,
                         //paleta6s[indeks].r, paleta6s[indeks].g, paleta6s[indeks].b);

                obrazekDoZapisu[indeksPiksela] = indeks;
                indeksPiksela++;
            }
        }
        y_start += 8;
    }
}

// Narzucona skala szarosci z ditheringiem Floyda-Steinberga
/*void paletaMedianCutBWDith() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;

    int indeksPiksela;

    int szary = 0;
    int szaryNew = 0;

    int numer = 0;
    int indeks = 0;

    Uint8 przesuniecie = 1;
    float bledy[(szerokosc/2)+2][wysokosc+2];
    memset(bledy, 0, sizeof(bledy));
    int blad = 0;

    // zbieranie danych
    for (int y=0; y<wysokosc/2; y++) {
        for (int x=0; x<szerokosc/2; x++) {
            kolor = getPixel(x, y);
            szary=0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            obrazekS[numer] = szary;
            setPixel(x + szerokosc/2, y, szary, szary, szary);
            numer++;
        }
    }
    MedianCutBw(0, numer-1, 6); // utworz palete dedykowana

    for (int y=0; y<wysokosc/2; y++) {
        for (int x=0; x<szerokosc/2; x++) {
            kolor = getPixel(x, y);
            szary=0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            szary += bledy[x+przesuniecie][y];

            szaryNew = szary;
            if (szaryNew>255) szaryNew = 255;
            else if (szaryNew<0) szaryNew = 0;

            indeks = znajdzSasiadaBW(szaryNew);
            blad = szary - paleta6s[indeks].r;

            bledy[x+1+przesuniecie][y] += (blad*7.0/16.0);
            bledy[x-1+przesuniecie][y+1] += (blad*3.0/16.0);
            bledy[x+przesuniecie][y+1] += (blad*5.0/16.0);
            bledy[x+1+przesuniecie][y+1] += (blad*1.0/16.0);

            indeksPiksela = int(y/8) * szerokosc/2 * 8 + x*8 + y%8;
            obrazekDoZapisu[indeksPiksela] = indeks;
        }
    }
}*/

void MedianCutBw(int start, int koniec, int iteracja) {
    if (iteracja > 0) {
        // najpierw sortuj kubelek
        sortujKubelekBW(start, koniec);

        // wyznacz srodek podzialu
        int srodek = (start + koniec + 1)/2;

        // dziel kubelek na mniejsze
        MedianCutBw(start, srodek-1, iteracja-1);
        MedianCutBw(srodek, koniec, iteracja-1);
    }
    else {
        // buduj palete usredniajac wartosci z okreslonego kubelka
        int sumaBW = 0;
        for (int p=start; p<=koniec; p++) {
            sumaBW += obrazekS[p]; // sumuj wartosci z danego kubelka
        }
        Uint8 noweBW = sumaBW / (koniec + 1 - start); // wyliczenie sredniej
        SDL_Color nowyKolor = {noweBW, noweBW, noweBW};
        paleta6s[ileKubelkow] = nowyKolor;

        ileKubelkow++;
    }
}

void sortujKubelekBW(int start, int koniec) {
    int  minimum;
    for (int p = start; p <= koniec; p++) {
        minimum = p;
        for (int i=p; i <= koniec; i++) {
            if (obrazekS[i] < obrazekS[minimum])
                minimum = i;
        }
        swap(obrazekS[p], obrazekS[minimum]);
    }
}

int znajdzSasiadaBW(Uint8 wartosc) {
    int minimum = 999;
    int indexMinimum = 0;

    int odleglosc = 0;

    for (int i=0; i<64; i++) {
        odleglosc = abs(wartosc - paleta6s[i].r);
        if (odleglosc < minimum) {
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}

// CZESC KOLOROWA ------------
void paletaMedianCut() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int numer = 0;
    int indeks = 0;

    int y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                obrazekK[numer] = {kolor.r, kolor.g, kolor.b};
                setPixel(x + szerokosc/2, y,
                         obrazekK[numer].r, obrazekK[numer].g, obrazekK[numer].b);
                numer++;
            }
        }
        y_start += 8;
    }

    MedianCut(0, numer-1, 6);

    int indeksPiksela = 0;
    y_start=0;
    for (int i=0; i < wysokosc/2/8; i++) {
        for (int x=0; x<szerokosc/2; x++) {
            for (int y=y_start; y<y_start+8; y++){
                kolor = getPixel(x, y);
                indeks = znajdzSasiada(kolor);
                obrazekDoZapisu[indeksPiksela] = indeks;
                indeksPiksela++;
            }
        }
        y_start += 8;
    }
}

// Paleta narzucona z ditheringiem Floyda-Steinberga
/*void paletaMedianCutDith() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    SDL_Color newKolor;
    int numer = 0;
    int indeks = 0;

    int indeksPiksela;

    int newRed, newGreen, newBlue;
    int red, green, blue;
    Uint8 przesuniecie = 1;
    float bledyR[(szerokosc/2)+2][wysokosc+2];
    float bledyG[(szerokosc/2)+2][wysokosc+2];
    float bledyB[(szerokosc/2)+2][wysokosc+2];
    memset(bledyR, 0, sizeof(bledyR));
    memset(bledyG, 0, sizeof(bledyG));
    memset(bledyB, 0, sizeof(bledyB));
    int bladR = 0;
    int bladG = 0;
    int bladB = 0;

    // pobranie danych
    for (int y=0; y<wysokosc/2; y++) {
        for (int x=0; x<szerokosc/2; x++) {
            kolor = getPixel(x, y);
            obrazekK[numer] = {kolor.r, kolor.g, kolor.b};

            numer++;
        }
    }

    MedianCut(0, numer-1, 6); // utworz palete

    for (int y=0; y<wysokosc/2; y++) {
        for (int x=0; x<szerokosc/2; x++) {
            kolor = getPixel(x, y);

            red = kolor.r + bledyR[x+przesuniecie][y];
            green = kolor.g + bledyG[x+przesuniecie][y];
            blue = kolor.b + bledyB[x+przesuniecie][y];

            newRed = red;
            newGreen = green;
            newBlue = blue;


            if (newRed>255) newRed = 255;
            else if (newRed<0) newRed = 0;

            if (newGreen>255) newGreen = 255;
            else if (newGreen<0) newGreen = 0;

            if (newBlue>255) newBlue = 255;
            else if (newBlue<0) newBlue = 0;

            indeks = znajdzSasiada({newRed, newGreen, newBlue});

            bladR = abs(red - paleta6k[indeks].r);
            bladG = abs(green - paleta6k[indeks].g);
            bladB = abs(blue - paleta6k[indeks].b);

            bledyR[x+1+przesuniecie][y] += (bladR*7.0/16.0);
            bledyR[x-1+przesuniecie][y+1] += (bladR*3.0/16.0);
            bledyR[x+przesuniecie][y+1] += (bladR*5.0/16.0);
            bledyR[x+1+przesuniecie][y+1] += (bladR*1.0/16.0);

            bledyG[x+1+przesuniecie][y] += (bladG*7.0/16.0);
            bledyG[x-1+przesuniecie][y+1] += (bladG*3.0/16.0);
            bledyG[x+przesuniecie][y+1] += (bladG*5.0/16.0);
            bledyG[x+1+przesuniecie][y+1] += (bladG*1.0/16.0);

            bledyB[x+1+przesuniecie][y] += (bladB*7.0/16.0);
            bledyB[x-1+przesuniecie][y+1] += (bladB*3.0/16.0);
            bledyB[x+przesuniecie][y+1] += (bladB*5.0/16.0);
            bledyB[x+1+przesuniecie][y+1] += (bladB*1.0/16.0);

            //setPixel(x + szerokosc/2, y + wysokosc/2,
                     //paleta6k[indeks].r, paleta6k[indeks].g, paleta6k[indeks].b);
            indeksPiksela = int(y/8) * szerokosc/2 * 8 + x*8 + y%8;
            obrazekDoZapisu[indeksPiksela] = indeks;
        }
    }
    narysujPalete6b(0, 210, paleta6k);
}*/

void MedianCut(int start, int koniec, int iteracja) {
    //for (int i=0; i<iteracja; i++) cout << " ";
    //cout << "start: "<<start<<", koniec: "<<koniec<<", iteracja: "<<iteracja<<endl;
    if (iteracja > 0) {
        // najpierw ustalamy wzgledem ktorej skladowej bedziemy sortowac kubelek
        Uint8 sortowanie = najwiekszaRoznica(start, koniec);


        // potem sortujemy kubelek wzgledem tej skladowej
        sortujKubelek(start, koniec, sortowanie);
        //for (int i=0; i<iteracja; i++) cout <<" ";
        //cout<<"Dziellimy kubelek na poziomie "<<iteracja<<endl;

        // wyznacz srodek podzialu
        int srodek = (start + koniec + 1)/2;

        // dziel kubelek na mniejsze
        MedianCut(start, srodek-1, iteracja-1);
        MedianCut(srodek, koniec, iteracja-1);
    }
    else {
        // buduj palete usredniajac wartosci z okreslonego kubelka
        int sumaR = 0, sumaG = 0, sumaB = 0;
        for (int p=start; p<=koniec; p++) {
            sumaR += obrazekK[p].r; // sumuj wartosci R z danego kubelka
            sumaG += obrazekK[p].g; // sumuj wartosci R z danego kubelka
            sumaB += obrazekK[p].b; // sumuj wartosci R z danego kubelka
        }
        int sredniaR = sumaR / (koniec + 1 - start); // wyliczenie sredniej R
        int sredniaG = sumaG / (koniec + 1 - start); // wyliczenie sredniej G
        int sredniaB = sumaB / (koniec + 1 - start); // wyliczenie sredniej B

        SDL_Color nowyKolor = {sredniaR, sredniaG, sredniaB};
        paleta6k[ileKubelkow] = nowyKolor;

        /*
        cout<<"Kubelek "<<ileKubelkow<<": ";
        cout<<"(s: "<<start<<", k: "<<koniec<<", e: "<<(koniec+1-start)<<")";
        cout<<endl;
        cout<<"Kolor "<<ileKubelkow<<": ("<<(int)nowyKolor.r<<", ";
        cout<<(int)nowyKolor.g<<", "<<(int)nowyKolor.b<<")"<<endl;
        */
        ileKubelkow++;
    }
}

Uint8 najwiekszaRoznica(int start, int koniec) {
    int minR=start, minG=start, minB=start;
    int maxR=start, maxG=start, maxB=start;

    Uint8 roznica = 0;

    for (int i=start; i<=koniec; i++) {
        if (obrazekK[i].b < obrazekK[minB].b) minB=i;
        if (obrazekK[i].g < obrazekK[minG].g) minG=i;
        if (obrazekK[i].r < obrazekK[minR].r) minR=i;
        if (obrazekK[i].b > obrazekK[maxB].b) maxB=i;
        if (obrazekK[i].g > obrazekK[maxG].g) maxG=i;
        if (obrazekK[i].r > obrazekK[maxR].r) maxR=i;
    }
    int roznicaR = obrazekK[maxR].r-obrazekK[minR].r;
    int roznicaG = obrazekK[maxG].g-obrazekK[minG].g;
    int roznicaB = obrazekK[maxB].b-obrazekK[minB].b;

    int roznicaM = max(max(roznicaR, roznicaG), roznicaB);

    if (roznicaM == roznicaR)
        roznica = 1; //R
    else if (roznicaM == roznicaG)
        roznica = 2; // G
    else roznica = 3; // B
    return roznica;
}

void sortujKubelek(int start, int koniec, Uint8 sortowanie) {
    int  minimum;
    for (int p = start; p <= koniec; p++) {
        minimum = p;
        for (int i=p; i <= koniec; i++) {
            switch(sortowanie){
                case 1:
                    if (obrazekK[i].r < obrazekK[minimum].r) minimum = i;
                break;
                case 2:
                    if (obrazekK[i].g < obrazekK[minimum].g) minimum = i;
                break;
                case 3:
                    if (obrazekK[i].b < obrazekK[minimum].b) minimum = i;
                break;
            }

        }
        swap(obrazekK[p], obrazekK[minimum]);
    }
}

int znajdzSasiada(SDL_Color kolor) {
    int minimum = 99999;
    int indexMinimum = 0;

    SDL_Color kolorPaleta;
    float odleglosc = 0;

    for (int i=0; i<64; i++) {
        kolorPaleta = paleta6k[i];
        odleglosc = sqrt((kolor.r - kolorPaleta.r)*(kolor.r - kolorPaleta.r)+
                         (kolor.g - kolorPaleta.g)*(kolor.g - kolorPaleta.g)+
                         (kolor.b - kolorPaleta.b)*(kolor.b - kolorPaleta.b));
        if (odleglosc < minimum) {
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}

