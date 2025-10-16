// zmienne globalne
#ifndef GK2024_ZMIENNE_H_INCLUDED
#define GK2024_ZMIENNE_H_INCLUDED

#include <SDL2/SDL.h>

#define szerokosc 640
#define wysokosc 400

#define tytul "GK2024 - Projekt - Zespol 22"

extern SDL_Window* window;
extern SDL_Surface* screen;

extern SDL_Color paleta6[szerokosc*wysokosc];
extern int ileKolorow;

extern SDL_Color paleta6k[64];
extern SDL_Color paleta6s[64];

extern int tablicaBayera4[4][4];
extern float zaktualizowanaTablicaBayera4[4][4];

extern int ileKubelkow;
extern Uint8 obrazekS[320*200];
extern SDL_Color obrazekK[320*200];

extern Uint8 obrazekDoZapisu[320*200];

extern SDL_Color paletaOdczytana[64];

#endif // GK2024_ZMIENNE_H_INCLUDED
