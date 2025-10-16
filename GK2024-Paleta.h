// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2024_PALETA_H_INCLUDED
#define GK2024_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

Uint8 z24Kdo6K(SDL_Color kolor);
SDL_Color z6Kdo24K(Uint8 kolor6bit);
Uint8 z24Kdo6S(SDL_Color kolor);
SDL_Color z6Sdo24S(Uint8 kolor6bit);
void paletaNarzuconaBW();
void paletaNarzuconaKolor();
void narysujPalete(int px, int py, SDL_Color pal6[]);
void narysujPalete6b(int px, int py, SDL_Color pal6b[]);
int sprawdzKolor(SDL_Color kolor);
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
void wymazPalete();
void czyscPalete();
bool paletaWykryta();
//void paletaNarzuconaDith();
//void zaktualizujTabliceBayera4(int zakres);
//void narzuconaSzaraDith();
#endif // GK2024_PALETA_H_INCLUDED
