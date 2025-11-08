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

// ========================= FILTRY =========================
Uint8 FilterNone(Uint8 raw) {
    return raw;
}

Uint8 FilterSub(Uint8 raw, Uint8 left) {
    return (raw - left) % 256;
}

Uint8 FilterUp(Uint8 raw, Uint8 upper) {
    return (raw - upper) % 256;
}

Uint8 FilterAverage(Uint8 raw, Uint8 left, Uint8 upper) {
    return (raw - ((left + upper) / 2)) % 256;
}

Uint8 FilterPaeth(Uint8 raw, Uint8 left, Uint8 upper, Uint8 upper_left) {
    Uint8 paeth = PaethPredictor(left, upper, upper_left);
    return (raw - paeth) % 256;
}

// ========================= TESTY / WIZUALIZACJA =========================
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


// ========================== DEKODOWANIE FILTRÓW ==========================

void decodeFilterType1() { // Sub
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = half_width; x < szerokosc; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color left = (x > half_width) ? getPixel(x - 1, y) : SDL_Color{0,0,0,0};

            SDL_Color out;
            out.r = (c.r + left.r) % 256;
            out.g = (c.g + left.g) % 256;
            out.b = (c.b + left.b) % 256;

            // przerysowujemy do dolnej lewej æwiartki
            setPixel(x - half_width, y + half_height, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void decodeFilterType2() { // Up
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = half_width; x < szerokosc; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color up = (y > 0) ? getPixel(x, y - 1) : SDL_Color{0,0,0,0};

            SDL_Color out;
            out.r = (c.r + up.r) % 256;
            out.g = (c.g + up.g) % 256;
            out.b = (c.b + up.b) % 256;

            setPixel(x - half_width, y + half_height, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void decodeFilterType3() { // Average
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = half_width; x < szerokosc; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color left = (x > half_width) ? getPixel(x - 1, y) : SDL_Color{0,0,0,0};
            SDL_Color up = (y > 0) ? getPixel(x, y - 1) : SDL_Color{0,0,0,0};

            SDL_Color out;
            out.r = (c.r + ((left.r + up.r) / 2)) % 256;
            out.g = (c.g + ((left.g + up.g) / 2)) % 256;
            out.b = (c.b + ((left.b + up.b) / 2)) % 256;

            setPixel(x - half_width, y + half_height, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void decodeFilterType4() { // Paeth
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = half_width; x < szerokosc; x++) {
            SDL_Color c = getPixel(x, y);
            SDL_Color left = (x > half_width) ? getPixel(x - 1, y) : SDL_Color{0,0,0,0};
            SDL_Color up = (y > 0) ? getPixel(x, y - 1) : SDL_Color{0,0,0,0};
            SDL_Color up_left = (x > half_width && y > 0) ? getPixel(x - 1, y - 1) : SDL_Color{0,0,0,0};

            SDL_Color out;
            out.r = (c.r + PaethPredictor(left.r, up.r, up_left.r)) % 256;
            out.g = (c.g + PaethPredictor(left.g, up.g, up_left.g)) % 256;
            out.b = (c.b + PaethPredictor(left.b, up.b, up_left.b)) % 256;

            setPixel(x - half_width, y + half_height, out.r, out.g, out.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

