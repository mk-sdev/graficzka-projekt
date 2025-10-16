// metody do algorytmu kwantyzacji (MedianCut)
#ifndef GK2024_MEDIANCUT_H_INCLUDED
#define GK2024_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>

#endif // GK2024_MEDIANCUT_H_INCLUDED
void paletaMedianCutBW();
void paletaMedianCut();

//void paletaMedianCutBWDith();
//void paletaMedianCutDith();


void MedianCutBw(int start, int koniec, int iteracja);
void MedianCut(int start, int koniec, int iteracja);
void sortujKubelekBW(int start, int koniec);
void sortujKubelek(int start, int koniec, Uint8 sortowanie);
int znajdzSasiadaBW(Uint8 wartosc);
int znajdzSasiada(SDL_Color kolor);
Uint8 najwiekszaRoznica(int start, int koniec);
