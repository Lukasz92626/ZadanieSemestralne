#include <iostream>

#ifndef UZYTKOWNIK_CPP
#define UZYTKOWNIK_CPP

#include "gracz.cpp"

#include "obslugaGry.hpp"

class Uzytkownik : public Gracz {
private:
	/*	wczytuje od uzytkownika litere.
	*/

	char wczytaj_litera() {
		char znak = '0'; //wczytywany znak
		while (scanf_s("%c", &znak, 1) != 1 || !((znak >= 'a' && znak <= 'z') || (znak >= 'A' && znak <= 'Z')) || getchar() != '\n') {
			printf("Podany znak nie jest litera. Popraw: ");
			while (getchar() != '\n')
				;
		}
		return znak;
	}
public:
	Uzytkownik() : Gracz() {
		;
	}
	Uzytkownik(int nile_niepowodzen_gracza, int nile_liter_trafiono, int ntryb, int nnr_gracza) : Gracz(nile_niepowodzen_gracza, nile_liter_trafiono, ntryb, nnr_gracza) {
		;
	}
	Uzytkownik(Uzytkownik& kopiowany) {
		ile_niepowodzen_gracza = kopiowany.get_ile_niepowodzen_gracza();
		ile_liter_trafiono = kopiowany.get_ile_liter_trafiono();
		tryb = kopiowany.get_tryb();
		nr_gracza = kopiowany.get_nr_gracza();
	}
	~Uzytkownik() {
		if (nast != NULL)
			delete nast;
	}

	/*	Pobiera od uzytkownika litere.
	*/

	char pobierz_litere() {
		printf("Podaj litere: ");
		return wczytaj_litera();
	}

	friend void Obsluga_gry::spr_litere();
};
#endif