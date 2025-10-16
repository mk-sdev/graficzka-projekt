// funkcje do operacji na plikach
#ifndef GK2024_PLIKI_H_INCLUDED
#define GK2024_PLIKI_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <fstream>
#include <SDL2/SDL.h>

void zapiszPlik6(string nazwaObrazka, int opcja);
void odczytajPlik6(string nazwaObrazka);

void zapiszObraz6(ofstream& wyjscie);
void zapiszPalete6(ofstream& wyjscie, SDL_Color paleta[], int rozmiar);

void odczytajObraz6(ifstream& wejscie, Uint16 szerokoscObrazka, Uint16 wysokoscObrazka, int opcja);
void odczytajPalete6(ifstream& wejscie);

string getFileName(const string& filePath);
string getFileExtension(const string& filePath);

//void zapiszJakoBMP(const string& fileName, SDL_Surface* surface);
//void konwertujZ22doBMP(const string& fileName);

#endif // GK2024_PLIKI_H_INCLUDED
