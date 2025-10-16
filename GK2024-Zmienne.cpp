// zmienne globalne
#include "GK2024-Zmienne.h"

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

SDL_Color paleta6[szerokosc*wysokosc];
int ileKolorow = 0;

SDL_Color paleta6k[64];
SDL_Color paleta6s[64];

int tablicaBayera4[4][4] = { {6, 14, 8, 16},
                             {10, 2, 12, 4},
                             {7, 15, 5, 13},
                             {11, 3, 9, 1}};

float zaktualizowanaTablicaBayera4[4][4];

int ileKubelkow = 0;
Uint8 obrazekS[320*200];
SDL_Color obrazekK[320*200];
Uint8 obrazekDoZapisu[320*200];
SDL_Color paletaOdczytana[64];
