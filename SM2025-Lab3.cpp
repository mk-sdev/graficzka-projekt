
#include "SM2025-Lab3.h"
#include "GK2024-Zmienne.h"
#include <iostream>
using namespace std;

void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    // konwersja do 5-bitowego kanalu
    Uint16 r5 = (r * 31) / 255;
    Uint16 g5 = (g * 31) / 255;
    Uint16 b5 = (b * 31) / 255;

    // polaczenie w 16 nitowy kolor rgb
    Uint16 rgb555 = (r5 << 10) | (g5 << 5) | b5;

    setRGB555(xx, yy, rgb555);
}

void setRGB555(int xx, int yy, Uint16 rgb555)
{
    // rozdzielenie na kanly 5-bitowe
    Uint8 r5 = (rgb555 >> 10) & 0x1F;
    Uint8 g5 = (rgb555 >> 5) & 0x1F;
    Uint8 b5 = rgb555 & 0x1F;

    // skalowanie do pelnego 8 bitowego rgb
    Uint8 r = (r5 * 255) / 31;
    Uint8 g = (g5 * 255) / 31;
    Uint8 b = (b5 * 255) / 31;

    setPixel(xx, yy, r, g, b);
    SDL_UpdateWindowSurface(window);
}

void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    Uint16 r5 = (r * 31) / 255;
    Uint16 g6 = (g * 63) / 255;
    Uint16 b5 = (b * 31) / 255;

    Uint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;

    setRGB565(xx, yy, rgb565);
}

void setRGB565(int xx, int yy, Uint16 rgb565)
{
    Uint8 r5 = (rgb565 >> 11) & 0x1F;
    Uint8 g6 = (rgb565 >> 5) & 0x3F;
    Uint8 b5 = rgb565 & 0x1F;

    Uint8 r = (r5 * 255) / 31;
    Uint8 g = (g6 * 255) / 63;
    Uint8 b = (b5 * 255) / 31;

    setPixel(xx, yy, r, g, b);
    SDL_UpdateWindowSurface(window);
}

void rysujRgb555()
{
    int x, y;
    int r, g, b;

    cout << "Podaj wspolrzedne piksela x: ";
    cin >> x;
    cout << "Podaj wspolrzedne piksela y: ";
    cin >> y;

    cout << "Podaj kolor R: ";
    cin >> r;
    cout << "Podaj kolor G: ";
    cin >> g;
    cout << "Podaj kolor B: ";
    cin >> b;

    setRGB555(x, y, static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b));
}

void rysujRgb555_2()
{
    int x, y;
    unsigned int rgb555;

    cout << "Podaj wspolrzedne piksela x: ";
    cin >> x;
    cout << "Podaj wspolrzedne piksela y: ";
    cin >> y;

    cout << "Podaj wartosc koloru RGB555 (0-32767): ";
    cin >> hex >> rgb555;
    cin >> dec; // wracamy do trybu dziesietnego

    setRGB555(x, y, static_cast<Uint16>(rgb555));
}


void rysujRgb565()
{
    int x, y;
    int r, g, b;

    cout << "Podaj wspolrzedne piksela x: ";
    cin >> x;
    cout << "Podaj wspolrzedne piksela y: ";
    cin >> y;

    cout << "Podaj kolor R: ";
    cin >> r;
    cout << "Podaj kolor G: ";
    cin >> g;
    cout << "Podaj kolor B: ";
    cin >> b;

    setRGB565(x, y, static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b));
}

void rysujRgb565_2()
{
    int x, y;
    unsigned int rgb565;

    cout << "Podaj wspolrzedne piksela x: ";
    cin >> x;
    cout << "Podaj wspolrzedne piksela y: ";
    cin >> y;

    cout << "Podaj wartosc koloru RGB565 (0-65535): ";
    cin >> rgb565;
    cin >> dec; // powrot do dziesietnego

    setRGB565(x, y, static_cast<Uint16>(rgb565));

}

/// 2


SDL_Color getRGB555(int xx, int yy)
{
    // pobranie koloru piksela z ekranu
    SDL_Color col = getPixel(xx, yy);

    // kwantyzacja do 5 bitow na kanal
    Uint8 r5 = (col.r * 31) / 255;
    Uint8 g5 = (col.g * 31) / 255;
    Uint8 b5 = (col.b * 31) / 255;

    //przeskalowanie z powrotem do 8 bitow
    SDL_Color result;
    result.r = (r5 * 255) / 31;
    result.g = (g5 * 255) / 31;
    result.b = (b5 * 255) / 31;
    result.a = 255;

    return result;
}

Uint16 getRGB555_(int xx, int yy)
{
    // pobranie koloru z ekranu
    SDL_Color col = getPixel(xx, yy);

    // kwantyzacja do 5 bitow
    Uint16 r5 = (col.r * 31) / 255;
    Uint16 g5 = (col.g * 31) / 255;
    Uint16 b5 = (col.b * 31) / 255;

    // z³ozenie w 16 bitowy format rgb555
    Uint16 rgb555 = (r5 << 10) | (g5 << 5) | b5;

    return rgb555;
}

SDL_Color getRGB565(int xx, int yy)
{
    SDL_Color col = getPixel(xx, yy);

    // kwantyzacja: 5 bitow r, 6 bitow g, 5 bitow b
    Uint8 r5 = (col.r * 31) / 255;
    Uint8 g6 = (col.g * 63) / 255;
    Uint8 b5 = (col.b * 31) / 255;

    //przeskalowanie do 8bitow
    SDL_Color result;
    result.r = (r5 * 255) / 31;
    result.g = (g6 * 255) / 63;
    result.b = (b5 * 255) / 31;
    result.a = 255;

    return result;
}

Uint16 getRGB565_(int xx, int yy)
{
    SDL_Color col = getPixel(xx, yy);

    Uint16 r5 = (col.r * 31) / 255;
    Uint16 g6 = (col.g * 63) / 255;
    Uint16 b5 = (col.b * 31) / 255;

    Uint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;

    return rgb565;
}


/// 3

// funkcja pomocnicza
template <typename T>
T clampValue(T val, T minVal, T maxVal)
{
    if (val < minVal) return minVal;
    if (val > maxVal) return maxVal;
    return val;
}

static const int Bayer4x4[4][4] = {
    { 0,  8,  2, 10},
    {12,  4, 14,  6},
    { 3, 11,  1,  9},
    {15,  7, 13,  5}
};

SDL_Color getRGB555D(int xx, int yy)
{
    SDL_Color col = getPixel(xx, yy);
    double dither = (Bayer4x4[yy % 4][xx % 4] + 0.5) / 16.0;

    double step = 255.0 / 31.0; // 5-bit -> 31 poziomow
    Uint8 r = clampValue(int(col.r + dither * step - step / 2), 0, 255);
    Uint8 g = clampValue(int(col.g + dither * step - step / 2), 0, 255);
    Uint8 b = clampValue(int(col.b + dither * step - step / 2), 0, 255);

    Uint8 r5 = (r * 31) / 255;
    Uint8 g5 = (g * 31) / 255;
    Uint8 b5 = (b * 31) / 255;

    SDL_Color result;
    result.r = (r5 * 255) / 31;
    result.g = (g5 * 255) / 31;
    result.b = (b5 * 255) / 31;
    result.a = 255;
    return result;
}

Uint16 getRGB555D_(int xx, int yy)
{
    SDL_Color c = getRGB555D(xx, yy);
    Uint16 r5 = (c.r * 31) / 255;
    Uint16 g5 = (c.g * 31) / 255;
    Uint16 b5 = (c.b * 31) / 255;
    return (r5 << 10) | (g5 << 5) | b5;
}

SDL_Color getRGB565D(int xx, int yy)
{
    SDL_Color col = getPixel(xx, yy);
    double dither = (Bayer4x4[yy % 4][xx % 4] + 0.5) / 16.0;

    double stepR = 255.0 / 31.0;
    double stepG = 255.0 / 63.0;
    double stepB = 255.0 / 31.0;

    Uint8 r = clampValue(int(col.r + dither * stepR - stepR / 2), 0, 255);
    Uint8 g = clampValue(int(col.g + dither * stepG - stepG / 2), 0, 255);
    Uint8 b = clampValue(int(col.b + dither * stepB - stepB / 2), 0, 255);

    Uint8 r5 = (r * 31) / 255;
    Uint8 g6 = (g * 63) / 255;
    Uint8 b5 = (b * 31) / 255;

    SDL_Color result;
    result.r = (r5 * 255) / 31;
    result.g = (g6 * 255) / 63;
    result.b = (b5 * 255) / 31;
    result.a = 255;
    return result;
}

Uint16 getRGB565D_(int xx, int yy)
{
    SDL_Color c = getRGB565D(xx, yy);
    Uint16 r5 = (c.r * 31) / 255;
    Uint16 g6 = (c.g * 63) / 255;
    Uint16 b5 = (c.b * 31) / 255;
    return (r5 << 11) | (g6 << 5) | b5;
}

/// 4

void przerysujObrazRGB555()
{
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {

            SDL_Color kolor = getPixel(x, y);

            Uint16 rgb555 = ((kolor.r * 31) / 255 << 10) |
                            ((kolor.g * 31) / 255 << 5) |
                            ((kolor.b * 31) / 255);

            Uint8 r = (((rgb555 >> 10) & 0x1F) * 255) / 31;
            Uint8 g = (((rgb555 >> 5) & 0x1F) * 255) / 31;
            Uint8 b = ((rgb555 & 0x1F) * 255) / 31;

            setPixel(x + half_width, y, r, g, b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void przerysujObrazRGB565()
{
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {

            SDL_Color kolor = getPixel(x, y);

            Uint16 rgb565 = ((kolor.r * 31) / 255 << 11) |
                            ((kolor.g * 63) / 255 << 5) |
                            ((kolor.b * 31) / 255);

            Uint8 r = (((rgb565 >> 11) & 0x1F) * 255) / 31;
            Uint8 g = (((rgb565 >> 5) & 0x3F) * 255) / 63;
            Uint8 b = ((rgb565 & 0x1F) * 255) / 31;

            setPixel(x + half_width, y, r, g, b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void przerysujObrazRGB555D()
{
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {

            SDL_Color kolor = getRGB555D(x, y);
            setPixel(x + half_width, y + half_height, kolor.r, kolor.g, kolor.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void przerysujObrazRGB565D()
{
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {

            SDL_Color kolor = getRGB565D(x, y);
            setPixel(x + half_width, y + half_height, kolor.r, kolor.g, kolor.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}










