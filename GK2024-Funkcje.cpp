// podstawowe funkcje
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"
#include "SM2025-Lab2.h"
#include "SM2025-Lab3.h"
#include "SM2025-Lab4.h"
#include "SM2025-Lab5.h"

void Funkcja1() {
    paletaNarzuconaKolor();
    SDL_UpdateWindowSurface(window);
}

/*void Funkcja2() {
    paletaNarzuconaDith();
    SDL_UpdateWindowSurface(window);
}*/

void Funkcja3() {
    paletaNarzuconaBW();
    SDL_UpdateWindowSurface(window);
}

/*void Funkcja4() {
    narzuconaSzaraDith();
    SDL_UpdateWindowSurface(window);
}*/

void Funkcja5() {
    paletaMedianCut();
    SDL_UpdateWindowSurface(window);
}

/*void Funkcja6() {
    paletaMedianCutDith();
    SDL_UpdateWindowSurface(window);
}*/

void Funkcja7() {
    paletaMedianCutBW();
    SDL_UpdateWindowSurface(window);
}

/*void Funkcja8() {
    paletaMedianCutBWDith();
    SDL_UpdateWindowSurface(window);
}*/

bool Funkcja9() {
    return paletaWykryta();
}

void Funkcja10(){
    rysujPixelYUV();
}
void Funkcja11(){
    przerysujObrazYUV();
}
void Funkcja12(){
    rysujPixelYIQ();
}
void Funkcja13(){
    przerysujObrazYIQ();
}
void Funkcja14(){
    rysujPixelYCbCr();
}
void Funkcja15(){
    przerysujObrazYCbCr();
}
void Funkcja16(){
    rysujPixelHSL();
}
void Funkcja17(){
    przerysujObrazHSL();
}

//Lab4
void Funkcja18(){
    FunkcjaLab4();
};

void Funkcja19(){
    FunkcjaLab4_2();
};

//Lab3
void Funkcja20()
{
    rysujRgb555();
}

void Funkcja21()
{
    rysujRgb555_2();
}

void Funkcja22()
{
    rysujRgb565();
}

void Funkcja23()
{
    rysujRgb565_2();
}

void Funkcja24(){
    przerysujObrazRGB555();
}

void Funkcja25(){
    przerysujObrazRGB565();
}

void Funkcja26(){
    przerysujObrazRGB555D();
}

void Funkcja27(){
    przerysujObrazRGB565D();
}

/// Lab5


void Funkcja28() {applyFilterType1();}
void Funkcja29() {applyFilterType2();}
void Funkcja30() {applyFilterType3();}
void Funkcja31() {applyFilterType4();}

void Funkcja32() {decodeFilterType1();}
void Funkcja33() {decodeFilterType2();}
void Funkcja34() {decodeFilterType3();}
void Funkcja35() {decodeFilterType4();}


void Funkcja36() {}
void Funkcja37() {}
void Funkcja38() {}
void Funkcja39() {}
void Funkcja40() {}
void Funkcja41() {}
void Funkcja42() {}
void Funkcja43() {}
void Funkcja44() {}
void Funkcja45() {}
void Funkcja46() {}
void Funkcja47() {}
void Funkcja48() {}
void Funkcja49() {}
void Funkcja50() {}


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y) {
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}

