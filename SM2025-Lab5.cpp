#include "SM2025-Lab5.h"
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include <iostream>

Uint8 PaethPredictor(Uint8 a, Uint8 b, Uint8 c) {
    int p = a + b - c;
    int pa = abs(p - a);
    int pb = abs(p - b);
    int pc = abs(p - c);

    if (pa <= pb && pa <= pc) return a;
    else if (pb <= pc) return b;
    else return c;
}

/// FILTRY
Uint8 FilterNone(Uint8 raw) {
    return raw;
}

Uint8 FilterSub(Uint8 raw, Uint8 left) {
    return Uint8(raw - left);
}

Uint8 FilterUp(Uint8 raw, Uint8 upper) {
    return Uint8(raw - upper);
}

Uint8 FilterAverage(Uint8 raw, Uint8 left, Uint8 upper) {
    Uint8 avg = Uint8((left + upper) / 2);
    return Uint8(raw - avg);
}

Uint8 FilterPaeth(Uint8 raw, Uint8 left, Uint8 upper, Uint8 upper_left) {
    Uint8 paeth = PaethPredictor(left, upper, upper_left);
    return Uint8(raw - paeth);
}

/// FILTROWANIE

void applyFilterType1() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color left = (x > 0) ? getPixel(x - 1, y) : SDL_Color{0,0,0,0};
            SDL_Color out;
            out.r = FilterSub(c.r, left.r);
            out.g = FilterSub(c.g, left.g);
            out.b = FilterSub(c.b, left.b);
            setPixel(x + half_width, y, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void applyFilterType2() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color up = (y > 0) ? getPixel(x, y - 1) : SDL_Color{0,0,0,0};
            SDL_Color out;
            out.r = FilterUp(c.r, up.r);
            out.g = FilterUp(c.g, up.g);
            out.b = FilterUp(c.b, up.b);
            setPixel(x + half_width, y, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void applyFilterType3() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color left = (x > 0) ? getPixel(x - 1, y) : SDL_Color{0,0,0,0};
            SDL_Color up = (y > 0) ? getPixel(x, y - 1) : SDL_Color{0,0,0,0};
            SDL_Color out;
            out.r = FilterAverage(c.r, left.r, up.r);
            out.g = FilterAverage(c.g, left.g, up.g);
            out.b = FilterAverage(c.b, left.b, up.b);
            setPixel(x + half_width, y, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void applyFilterType4() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color left = (x > 0) ? getPixel(x - 1, y) : SDL_Color{0,0,0,0};
            SDL_Color up = (y > 0) ? getPixel(x, y - 1) : SDL_Color{0,0,0,0};
            SDL_Color up_left = (x > 0 && y > 0) ? getPixel(x - 1, y - 1) : SDL_Color{0,0,0,0};

            SDL_Color out;
            out.r = FilterPaeth(c.r, left.r, up.r, up_left.r);
            out.g = FilterPaeth(c.g, left.g, up.g, up_left.g);
            out.b = FilterPaeth(c.b, left.b, up.b, up_left.b);
            setPixel(x + half_width, y, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}


/// DEKODOWANIE

void decodeFilterType1() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    SDL_Color decoded[half_width][half_height];

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {

            SDL_Color f = getPixel(x + half_width, y); // piksel przefiltrowany
            SDL_Color left = (x > 0) ? decoded[x-1][y] : SDL_Color{0,0,0,0};

            decoded[x][y].r = (f.r + left.r) % 256;
            decoded[x][y].g = (f.g + left.g) % 256;
            decoded[x][y].b = (f.b + left.b) % 256;
        }
    }

    // rysujemy wynik w lewym dolnym rogu
    for (int y = 0; y < half_height; y++)
        for (int x = 0; x < half_width; x++)
            setPixel(x, y + half_height,
                     decoded[x][y].r, decoded[x][y].g, decoded[x][y].b);

    SDL_UpdateWindowSurface(window);
}


void decodeFilterType2() {
    int hw = szerokosc / 2;
    int hh = wysokosc / 2;

    SDL_Color decoded[hh][hw];

    for (int y = 0; y < hh; y++) {
        for (int x = 0; x < hw; x++) {

            SDL_Color f = getPixel(x + hw, y);

            SDL_Color up = (y > 0) ? decoded[y-1][x] : SDL_Color{0,0,0,0};

            decoded[y][x].r = (f.r + up.r) % 256;
            decoded[y][x].g = (f.g + up.g) % 256;
            decoded[y][x].b = (f.b + up.b) % 256;
        }
    }

    for (int y = 0; y < hh; y++)
        for (int x = 0; x < hw; x++)
            setPixel(x, y + hh,
                decoded[y][x].r, decoded[y][x].g, decoded[y][x].b);

    SDL_UpdateWindowSurface(window);
}


void decodeFilterType3() {
    int hw = szerokosc / 2;
    int hh = wysokosc / 2;

    SDL_Color decoded[hh][hw];

    for (int y = 0; y < hh; y++) {
        for (int x = 0; x < hw; x++) {

            SDL_Color f = getPixel(x + hw, y);

            SDL_Color left = (x > 0) ? decoded[y][x-1] : SDL_Color{0,0,0,0};
            SDL_Color up = (y > 0) ? decoded[y-1][x] : SDL_Color{0,0,0,0};

            Uint8 pred_r = (left.r + up.r) / 2;
            Uint8 pred_g = (left.g + up.g) / 2;
            Uint8 pred_b = (left.b + up.b) / 2;

            decoded[y][x].r = (f.r + pred_r) % 256;
            decoded[y][x].g = (f.g + pred_g) % 256;
            decoded[y][x].b = (f.b + pred_b) % 256;
        }
    }

    for (int y = 0; y < hh; y++)
        for (int x = 0; x < hw; x++)
            setPixel(x, y + hh,
                decoded[y][x].r, decoded[y][x].g, decoded[y][x].b);

    SDL_UpdateWindowSurface(window);
}


void decodeFilterType4() {
    int hw = szerokosc / 2;
    int hh = wysokosc / 2;

    SDL_Color decoded[hh][hw];

    for (int y = 0; y < hh; y++) {
        for (int x = 0; x < hw; x++) {

            SDL_Color f = getPixel(x + hw, y);

            SDL_Color left = (x > 0) ? decoded[y][x-1] : SDL_Color{0,0,0,0};
            SDL_Color up = (y > 0) ? decoded[y-1][x] : SDL_Color{0,0,0,0};
            SDL_Color up_left  = (x > 0 && y > 0) ? decoded[y-1][x-1] : SDL_Color{0,0,0,0};

            decoded[y][x].r = (f.r + PaethPredictor(left.r, up.r, up_left.r)) % 256;
            decoded[y][x].g = (f.g + PaethPredictor(left.g, up.g, up_left.g)) % 256;
            decoded[y][x].b = (f.b + PaethPredictor(left.b, up.b, up_left.b)) % 256;
        }
    }

    for (int y = 0; y < hh; y++)
        for (int x = 0; x < hw; x++)
            setPixel(x, y + hh,
                decoded[y][x].r, decoded[y][x].g, decoded[y][x].b);

    SDL_UpdateWindowSurface(window);
}


