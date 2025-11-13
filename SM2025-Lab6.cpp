#include "SM2025-Lab6.h"
#include <iostream>
#include <fstream>      // dodane do zapisu pliku
#include "GK2024-Zmienne.h"

int ByteRunKompresja(int wejscie[], int dlugosc, const std::string& nazwaPliku);

void byteRun() {
    int nieskompresowane[] = {
        0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 8, 8, 8, 8, 8, 2, 2, 1, 3
    };
    int dlugosc = 24;

    std::cout << "wejscie: " << std::endl;
    for (int c = 0; c < dlugosc; c++)
        std::cout << nieskompresowane[c] << ", ";
    std::cout << "\n";

    std::string plikWyjsciowy = "wynik_kompresji.txt";

    std::cout << "skompresowane wyjscie (ByteRun):" << std::endl;
    int rozmiarPoKompresji = ByteRunKompresja(nieskompresowane, dlugosc, plikWyjsciowy);

    std::cout << "\n\nWynik zapisano do pliku: " << plikWyjsciowy << std::endl;
    std::cout << "Rozmiar przed kompresj¹: " << dlugosc << " bajtów" << std::endl;
    std::cout << "Rozmiar po kompresji:   " << rozmiarPoKompresji << " bajtów" << std::endl;
    std::cout << "Stopieñ kompresji:      "
              << (100.0 * (1.0 - (double)rozmiarPoKompresji / dlugosc))
              << "%\n";

    SDL_UpdateWindowSurface(window);
}


int ByteRunKompresja(int wejscie[], int dlugosc, const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "B³¹d: nie mo¿na otworzyæ pliku do zapisu!" << std::endl;
        return 0;
    }

    int i = 0;
    int licznikWyniku = 0; // liczba bajtów po kompresji

    while (i < dlugosc) {
        // --- Sekwencja powtórzeñ ---
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])) {
            int j = 0;
            while ((i + j < dlugosc - 1) &&
                   (wejscie[i + j] == wejscie[i + 1 + j]) &&
                   (j < 127)) {
                j++;
            }

            int licznik = -j;
            int wartosc = wejscie[i];

            std::cout << "(" << licznik << "), " << wartosc << ", ";
            plik << "(" << licznik << "), " << wartosc << ", ";

            licznikWyniku += 2; // (licznik + wartoœæ)
            i += (j + 1);
        }
        // --- Sekwencja unikalnych wartoœci ---
        else {
            int j = 0;
            while ((i + j < dlugosc - 1) &&
                   (wejscie[i + j] != wejscie[i + 1 + j]) &&
                   (j < 128)) {
                j++;
            }

            if ((i + j == dlugosc - 1) && (j < 128)) {
                j++;
            }

            std::cout << "(" << (j - 1) << "), ";
            plik << "(" << (j - 1) << "), ";

            licznikWyniku++; // bajt licznika

            for (int k = 0; k < j; k++) {
                std::cout << wejscie[i + k] << ", ";
                plik << wejscie[i + k] << ", ";
                licznikWyniku++; // ka¿dy bajt danych
            }

            i += j;
        }
    }

    plik.close();
    return licznikWyniku; // zwracamy rozmiar po kompresji
}
