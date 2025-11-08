#ifndef SM2025_FUNKCJE_H_INCLUDED
#define SM2025_FUNKCJE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>


typedef struct {
    float y;
    float u;
    float v;
} YUV;

typedef struct {
    float y;
    float i;
    float q;
} YIQ;

typedef struct {
    float y;
    float cb;
    float cr;
} YCbCr;

typedef struct {
    float h;  // Hue
    float s;  // Saturation
    float l;  // Lightness
} HSL;


void rysujPixelYUV();
void rysujPixelYIQ();
void rysujPixelYCbCr();
void rysujPixelHSL();

void przerysujObrazYUV();
void przerysujObrazYIQ();
void przerysujObrazYCbCr();
void przerysujObrazHSL();

YUV getYUV(int x, int y);
YIQ getYIQ(int x, int y);
YCbCr getYCbCr(int x, int y);

void setYUV(int x, int y, float Y, float U, float V);
void setYIQ(int x, int y, float Y, float I, float Q);
void setYCbCr(int x, int y, float Y, float Cb, float Cr);
HSL getHSL(int x, int y);
void setHSL(int x, int y, float H, float S, float L);
#endif // SM2025_FUNKCJE_H_INCLUDED
