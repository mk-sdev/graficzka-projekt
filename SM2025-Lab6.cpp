#include "SM2025-Lab6.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "GK2024-Zmienne.h"

int ByteRunKompresja(int wejscie[], int dlugosc, const std::string& nazwaPliku);

int ByteRunKompresja(int wejscie[], int dlugosc, const std::string& nazwaPliku);
std::vector<int> ByteRunDekompresja(const std::string& nazwaPliku);

void byteRun() {
    int nieskompresowane[] = {
        0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 2, 2, 1, 3
    };
    int dlugosc = 24;

    std::cout << "Wejscie: " << std::endl;
    for (int c = 0; c < dlugosc; c++)
        std::cout << nieskompresowane[c] << ", ";
    std::cout << "\n\n";

    std::string plikWyjsciowy = "wynik_kompresji.txt";

    std::cout << "Skompresowane wyjœcie (ByteRun):" << std::endl;
    int rozmiarPoKompresji = ByteRunKompresja(nieskompresowane, dlugosc, plikWyjsciowy);

    std::cout << "\n\nWynik zapisano do pliku: " << plikWyjsciowy << std::endl;
    std::cout << "Rozmiar przed kompresja: " << dlugosc << " bajtow" << std::endl;
    std::cout << "Rozmiar po kompresji:   " << rozmiarPoKompresji << " bajtow" << std::endl;
    std::cout << "Stopien kompresji:      "
              << (100.0 * (1.0 - (double)rozmiarPoKompresji / dlugosc))
              << "%\n\n";

    // dekompresja
    std::vector<int> zdekompresowane = ByteRunDekompresja(plikWyjsciowy);

    std::cout << "Zdekompresowane dane:" << std::endl;
    for (int val : zdekompresowane)
        std::cout << val << ", ";
    std::cout << "\n";

    SDL_UpdateWindowSurface(window);
}


int ByteRunKompresja(int wejscie[], int dlugosc, const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Blad: nie mozna otworzyæ pliku do zapisu" << std::endl;
        return 0;
    }

    int i = 0;
    int licznikWyniku = 0; // liczba bajtow po kompresji

    while (i < dlugosc) {
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

            licznikWyniku += 2; // licznik + wartosc
            i += (j + 1);
        }
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
                licznikWyniku++; // kazdy bajt danych
            }

            i += j;
        }
    }

    plik.close();
    return licznikWyniku;
}


std::vector<int> ByteRunDekompresja(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    std::vector<int> wynik;

    if (!plik.is_open()) {
        std::cerr << "Blad: nie mo¿na otworzyæ pliku do odczytu!" << std::endl;
        return wynik;
    }

    std::string linia;
    std::stringstream ss;
    while (std::getline(plik, linia))
        ss << linia; // scalenie wszystkich lini do jednego strurmienia

    std::string token;
    int licznik = 0;
    bool oczekujeLiczby = false;

    while (std::getline(ss, token, ',')) {
        // usuniecie spacji
        while (!token.empty() && (token.front() == ' ' || token.front() == '\t'))
            token.erase(token.begin());
        while (!token.empty() && (token.back() == ' ' || token.back() == '\t'))
            token.pop_back();

        if (token.empty()) continue;

        //jesli token zaczyna siê od "(" - to licznik
        if (token.front() == '(') {
            size_t pos = token.find(')');
            std::string licznikStr = token.substr(1, pos - 1);
            licznik = std::stoi(licznikStr);
            oczekujeLiczby = true;
        } else if (oczekujeLiczby) {
            int wartosc = std::stoi(token);
            if (licznik < 0) {
                // sekwencja powtorzen
                int powtorzenia = -licznik + 1;
                for (int i = 0; i < powtorzenia; i++)
                    wynik.push_back(wartosc);
            } else {
                // sekewncja roznych wartosci
                wynik.push_back(wartosc);
                licznik--;
                // wczytaj kolejne liczby w tej sekwencji
                while (licznik >= 0 && std::getline(ss, token, ',')) {
                    while (!token.empty() && (token.front() == ' ' || token.front() == '\t'))
                        token.erase(token.begin());
                    while (!token.empty() && (token.back() == ' ' || token.back() == '\t'))
                        token.pop_back();
                    if (token.empty()) continue;

                    int wartosc2 = std::stoi(token);
                    wynik.push_back(wartosc2);
                    licznik--;
                }
            }
            oczekujeLiczby = false;
        }
    }

    plik.close();
    return wynik;
}
