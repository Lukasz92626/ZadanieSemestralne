#include <iostream>
#include <fstream>

#include "definicje.hpp"

using namespace std;

/*	Otwiera podany plik i sprawdza czy sie to powiodlo.
*	nazwa_pliku - nazwa otwieranego pliku
*	tryb_wypisywania - tryb wypisywania komunikatow
*	return strumien - strumien otwartego pliku
*/

ifstream otworz_plik(char nazwa_pliku[], bool tryb_wypisywania) {
	ifstream strumien(nazwa_pliku);
	if (!strumien) {
		printf("Blad otwarcia pliku %s.\n", nazwa_pliku);
	}
	else if (tryb_wypisywania) {
		printf("Plik %s zostal otwarty.\n", nazwa_pliku);
	}
	return strumien;
}

/*	Sprawdza czy plik da sie otworzyc.
*	nazwa_pliku - nazwa otwieranego pliku
*	return 0 - gdy nie powiodlo sie, 1 - gdy sie powiodlo
*/

int sprawdz_plik(char nazwa_pliku[]) {
	ifstream strumien_test(nazwa_pliku); //strumien testowanego pliku
	if (!strumien_test) {
		printf("Blad otwarcia pliku %s.\n", nazwa_pliku);
		return 0;
	}
	strumien_test.seekg(0, ios::end);
	if (strumien_test.tellg() == 0) {
		printf("Plik %s jest pusty.\n", nazwa_pliku);
		strumien_test.close();
		return 0;
	}
	strumien_test.close();
	return 1;
}

/*	Liczy dlugosc pliku podanego przez uzytkownika.
*	nazwa_pliku - nazwa sprawdzanego pliku
*	return dlugosc - ilosc linii w pliku
*/

int licz_dl_pliku_hasla(char nazwa_pliku[]) {
	ifstream strumien; //strumien otwartego pliku
	char test_haslo[DL_HASLA]; //testowe wczytywanie hasel
	char test_kategoria[DL_KATEGORIA]; //testowa kategoria
	int dlugosc = 0; //dlgosc pliku
	if (sprawdz_plik(nazwa_pliku) == 0) {
		//printf("Blad otwarcia pliku %s.\n", nazwa_pliku);
		return 0;
	}
	strumien = otworz_plik(nazwa_pliku, false);
	while (!strumien.eof()) {
		strumien >> test_haslo;
		strumien >> test_kategoria;
		++dlugosc;
	}
	strumien.close();
	return dlugosc;
}