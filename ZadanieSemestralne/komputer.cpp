#ifndef KOMPUTER_CPP
#define KOMPUTER_CPP

#include "gracz.cpp"
#include "OperacjeNaInt.hpp"

#include "obslugaGry.hpp"

class Komputer : public Gracz {
private:
	/*	Losuje litere.
	*/

	char losuj_litere() {
		char litera = 'a'; //losowana litera
		litera = (char)losuj_naturalna_zakres('a', 'z');
		return litera;
	}
public:
	Komputer() : Gracz() {
		;
	}
	Komputer(int nile_niepowodzen_gracza, int nile_liter_trafiono, int ntryb, int nnr_gracza) : Gracz(nile_niepowodzen_gracza, nile_liter_trafiono, ntryb, nnr_gracza) {
		;
	}
	Komputer(Komputer& kopiowany) {
		ile_niepowodzen_gracza = kopiowany.get_ile_niepowodzen_gracza();
		ile_liter_trafiono = kopiowany.get_ile_liter_trafiono();
		tryb = kopiowany.get_tryb();
		nr_gracza = kopiowany.get_nr_gracza();
	}
	~Komputer() {
		if (nast != NULL)
			delete nast;
	}

	/*	Pobiera od komputera litere.
	*/

	char pobierz_litere() {
		char lit = losuj_litere(); //wylosowana litera
		printf("Wylosowano litere: %c\n", lit);
		return lit;
	}

	friend void Obsluga_gry::spr_litere();
};
#endif