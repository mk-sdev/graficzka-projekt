#ifndef SM2025_LAB5_H_INCLUDED
#define SM2025_LAB5_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

Uint8 PaethPredictor(Uint8 a, Uint8 b, Uint8 c);

// Filtry
Uint8 FilterNone(Uint8 raw);
Uint8 FilterSub(Uint8 raw, Uint8 left);
Uint8 FilterUp(Uint8 raw, Uint8 upper);
Uint8 FilterAverage(Uint8 raw, Uint8 left, Uint8 upper);
Uint8 FilterPaeth(Uint8 raw, Uint8 left, Uint8 upper, Uint8 upper_left);

// Funkcje przetwarzaj¹ce obraz
void applyFilterType1();
void applyFilterType2();
void applyFilterType3();
void applyFilterType4();

void decodeFilterType1();
void decodeFilterType2();
void decodeFilterType3();
void decodeFilterType4();
#endif // SM2025_LAB5_H_INCLUDED
