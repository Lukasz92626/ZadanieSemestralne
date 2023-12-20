#include <iostream>

#ifndef GRACZ_cpp
#define GRACZ_cpp
#include "definicje.hpp"

//#include "obslugaGry.hpp"

class Gracz {
protected:
	int ile_niepowodzen_gracza = 0; //liczba niepowodzen gracza
	int ile_liter_trafiono = 0; //liczba trafionych liter
	int tryb = TRYB_UZYTKOWNIKA; //tryb gry
	int nr_gracza = 1; //numer gracza
	char spr_haslo[DL_HASLA]; //wczytywane haslo
	bool czy_odgadniete = false; //przechowuje informacje na temat odgadniecia hasla odrazu
public:
	Gracz* nast; //wskaznik na nastepnego gracza
	Gracz() {
		ile_niepowodzen_gracza = 0;
		ile_liter_trafiono = 0;
		tryb = TRYB_UZYTKOWNIKA;
		nr_gracza = 1;
		nast = NULL;
		strcpy(spr_haslo, "");
	}
	Gracz(int nile_niepowodzen_gracza, int nile_liter_trafiono, int ntryb, int nnr_gracza) {
		set_ile_niepowodzen_gracza(nile_niepowodzen_gracza);
		set_ile_liter_trafiono(nile_liter_trafiono);
		set_tryb(ntryb);
		set_nr_gracza(nnr_gracza);
		nast = NULL;
		strcpy(spr_haslo, "");
	}
	Gracz(Gracz& kopiowany) {
		ile_niepowodzen_gracza = kopiowany.get_ile_niepowodzen_gracza();
		ile_liter_trafiono = kopiowany.get_ile_liter_trafiono();
		tryb = kopiowany.get_tryb();
		nr_gracza = kopiowany.get_nr_gracza();
		strcpy(spr_haslo, "");
	}

	int get_ile_niepowodzen_gracza() { return ile_niepowodzen_gracza; }
	bool set_ile_niepowodzen_gracza(int nile_niepowodzen_gracza) {
		if (nile_niepowodzen_gracza > 0 && nile_niepowodzen_gracza <= MAX_NIEPOWODZEN) {
			ile_niepowodzen_gracza = nile_niepowodzen_gracza;
			return true;
		}
		return false;
	}
	int get_ile_liter_trafiono() { return ile_liter_trafiono; }
	bool set_ile_liter_trafiono(int nile_liter_trafiono) {
		if (nile_liter_trafiono > 0 && nile_liter_trafiono <= DL_TRAFIONE) {
			ile_liter_trafiono = nile_liter_trafiono;
			return true;
		}
		return false;
	}
	int get_tryb() { return tryb; }
	bool set_tryb(int ntryb) {
		if (ntryb == TRYB_KOMPUTER || ntryb == TRYB_UZYTKOWNIKA) {
			tryb = ntryb;
			return true;
		}
		return false;
	}
	int get_nr_gracza() { return nr_gracza; }
	bool set_nr_gracza(int nnr_gracza) {
		if (nnr_gracza >= 0) {
			nr_gracza = nnr_gracza;
			return true;
		}
		return false;
	}

	/*	Pobiera od gracza litere.
	*/

	virtual char pobierz_litere() = 0;

	//friend void Obsluga_gry::spr_litere();
};
#endif