
// SM2025-Lab4.cpp
#include "SM2025-Lab4.h"
#include "SM2025-Lab2.h"
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"


// funkcja pomocnicza: bezpieczne sprawdzenie granic dla bloków 2x2
static inline int clamp_int(int v, int low, int high) {
    if (v < low) return low;
    if (v > high) return high;
    return v;
}

void subsampleYUV420()
{
    int half_w = szerokosc / 2;
    int half_h = wysokosc / 2;

    int dest_x = half_w;
    int dest_y = 0;

    for (int by = 0; by < half_h; by += 2) {
        for (int bx = 0; bx < half_w; bx += 2) {

            int block_w = ((bx + 1) < half_w) ? 2 : 1;
            int block_h = ((by + 1) < half_h) ? 2 : 1;
            int count = block_w * block_h;

            float sum_u = 0.0f, sum_v = 0.0f;
            float y_vals[4];
            int idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    int sx = bx + dx;
                    int sy = by + dy;
                    YUV yuv = getYUV(sx, sy);
                    y_vals[idx++] = yuv.y;
                    sum_u += yuv.u;
                    sum_v += yuv.v;
                }
            }
            float avg_u = sum_u / count;
            float avg_v = sum_v / count;

            idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    int sx = bx + dx;
                    int sy = by + dy;
                    float Y = y_vals[idx++];
                    setYUV(dest_x + sx, dest_y + sy, Y, avg_u, avg_v);
                }
            }
        }
    }

}


void subsampleYIQ420()
{
    int half_w = szerokosc / 2;
    int half_h = wysokosc / 2;

    int dest_x = 0;
    int dest_y = half_h;

    for (int by = 0; by < half_h; by += 2) {
        for (int bx = 0; bx < half_w; bx += 2) {

            int block_w = ((bx + 1) < half_w) ? 2 : 1;
            int block_h = ((by + 1) < half_h) ? 2 : 1;
            int count = block_w * block_h;

            float sum_i = 0.0f, sum_q = 0.0f;
            float y_vals[4];
            int idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    int sx = bx + dx;
                    int sy = by + dy;
                    YIQ yiq = getYIQ(sx, sy);
                    y_vals[idx++] = yiq.y;
                    sum_i += yiq.i;
                    sum_q += yiq.q;
                }
            }
            float avg_i = sum_i / count;
            float avg_q = sum_q / count;

            idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    int sx = bx + dx;
                    int sy = by + dy;
                    float Y = y_vals[idx++];
                    setYIQ(dest_x + sx, dest_y + sy, Y, avg_i, avg_q);
                }
            }
        }
    }
}


void subsampleYCbCr420()
{
    int half_w = szerokosc / 2;
    int half_h = wysokosc / 2;

    int dest_x = half_w;
    int dest_y = half_h;

    for (int by = 0; by < half_h; by += 2) {
        for (int bx = 0; bx < half_w; bx += 2) {

            int block_w = ((bx + 1) < half_w) ? 2 : 1;
            int block_h = ((by + 1) < half_h) ? 2 : 1;
            int count = block_w * block_h;

            float sum_cb = 0.0f, sum_cr = 0.0f;
            float y_vals[4];
            int idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    int sx = bx + dx;
                    int sy = by + dy;
                    YCbCr ycc = getYCbCr(sx, sy);
                    y_vals[idx++] = ycc.y;
                    sum_cb += ycc.cb;
                    sum_cr += ycc.cr;
                }
            }
            float avg_cb = sum_cb / count;
            float avg_cr = sum_cr / count;

            idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    int sx = bx + dx;
                    int sy = by + dy;
                    float Y = y_vals[idx++];
                    setYCbCr(dest_x + sx, dest_y + sy, Y, avg_cb, avg_cr);
                }
            }
        }
    }
}


void subsampleHSL420_H()
{
    int half_w = szerokosc / 2;
    int half_h = wysokosc / 2;
    int dest_x = half_w;
    int dest_y = 0;

    for (int by = 0; by < half_h; by += 2) {
        for (int bx = 0; bx < half_w; bx += 2) {

            int block_w = ((bx + 1) < half_w) ? 2 : 1;
            int block_h = ((by + 1) < half_h) ? 2 : 1;
            int count = block_w * block_h;

            float sum_h = 0.0f;
            float s_vals[4], l_vals[4];
            int idx = 0;

            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    HSL hsl = getHSL(bx + dx, by + dy);
                    sum_h += hsl.h;
                    s_vals[idx] = hsl.s;
                    l_vals[idx] = hsl.l;
                    idx++;
                }
            }

            float avg_h = sum_h / count;

            idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    float S = s_vals[idx];
                    float L = l_vals[idx];
                    idx++;
                    setHSL(dest_x + bx + dx, dest_y + by + dy, avg_h, S, L);
                }
            }
        }
    }
}


void subsampleHSL420_L()
{
    int half_w = szerokosc / 2;
    int half_h = wysokosc / 2;
    int dest_x = 0;
    int dest_y = half_h;

    for (int by = 0; by < half_h; by += 2) {
        for (int bx = 0; bx < half_w; bx += 2) {

            int block_w = ((bx + 1) < half_w) ? 2 : 1;
            int block_h = ((by + 1) < half_h) ? 2 : 1;
            int count = block_w * block_h;

            float sum_l = 0.0f;
            float h_vals[4], s_vals[4];
            int idx = 0;

            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    HSL hsl = getHSL(bx + dx, by + dy);
                    sum_l += hsl.l;
                    h_vals[idx] = hsl.h;
                    s_vals[idx] = hsl.s;
                    idx++;
                }
            }

            float avg_l = sum_l / count;

            idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    float H = h_vals[idx];
                    float S = s_vals[idx];
                    idx++;
                    setHSL(dest_x + bx + dx, dest_y + by + dy, H, S, avg_l);
                }
            }
        }
    }
}


void subsampleHSL420_S()
{
    int half_w = szerokosc / 2;
    int half_h = wysokosc / 2;
    int dest_x = half_w;
    int dest_y = half_h;

    for (int by = 0; by < half_h; by += 2) {
        for (int bx = 0; bx < half_w; bx += 2) {

            int block_w = ((bx + 1) < half_w) ? 2 : 1;
            int block_h = ((by + 1) < half_h) ? 2 : 1;
            int count = block_w * block_h;

            float sum_s = 0.0f;
            float h_vals[4], l_vals[4];
            int idx = 0;

            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    HSL hsl = getHSL(bx + dx, by + dy);
                    sum_s += hsl.s;
                    h_vals[idx] = hsl.h;
                    l_vals[idx] = hsl.l;
                    idx++;
                }
            }

            float avg_s = sum_s / count;

            idx = 0;
            for (int dy = 0; dy < block_h; ++dy) {
                for (int dx = 0; dx < block_w; ++dx) {
                    float H = h_vals[idx];
                    float L = l_vals[idx];
                    idx++;
                    setHSL(dest_x + bx + dx, dest_y + by + dy, H, avg_s, L);
                }
            }
        }
    }
}





void FunkcjaLab4()
{
    subsampleYUV420();
    subsampleYIQ420();
    subsampleYCbCr420();

    SDL_UpdateWindowSurface(window);
}

void FunkcjaLab4_2(){
    subsampleHSL420_H();
    subsampleHSL420_L();
    subsampleHSL420_S();
    SDL_UpdateWindowSurface(window);
};
