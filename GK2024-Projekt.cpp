// główny plik projektu
#include "GK2024-Zmienne.h"
#include "GK2024-Funkcje.h"
#include "GK2024-Paleta.h"
#include "GK2024-MedianCut.h"
#include "GK2024-Pliki.h"

#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "tinyfiledialogs.h"
#include <conio.h>
using namespace std;

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    return false;
    }
    SDL_UpdateWindowSurface(window);

    bool endLoop = false;
    SDL_Event event;

    // domyślnie słonecznik się ładuje
    const char* wybranyPlik;
    string nazwaPliku = "obrazek1";
    string rozszerzeniePliku = ".bmp";
    ladujBMP((nazwaPliku + rozszerzeniePliku).c_str(), 0, 0);

    // główna pętla programu
    while (!endLoop) {
        cout << "\n\n\n====================================================" << endl;
        cout << "MENU" << endl;

        // Kolejność tych opcji trzeba będzie zmienić, bo chyba nie zgadzają się z tym co jest w switchu
        //cout << "q. Zaladuj plik" << endl;
        //cout << "c. Konwertuj plik .z22 na .bmp" << endl;
        cout << "1. Paleta narzucona" << endl;
        //cout << "2. Paleta narzucona + dithering" << endl;
        cout << "3. Narzucona skala szarosci" << endl;
        //cout << "4. Narzucona skala szarosci + dithering" << endl;
        cout << "5. Paleta dedykowana" << endl;
        //cout << "6. Paleta dedykowana + dithering" << endl;
        cout << "7. Dedykowana skala szarosci" << endl;
       // cout << "8. Dedykowana skala szarosci + dithering" << endl;
        cout << "9. Paleta wykryta" << endl;
        cout << "0. Wyjscie" << endl;

        cout << "\nWybierz opcje: ";
        char opcja;
        cin >> opcja;
        cout << "====================================================" << endl;

        // filtr do pokazywania konkretnych plików w oknie wyboru
        const char* filters[] = { "*.bmp", "*.z22" };
        const char* z22filter[] = { "*.z22" };
        // sprawdzamy czy pojawiło się zdarzenie
        switch (opcja) {
            /*case 'q':
                wymazPalete();
                // otwórz okno wyboru pliku
                wybranyPlik = tinyfd_openFileDialog("Wybierz plik BMP lub Z22", "", 2, filters, "Pliki BMP lub Z22", 0);
                // jak użytkownik wybierze plik
                if (wybranyPlik) {
                    nazwaPliku = wybranyPlik;
                    if (nazwaPliku.c_str()) {
                        rozszerzeniePliku = getFileExtension(nazwaPliku);

                        cout << "\n\nWybrany plik: " << nazwaPliku << endl;
                        cout << "Rozszerzenie pliku: " << rozszerzeniePliku << endl;

                        // załaduj wybrany plik
                        if (rozszerzeniePliku == ".bmp") {
                            ladujBMP(nazwaPliku.c_str(), 0, 0);
                        } else if (rozszerzeniePliku == ".z22") {
                            odczytajPlik6(getFileName(nazwaPliku));
                            SDL_UpdateWindowSurface(window);
                        } else {
                            cout << "Nie rozpoznano rozszerzenia pliku." << endl;
                        }
                    }
                } else {
                    cout << "Nie wybrano pliku." << endl;
                }
                break;*/
            /*case 'c':
                wymazPalete();
                // otwórz okno wyboru pliku
                wybranyPlik = tinyfd_openFileDialog("Wybierz plik Z22", "", 1, z22filter, "Pliki Z22", 0);
                // jak użytkownik wybierze plik
                if (wybranyPlik) {
                    nazwaPliku = wybranyPlik;
                    if (nazwaPliku.c_str()) {
                        rozszerzeniePliku = getFileExtension(nazwaPliku);

                        cout << "\n\nWybrany plik: " << nazwaPliku << endl;
                        cout << "Rozszerzenie pliku: " << rozszerzeniePliku << endl;

                        // załaduj wybrany plik
                        if (rozszerzeniePliku == ".z22") {
                            konwertujZ22doBMP(getFileName(nazwaPliku));
                        } else if (rozszerzeniePliku == ".z22") {

                            SDL_UpdateWindowSurface(window);
                        } else {
                            cout << "Nie rozpoznano rozszerzenia pliku." << endl;
                        }
                    }
                } else {
                    cout << "Nie wybrano pliku." << endl;
                }
                break;*/
            case '1':
                wymazPalete();
                Funkcja1();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_Narzucona", 1);
                odczytajPlik6(getFileName(nazwaPliku) + "_Narzucona");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Paleta narzucona" << endl;
                break;
            /*case '2':
                wymazPalete();
                //Funkcja2();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_NarzuconaDith", 2);
                odczytajPlik6(getFileName(nazwaPliku) + "_NarzuconaDith");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Paleta narzucona + dithering" << endl;
                break;*/
            case '3':
                wymazPalete();
                Funkcja3();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_NarzuconaBW", 3);
                odczytajPlik6(getFileName(nazwaPliku) + "_NarzuconaBW");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Narzucona skala szarosci" << endl;
                break;
            /*case '4':
                wymazPalete();
                //Funkcja4();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_NarzuconaBWDith", 4);
                odczytajPlik6(getFileName(nazwaPliku) + "_NarzuconaBWDith");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Narzucona skala szarosci + dithering" << endl;
                break;*/
            case '5':
                wymazPalete();
                Funkcja5();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_Dedykowana", 5);
                odczytajPlik6(getFileName(nazwaPliku) + "_Dedykowana");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Paleta dedykowana" << endl;
                break;
            /*case '6':
                wymazPalete();
                //Funkcja6();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_DedykowanaDith", 6);
                odczytajPlik6(getFileName(nazwaPliku) + "_DedykowanaDith");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Paleta dedykowana + dithering" << endl;
                break;*/
            case '7':
                wymazPalete();
                Funkcja7();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_DedykowanaBW", 7);
                odczytajPlik6(getFileName(nazwaPliku) + "_DedykowanaBW");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Dedykowana skala szarosci" << endl;
                break;
            /*case '8':
                wymazPalete();
                //Funkcja8();
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_DedykowanaBWDith", 8);
                odczytajPlik6(getFileName(nazwaPliku) + "_DedykowanaBWDith");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Dedykowana skala szarosci + dithering" << endl;
                break;*/
            case '9':
                wymazPalete();
                if (!Funkcja9())
                    break;
                cout << nazwaPliku << endl;
                zapiszPlik6(getFileName(nazwaPliku) + "_Wykryta", 9);
                odczytajPlik6(getFileName(nazwaPliku) + "_Wykryta");
                SDL_UpdateWindowSurface(window);
                cout << "Wybrano: Paleta wykryta" << endl;
                break;
            case '0':
                endLoop=true;
                system("cls");
                cout << "Koniec programu." << endl;
                break;
            default: czyscEkran(0, 0, 0);
        }
        //system("cls");

    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
    return 0;
}
