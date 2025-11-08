
// podstawowe funkcje
#include "GK2024-Funkcje.h"
#include "GK2024-Zmienne.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"

struct YUV
{
    float y;
    float u;
    float v;
};


struct YIQ
{
    float y;
    float i;
    float q;
};

struct YCbCr
{
    float y;
    float cb;
    float cr;
};

struct HSL
{
    float h;
    float s;
    float l;
};

Uint8 yuv_to_r(float y, float u, float v)
{
    float r = y + 1.13983f * v;

    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;

    return static_cast<Uint8>(std::round(r * 255.0f));
}

Uint8 yuv_to_g(float y, float u, float v)
{
    float g = y - 0.39465f * u - 0.58060f * v;

    if (g < 0.0f) g = 0.0f;
    if (g > 1.0f) g = 1.0f;

    return static_cast<Uint8>(std::round(g * 255.0f));
}

Uint8 yuv_to_b(float y, float u, float v)
{
    float b = y + 2.03211f * u;

    if (b < 0.0f) b = 0.0f;
    if (b > 1.0f) b = 1.0f;

    return static_cast<Uint8>(std::round(b * 255.0f));
}



Uint8 yiq_to_red_rgb(float y, float i, float q)
{
    constexpr float RGB_MAX_VALUE = 255.0;
    constexpr float RGB_MIN_VALUE = 0;
    float red = y + i * 0.956 + q * 0.619;
    red *= RGB_MAX_VALUE;

    if(red > RGB_MAX_VALUE)
        red = RGB_MAX_VALUE;

    if(red < RGB_MIN_VALUE)
        red = RGB_MIN_VALUE;

    red = std::roundf(red);

    return static_cast<Uint8>(red);
}

Uint8 yiq_to_green_rgb(float y, float i, float q)
{
    constexpr float RGB_MAX_VALUE = 255.0;
    constexpr float RGB_MIN_VALUE = 0.0;
    float green = y - i * 0.272 - q * 0.647;
    green *= RGB_MAX_VALUE;

    if(green > RGB_MAX_VALUE)
        green = RGB_MAX_VALUE;

    if(green < RGB_MIN_VALUE)
        green = RGB_MIN_VALUE;

    green = std::roundf(green);

    return static_cast<Uint8>(green);
}

Uint8 yiq_to_blue_rgb(float y, float i, float q)
{
    constexpr float RGB_MAX_VALUE = 255.0;
    constexpr float RGB_MIN_VALUE = 0.0;
    float blue = y - i * 1.106 + q * 1.703;
    blue *= RGB_MAX_VALUE;

    if(blue > RGB_MAX_VALUE)
        blue = RGB_MAX_VALUE;

    if(blue < RGB_MIN_VALUE)
        blue = RGB_MIN_VALUE;

    blue = std::roundf(blue);

    return static_cast<Uint8>(blue);
}

Uint8 ycbcr_to_r(float y, float cb, float cr)
{
    float r = y + 1.402f * cr;
    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;
    return static_cast<Uint8>(std::round(r * 255.0f));
}

Uint8 ycbcr_to_g(float y, float cb, float cr)
{
    float g = y - 0.344136f * cb - 0.714136f * cr;
    if (g < 0.0f) g = 0.0f;
    if (g > 1.0f) g = 1.0f;
    return static_cast<Uint8>(std::round(g * 255.0f));
}

Uint8 ycbcr_to_b(float y, float cb, float cr)
{
    float b = y + 1.772f * cb;
    if (b < 0.0f) b = 0.0f;
    if (b > 1.0f) b = 1.0f;
    return static_cast<Uint8>(std::round(b * 255.0f));
}

float hue_to_rgb(float p, float q, float t)
{
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}


Uint8 hsl_to_r(float h, float s, float l)
{
    h /= 360.0f;
    float r, g, b;

    if (s == 0.0f)
        r = g = b = l;
    else {
        float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
        float p = 2.0f * l - q;
        r = hue_to_rgb(p, q, h + 1.0f / 3.0f);
    }

    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;
    return static_cast<Uint8>(std::round(r * 255.0f));
}

Uint8 hsl_to_g(float h, float s, float l)
{
    h /= 360.0f;
    float r, g, b;

    if (s == 0.0f)
        r = g = b = l;
    else {
        float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
        float p = 2.0f * l - q;
        g = hue_to_rgb(p, q, h);
    }

    if (g < 0.0f) g = 0.0f;
    if (g > 1.0f) g = 1.0f;
    return static_cast<Uint8>(std::round(g * 255.0f));
}

Uint8 hsl_to_b(float h, float s, float l)
{
    h /= 360.0f;
    float r, g, b;

    if (s == 0.0f)
        r = g = b = l;
    else {
        float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
        float p = 2.0f * l - q;
        b = hue_to_rgb(p, q, h - 1.0f / 3.0f);
    }

    if (b < 0.0f) b = 0.0f;
    if (b > 1.0f) b = 1.0f;
    return static_cast<Uint8>(std::round(b * 255.0f));
}


float rgb_to_y_yuv(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    return 0.299f * rf + 0.587f * gf + 0.114f * bf;
}

float rgb_to_u_yuv(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    return -0.14713f * rf - 0.28886f * gf + 0.436f * bf;
}

float rgb_to_v_yuv(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    return 0.615f * rf - 0.51499f * gf - 0.10001f * bf;
}


float rgb_to_y_yiq(Uint8 red, Uint8 green, Uint8 blue)
{
    constexpr float Y_MAX_VALUE = 1.0;
    constexpr float Y_MIN_VALUE = 0.0;
    constexpr float RGB_MAX_VALUE = 255.0;
    float red_0_to_1 = red / RGB_MAX_VALUE;
    float green_0_to_1 = green / RGB_MAX_VALUE;
    float blue_0_to_1 = blue / RGB_MAX_VALUE;
    float y = red_0_to_1 * 0.299 + green_0_to_1 * 0.587 + blue_0_to_1 * 0.114;

    if(y > Y_MAX_VALUE)
        return Y_MAX_VALUE;

    if(y < Y_MIN_VALUE)
        return Y_MIN_VALUE;

    return y;
}

float rgb_to_i_yiq(Uint8 red, Uint8 green, Uint8 blue)
{
    constexpr float I_MAX_VALUE = 0.5959;
    constexpr float I_MIN_VALUE = -0.5959;
    constexpr float RGB_MAX_VALUE = 255.0;
    float red_0_to_1 = red / RGB_MAX_VALUE;
    float green_0_to_1 = green / RGB_MAX_VALUE;
    float blue_0_to_1 = blue / RGB_MAX_VALUE;
    float i = red_0_to_1 * 0.5959 - green_0_to_1 * 0.2746 - blue_0_to_1 * 0.3213;

    if(i > I_MAX_VALUE)
        return I_MAX_VALUE;

    if(i < I_MIN_VALUE)
        return I_MIN_VALUE;

    return i;
}

float rgb_to_q_yiq(Uint8 red, Uint8 green, Uint8 blue)
{
    constexpr float Q_MAX_VALUE = 0.5227;
    constexpr float Q_MIN_VALUE = -0.5227;
    constexpr float RGB_MAX_VALUE = 255.0;
    float red_0_to_1 = red / RGB_MAX_VALUE;
    float green_0_to_1 = green / RGB_MAX_VALUE;
    float blue_0_to_1 = blue / RGB_MAX_VALUE;
    float q = red_0_to_1 * 0.2115 + green_0_to_1 * -0.5227 + blue_0_to_1 * 0.3112;

    if(q > Q_MAX_VALUE)
        return Q_MAX_VALUE;

    if(q < Q_MIN_VALUE)
        return Q_MIN_VALUE;

    return q;
}

float rgb_to_y_ycbcr(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    return 0.299f * rf + 0.587f * gf + 0.114f * bf;
}

float rgb_to_cb_ycbcr(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    return -0.168736f * rf - 0.331264f * gf + 0.5f * bf;
}

float rgb_to_cr_ycbcr(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    return 0.5f * rf - 0.418688f * gf - 0.081312f * bf;
}

float rgb_to_h_hsl(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max_val = rf;
    if (gf > max_val) max_val = gf;
    if (bf > max_val) max_val = bf;

    float min_val = rf;
    if (gf < min_val) min_val = gf;
    if (bf < min_val) min_val = bf;

    float delta = max_val - min_val;
    float h = 0.0f;

    if (delta == 0.0f)
        h = 0.0f;
    else if (max_val == rf)
        h = 60.0f * fmod(((gf - bf) / delta), 6.0f);
    else if (max_val == gf)
        h = 60.0f * (((bf - rf) / delta) + 2.0f);
    else
        h = 60.0f * (((rf - gf) / delta) + 4.0f);

    if (h < 0.0f) h += 360.0f;
    return h;
}

float rgb_to_s_hsl(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max_val = rf;
    if (gf > max_val) max_val = gf;
    if (bf > max_val) max_val = bf;

    float min_val = rf;
    if (gf < min_val) min_val = gf;
    if (bf < min_val) min_val = bf;

    float delta = max_val - min_val;
    float l = (max_val + min_val) / 2.0f;

    if (delta == 0.0f)
        return 0.0f;

    return delta / (1.0f - fabs(2.0f * l - 1.0f));
}

float rgb_to_l_hsl(Uint8 r, Uint8 g, Uint8 b)
{
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max_val = rf;
    if (gf > max_val) max_val = gf;
    if (bf > max_val) max_val = bf;

    float min_val = rf;
    if (gf < min_val) min_val = gf;
    if (bf < min_val) min_val = bf;

    return (max_val + min_val) / 2.0f;
}

void setYUV(int x, int y, float y_val, float u_val, float v_val)
{
    Uint8 r = yuv_to_r(y_val, u_val, v_val);
    Uint8 g = yuv_to_g(y_val, u_val, v_val);
    Uint8 b = yuv_to_b(y_val, u_val, v_val);

    setPixel(x, y, r, g, b);
}


void setYIQ(int xx, int yy, float y, float i, float q)
{
    Uint8 red = yiq_to_red_rgb(y, i, q);
    Uint8 green = yiq_to_green_rgb(y, i, q);
    Uint8 blue = yiq_to_blue_rgb(y, i, q);

    //std::cout << red << " " << green << " " << blue;
    //cout<< xx << " " << yy <<endl;
    setPixel(xx, yy, red, green, blue);
}

void setYCbCr(int x, int y, float y_val, float cb, float cr)
{
    Uint8 r = ycbcr_to_r(y_val, cb, cr);
    Uint8 g = ycbcr_to_g(y_val, cb, cr);
    Uint8 b = ycbcr_to_b(y_val, cb, cr);

    setPixel(x, y, r, g, b);
}

void setHSL(int x, int y, float h, float s, float l)
{
    Uint8 r = hsl_to_r(h, s, l);
    Uint8 g = hsl_to_g(h, s, l);
    Uint8 b = hsl_to_b(h, s, l);

    setPixel(x, y, r, g, b);
}

YUV getYUV(int x, int y)
{
    SDL_Color color = getPixel(x, y);
    YUV yuv;

    yuv.y = rgb_to_y_yuv(color.r, color.g, color.b);
    yuv.u = rgb_to_u_yuv(color.r, color.g, color.b);
    yuv.v = rgb_to_v_yuv(color.r, color.g, color.b);

    return yuv;
}

YIQ getYIQ(int xx, int yy)
{
    SDL_Color pixel_colour = getPixel(xx, yy);
    YIQ yiq;
    yiq.y = rgb_to_y_yiq(pixel_colour.r, pixel_colour.g, pixel_colour.b);
    yiq.i = rgb_to_i_yiq(pixel_colour.r, pixel_colour.g, pixel_colour.b);
    yiq.q = rgb_to_q_yiq(pixel_colour.r, pixel_colour.g, pixel_colour.b);

    return yiq;
}

YCbCr getYCbCr(int x, int y)
{
    SDL_Color color = getPixel(x, y);
    YCbCr ycc;
    ycc.y  = rgb_to_y_ycbcr(color.r, color.g, color.b);
    ycc.cb = rgb_to_cb_ycbcr(color.r, color.g, color.b);
    ycc.cr = rgb_to_cr_ycbcr(color.r, color.g, color.b);
    return ycc;
}



HSL getHSL(int x, int y)
{
    SDL_Color color = getPixel(x, y);
    HSL hsl;
    hsl.h = rgb_to_h_hsl(color.r, color.g, color.b);
    hsl.s = rgb_to_s_hsl(color.r, color.g, color.b);
    hsl.l = rgb_to_l_hsl(color.r, color.g, color.b);
    return hsl;
}

void rysujPixelYUV() {
    float y, u, v;
    int x_coord, y_coord;

    std::cout << "Podaj Y (0.0 - 1.0): ";
    std::cin >> y;
    std::cout << "Podaj U (-0.436 - 0.436): ";
    std::cin >> u;
    std::cout << "Podaj V (-0.615 - 0.615): ";
    std::cin >> v;

    std::cout << "Podaj wspolrzedne x: ";
    std::cin >> x_coord;
    std::cout << "Podaj wspolrzedne y: ";
    std::cin >> y_coord;

    setYUV(x_coord, y_coord, y, u, v);

    /*for(int row = 10; row < 100; row++)
    {
        for(int column = 10; column < 100; column++)
        {
            setYUV(row, column, y, u, v);
        }
    }*/

    SDL_UpdateWindowSurface(window);
}


void przerysujObrazYUV() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            // pobranie koloru
            SDL_Color color = getPixel(x, y);

            // konwersja RGB na YUV
            float y_val = rgb_to_y_yuv(color.r, color.g, color.b);
            float u_val = rgb_to_u_yuv(color.r, color.g, color.b);
            float v_val = rgb_to_v_yuv(color.r, color.g, color.b);

            // ustawienie koloru
            setYUV(x + half_width, y, y_val, u_val, v_val);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void rysujPixelYIQ() {

    float y = 0.0;
    float i = 0.0;
    float q = 0.0;
    int x_coordinates = 0;
    int y_coordinates = 0;

    std::cout << "Podaj Y: (0.0 - 1.0): ";
    std::cin >> y;
    std::cout << "Podaj I: (-0.5959 - 0.5959): ";
    std::cin >> i;
    std::cout << "Podaj Q: (-0.5227 - 0.5227): ";
    std::cin >> q;

    std::cout << "Podaj wspolrzedne x: ";
    std::cin >> x_coordinates;
    std::cout << "Podaj wspolrzedne y: ";
    std::cin >> y_coordinates;

    setYIQ(x_coordinates, y_coordinates, y, i, q);

    // Do debugowania

    /*for(int row = 10; row < 100; row++)
    {
        for(int column = 10; column < 100; column++)
        {
            setYIQ(row, column, y, i, q);
        }
    }*/


    SDL_UpdateWindowSurface(window);
}

void przerysujObrazYIQ() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            // pobranie koloru
            SDL_Color color = getPixel(x, y);

            // konwersja RGB na YIQ
            float y_val = rgb_to_y_yiq(color.r, color.g, color.b);
            float i_val = rgb_to_i_yiq(color.r, color.g, color.b);
            float q_val = rgb_to_q_yiq(color.r, color.g, color.b);

            // ustawienie koloru
            setYIQ(x + half_width, y, y_val, i_val, q_val);
        }
    }

    SDL_UpdateWindowSurface(window);
}


void rysujPixelYCbCr() {
    float y, cb, cr;
    int x_coord, y_coord;

    std::cout << "Podaj Y (0.0 - 1.0): ";
    std::cin >> y;
    std::cout << "Podaj Cb (-0.5 - 0.5): ";
    std::cin >> cb;
    std::cout << "Podaj Cr (-0.5 - 0.5): ";
    std::cin >> cr;


    std::cout << "Podaj wspolrzedne x: ";
    std::cin >> x_coord;
    std::cout << "Podaj wspolrzedne y: ";
    std::cin >> y_coord;

    setYCbCr(x_coord, y_coord, y, cb, cr);

    /*for(int row = 10; row < 100; row++)
    {
        for(int column = 10; column < 100; column++)
        {
            setYCbCr(row, column, y, cb, cr);
        }
    }*/

    SDL_UpdateWindowSurface(window);
}


void przerysujObrazYCbCr() {
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            // pobranie koloru
            SDL_Color color = getPixel(x, y);

            // konwersja RGB na YCbCr
            float y_val = rgb_to_y_ycbcr(color.r, color.g, color.b);
            float cb_val = rgb_to_cb_ycbcr(color.r, color.g, color.b);
            float cr_val = rgb_to_cr_ycbcr(color.r, color.g, color.b);

            // ustawienie koloru
            setYCbCr(x + half_width, y, y_val, cb_val, cr_val);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void rysujPixelHSL()
{
    float h, s, l;
    int x_coord, y_coord;

    std::cout << "Podaj H (0 - 360): ";
    std::cin >> h;
    std::cout << "Podaj S (0.0 - 1.0): ";
    std::cin >> s;
    std::cout << "Podaj L (0.0 - 1.0): ";
    std::cin >> l;

    std::cout << "Podaj wspolrzedne x: ";
    std::cin >> x_coord;
    std::cout << "Podaj wspolrzedne y: ";
    std::cin >> y_coord;

    setHSL(x_coord, y_coord, h, s, l);
    SDL_UpdateWindowSurface(window);
}



void przerysujObrazHSL()
{
    int half_width = szerokosc / 2;
    int half_height = wysokosc / 2;

    for (int y = 0; y < half_height; y++)
    {
        for (int x = 0; x < half_width; x++)
        {
            SDL_Color color = getPixel(x, y);

            float h = rgb_to_h_hsl(color.r, color.g, color.b);
            float s = rgb_to_s_hsl(color.r, color.g, color.b);
            float l = rgb_to_l_hsl(color.r, color.g, color.b);

            setHSL(x + half_width, y, h, s, l);
        }
    }

    SDL_UpdateWindowSurface(window);
}

