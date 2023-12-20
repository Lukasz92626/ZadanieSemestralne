#ifndef obslugaGry_hpp
#define obslugaGry_hpp

#include "gracz.cpp"

class Obsluga_gry {
public:
	Gracz* pierwszy; //wskaznik na pierwszego gracza
	Gracz* aktualny; //wskaznik na aktualnego gracza

	Obsluga_gry();
	Obsluga_gry(char nhaslo[], char nkategoria[]);
	~Obsluga_gry();
	char* get_haslo();
	void set_haslo(char nhaslo[]);

	char* get_kategoria();
	void set_kategoria(char nkategoria[]);

	int get_ile_niepowodzen();
	bool set_ile_niepowodzen(int nile_niepowodzen);

	int get_liczba_kolejek();
	bool set_liczba_kolejek(int nliczba_kolejek);

	int get_ile_graczy();

	int get_ile_trafionych();
	bool set_ile_trafionych(int nile_trafionych);

	char get_litera();
	bool set_litera(char nlitera);

	void wczytaj_haslo();

	void wczytaj_kategoria();

	void wypisz_informacje();

	void spr_litere();

	bool spr_czy_koniec_gry();

	void wypisz_haslo_czesciowo();

	char wczytaj_odgadywanie();

	void wczytaj_spr_haslo();

	void sprawdz_haslo();

	void sprawdz_czy_pobrac_haslo();

	void losuj_haslo();

	int wczytaj_tryb();

	void pobierz_ilosc_graczy();
	void stworz_graczy();
	void wczytaj_litere();
	void wypisz_statystyki();
	void rysuj_wisielca();
};
#endif