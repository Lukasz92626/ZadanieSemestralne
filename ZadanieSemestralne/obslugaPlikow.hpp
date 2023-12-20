#include <iostream>
using namespace std;

#ifndef obslugaPlikow_hpp
#define obslugaPlikow_hpp
ifstream otworz_plik(char nazwa_pliku[], bool tryb_wypisywania);
int sprawdz_plik(char nazwa_pliku[]);
int licz_dl_pliku_hasla(char nazwa_pliku[]);
#endif