
#ifndef SM2025_LAB3_H_INCLUDED
#define SM2025_LAB3_H_INCLUDED

#include <SDL2/SDL.h>
#include "GK2024-Funkcje.h"

// RGB555
void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);
void setRGB555(int xx, int yy, Uint16 rgb555);

// RGB565
void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);
void setRGB565(int xx, int yy, Uint16 rgb565);

void rysujRgb555();
void rysujRgb555_2();
void rysujRgb565();
void rysujRgb565_2();

void przerysujObrazRGB555();
void przerysujObrazRGB565();
void przerysujObrazRGB555D();
void przerysujObrazRGB565D();
#endif // SM2025_LAB3_H_INCLUDED
