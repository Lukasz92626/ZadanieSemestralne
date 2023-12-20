#include <iostream>
#include <fstream>

#ifndef OBSLUGA_GRY_CPP
#define OBSLUGA_GRY_CPP
#include "definicje.hpp"
#include "obslugaPlikow.hpp"
#include "operacjeNaInt.hpp"

#include "gracz.cpp"
#include "uzytkownik.cpp"
#include "komputer.cpp"

class Obsluga_gry {
private:
	char haslo[DL_HASLA]; //zgadywane haslo
	char kategoria[DL_KATEGORIA]; //kategoria hasla
	int trafione[DL_TRAFIONE] = { 0 }; //trafione litery z hasla, 0 - litera byla, 1 - nie bylo litery
	int nietrafione[DL_TRAFIONE] = { 0 }; //nietrafione litery z hasla, 0 - litera byla, 1 - nie bylo litery
	int ile_niepowodzen = 0; //liczba niepowodzen wszystkich graczy
	char litera; //pobierana aktualnie litera
	char spr_haslo[DL_HASLA]; //wczytywane haslo
	bool czy_odgadniete = false; //przechowuje informacje na temat odgadniecia hasla
	int ile_graczy; //ile graczy

	//statystyki
	int liczba_kolejek = 0; //liczba kolejek w czasie gry
	int ile_trafionych = 0; //liczba trafionych liter

	/*	Sprawdza czy w napisie sa same litery.
	*	napis - sprawdzany napis
	*/

	bool spr_napis_litery(char napis[]) {
		int i = 0;
		while (napis[i] != '\0' && i != DL_HASLA) {
			if (!(napis[i] >= 'a' && napis[i] <= 'z') && !(napis[i] >= 'A' && napis[i] <= 'Z') && napis[i] != ' ') {
				return false;
			}
			++i;
		}
		return true;
	}

	/*	Wczytuje napis od uzytkownika
	*	napis - wczytywany napis
	*/

	void wczytaj_napis(char napis[]) {
		while (scanf_s("%s", napis, DL_HASLA) != 1 || getchar() != '\n') {
			printf("Blad popraw: ");
			while (getchar() != '\n')
				;
		}
	}

	/*	Konwertuje podana litere na mala.
	*	zam_litera - zamieniana litera
	*/

	char konwersja_na_male(char zam_litera) {
		if (zam_litera >= 'A' && zam_litera <= 'Z') {
			zam_litera = 'a' + (zam_litera - 'A');
		}
		return zam_litera;
	}

	/*	Wypisuje informacje o wygranej.
	*/

	void wypisz_informacje_wygranie() {
		printf("Gracz %d odgadnal haslo.\n", aktualny->get_nr_gracza());
	}

	/*	Wypisuje informacje o porazce.
	*/

	void wypisz_informacje_porazka() {
		printf("Gracz %d nie trafil.\n", aktualny->get_nr_gracza());
		printf("Oto stadium Wisielca:\n");
		rysuj_wisielca();
	}

	/*	Zamienia tablice z trafionymi literami na 0 (czyli nie ma zadnej litery trafionej).
	*/

	void wyczysc_trafione() {
		for (int i = 0; i < DL_TRAFIONE; ++i) {
			trafione[i] = 0;
		}
	}

	/*	Zamienia tablice z nietrafionymi literami na 0 (czyli nie ma zadnej litery nietrafionej).
	*/

	void wyczysc_nietrafione() {
		for (int i = 0; i < DL_TRAFIONE; ++i) {
			nietrafione[i] = 0;
		}
	}

	/*	Wypisuje trafione litery.
	*/

	void wypisz_trafione() {
		bool czyPierwszy = true;
		for (int i = 0; i < DL_TRAFIONE; ++i) {
			if (trafione[i] >= 1) {
				if (czyPierwszy) {
					printf("%c", (char)('a' + i));
					czyPierwszy = false;
				}
				else
					printf(", %c", (char)('a' + i));
			}
		}
	}

	/*	Wypisuje nietrafione litery.
	*/

	void wypisz_nietrafione() {
		bool czyPierwszy = true;
		for (int i = 0; i < DL_TRAFIONE; ++i) {
			if (nietrafione[i] >= 1) {
				if (czyPierwszy) {
					printf("%c", (char)('a' + i));
					czyPierwszy = false;
				}
				else
					printf(", %c", (char)('a' + i));
			}
		}
	}
public:
	Gracz* pierwszy; //wskaznik na pierwszego gracza
	Gracz* aktualny; //wskaznik na aktualnego gracza

	Obsluga_gry() {
		strcpy(haslo, PRZ_HASLO);
		strcpy(kategoria, PRZ_KATEGORIA);
		wyczysc_trafione();
		wyczysc_nietrafione();
		ile_niepowodzen = 0;
		litera = 'a';
		ile_graczy = 0;
		pierwszy = NULL;
		aktualny = NULL;

		liczba_kolejek = 0;
		ile_trafionych = 0;
	}
	Obsluga_gry(char nhaslo[], char nkategoria[]) {
		strcpy(haslo, nhaslo);
		strcpy(kategoria, nkategoria);
		wyczysc_trafione();
		wyczysc_nietrafione();
		ile_niepowodzen = 0;
		litera = 'a';
		ile_graczy = 0;
		pierwszy = NULL;
		aktualny = NULL;
		liczba_kolejek = 0;
		ile_trafionych = 0;
	}
	~Obsluga_gry() {
		if (pierwszy != NULL)
			delete pierwszy;
	}

	char* get_haslo() { return haslo; }
	void set_haslo(char nhaslo[]) { strcpy(haslo, nhaslo); }

	char* get_kategoria() { return kategoria; }
	void set_kategoria(char nkategoria[]) { strcpy(kategoria, nkategoria); }

	int get_ile_niepowodzen() { return ile_niepowodzen; }
	bool set_ile_niepowodzen(int nile_niepowodzen) {
		if (nile_niepowodzen <= MAX_NIEPOWODZEN && nile_niepowodzen >= 0) {
			ile_niepowodzen = nile_niepowodzen;
			return true;
		}
		return false;
	}

	int get_liczba_kolejek() { return liczba_kolejek; }
	bool set_liczba_kolejek(int nliczba_kolejek) {
		if (nliczba_kolejek >= 0) {
			liczba_kolejek = nliczba_kolejek;
			return true;
		}
		return false;
	}

	int get_ile_graczy() { return ile_graczy; }

	int get_ile_trafionych() { return ile_trafionych; }
	bool set_ile_trafionych(int nile_trafionych) {
		if (nile_trafionych <= DL_TRAFIONE && nile_trafionych >= 0) {
			ile_trafionych = nile_trafionych;
			return true;
		}
		return false;
	}

	char get_litera() { return litera; }
	bool set_litera(char nlitera) {
		if ((nlitera >= 'a' && nlitera <= 'z') || (nlitera >= 'A' && nlitera <= 'Z')) {
			litera = nlitera;
			return true;
		}
		return false;
	}

	/*	Wczytuje haslo od uzytkownika.
	*/

	void wczytaj_haslo() {
		wczytaj_napis(haslo);
		while (!spr_napis_litery(haslo)) {
			printf("Blad. Haslo sklada sie tylko z liter.\nPodaj jeszcze raz: ");
			wczytaj_napis(haslo);
		}
	}

	/*	Wczytuje kategorie od uzytkownika.
	*/

	void wczytaj_kategoria() {
		wczytaj_napis(kategoria);
	}

	/*	Wypisuje informacje o rozgrywce.
	*/

	void wypisz_informacje() {
		cout << "\nInformacje o grze:\n";
		cout << "Kategoria hasla: " << kategoria << '\n';
		cout << "Haslo: ";
		wypisz_haslo_czesciowo();
		cout << "\nTrafione litery w hasle: ";
		wypisz_trafione();
		cout << "\nNietrafione litery w hasle: ";
		wypisz_nietrafione();
		cout << "\nLiczba niepowodzen: " << ile_niepowodzen << '\n';
		cout << "Liczba trafionych liter: " << ile_trafionych << '\n';
		cout << "Stadium wisielca:\n";
		rysuj_wisielca();
	}

	/*	Sprawdza czy podana litera jest w hasle.
	*/

	void spr_litere() {
		int i = 0;
		while (konwersja_na_male(haslo[i]) != litera && i < DL_HASLA - 1 && haslo[i] != '\0') {
			++i;
		}
		if (i != DL_HASLA - 1) {
			if (konwersja_na_male(haslo[i]) == litera && trafione[litera - 'a'] < 1) {
				trafione[litera - 'a'] = 1;
				aktualny->set_ile_liter_trafiono(aktualny->get_ile_liter_trafiono() + 1);
				++ile_trafionych;
				printf("Trafione.\n");
			}
			else if (trafione[litera - 'a'] == 1) {
				printf("Nietrafione. Litera juz byla.\n");
				++ile_niepowodzen;
				aktualny->set_ile_niepowodzen_gracza(aktualny->get_ile_niepowodzen_gracza() + 1);
			}
			else {
				nietrafione[litera - 'a'] = 1;
				printf("Nietrafione.\n");
				++ile_niepowodzen;
				aktualny->set_ile_niepowodzen_gracza(aktualny->get_ile_niepowodzen_gracza() + 1);
				//aktualny->ile_niepowodzen_gracza += 1;
			}
		}
		else if (i == DL_HASLA - 1) {
			nietrafione[litera - 'a'] = 1;
			printf("Nietrafione.\n");
			++ile_niepowodzen;
		}
	}

	/*	Sprawdza czy koniec gry.
	*/

	bool spr_czy_koniec_gry() {
		if (ile_niepowodzen >= MAX_NIEPOWODZEN) {
			printf("\nKoniec gry. Za duzo niepowodzen.\n");
			wypisz_informacje_porazka();
			return true;
		}
		else if (czy_odgadniete) {
			wypisz_informacje_wygranie();
			return true;
		}
		int i = 0;
		while (i < DL_HASLA - 1 && haslo[i] != '\0') {
			if (trafione[konwersja_na_male(haslo[i]) - 'a'] < 1) {
				return false;
			}
			++i;
		}
		wypisz_informacje_wygranie();
		return true;
	}

	/*	Wypisuje haslo w postaci znakow '_' oraz tylko z tymi literami ktore zostaly odgadniete.
	*/

	void wypisz_haslo_czesciowo() {
		int i = 0;
		while (i < DL_HASLA - 1 && haslo[i] != '\0') {
			if (haslo[i] >= 'a' && haslo[i] <= 'z') {
				if (trafione[haslo[i] - 'a'] >= 1) {
					putchar(haslo[i]);
				}
				else {
					putchar('_');
				}
			}
			else if (haslo[i] >= 'A' && haslo[i] <= 'Z') {
				if (trafione[haslo[i] - 'A'] >= 1) {
					putchar(haslo[i]);
				}
				else {
					putchar('_');
				}
			}
			else {
				putchar(haslo[i]);
			}
			++i;
		}
	}

	/*	Wczytuje sposob odgadywania hasla.
	*/

	char wczytaj_odgadywanie() {
		char odgadywanie = LITERA; //wczytywany sposob odgadywania
		while (scanf_s("%c", &odgadywanie, 1) != 1 || (odgadywanie != LITERA && odgadywanie != HASLO) || getchar() != '\n') {
			printf("Podany znak nie informuje o sposobie odgadywania. Popraw: ");
			while (getchar() != '\n')
				;
		}
		return odgadywanie;
	}

	/*	Wczytuje haslo od uzytkownika.
	*/

	void wczytaj_spr_haslo() {
		printf("Podaj zgadywane haslo: ");
		while (scanf_s("%s", spr_haslo, DL_HASLA) != 1 || getchar() != '\n') {
			printf("Blad popraw: ");
			while (getchar() != '\n')
				;
		}
	}

	/*	Sprawdza czy podane haslo jest zgadywanym haslem.
	*/

	void sprawdz_haslo() {
		int i = 0;
		while (konwersja_na_male(haslo[i]) == konwersja_na_male(spr_haslo[i]) && i < DL_HASLA - 1 && konwersja_na_male(haslo[i]) != '\0' && konwersja_na_male(spr_haslo[i]) != '\0') {
			++i;
		}
		if (i != DL_HASLA - 1) {
			if (konwersja_na_male(haslo[i]) == konwersja_na_male(spr_haslo[i])) {
				printf("\nTrafiono haslo.\n");
				czy_odgadniete = true;
			}
			else {
				printf("Nie trafiono hasla.\n");
				++ile_niepowodzen;
			}
		}
		else if (i == DL_HASLA - 1) {
			printf("Nie trafiono hasla.\n");
			++ile_niepowodzen;
		}
	}

	/*	Sprawdza czy uzytkownik zadeklarowal chec wpisania hasla i wykonuje odpowiednia czynnosc.
	*/

	void sprawdz_czy_pobrac_haslo() {
		char inf = 'T'; //informacja o wczytaniu hasla
		while (scanf_s("%c", &inf, 1) != 1 || (inf != 'T' && inf != 'N') || getchar() != '\n') {
			printf("Bladna odpowiedz. Popraw: ");
			while (getchar() != '\n')
				;
		}
		if (inf == 'T') {
			printf("Podaj nowe haslo: ");
			wczytaj_haslo();
			int i = 0;
			printf("Podaj kategorie hasla: ");
			wczytaj_kategoria();
		}
		else if (inf == 'N') {
			losuj_haslo();
			int i = 0;
			printf("Wylosowano haslo. Kategoria: %s\n", kategoria);
		}
	}

	/*	Losuje haslo z pliku.
	*/

	void losuj_haslo() {
		char nazwa_pliku[] = NAZWA_PLIKU_HASLA; //nazwa pliku z haslami
		int ile = 0; //ilosc hasel
		ile = licz_dl_pliku_hasla(nazwa_pliku);
		int nr = 0; //numer losowanego hasla
		if (ile == 0) {
			char los_hasla[ILE_LOS_HASLA][DL_HASLA] = { "wisielec", "funkcja", "Warszawa", "konstruktor", "Londyn", "Dziedziczenie", "Destruktor", "Metoda", "Zmienna", "klasa" }; //losowane hasla w trybie awaryjnym
			char los_kategorie[ILE_LOS_HASLA][DL_KATEGORIA] = { "Gra", "Programowanie", "Miasta", "Klasy", "Miasta", "Klasy", "Klasy", "Klasy", "Programowanie", "Programowanie" }; //kategorie do losowanych hasel w trybie awaryjnym
			printf("Losowanie hasla z tablicy, zamiast z pliku %s.\n", nazwa_pliku);
			nr = rand() % ILE_LOS_HASLA;
			strcpy(haslo, los_hasla[nr]);
			strcpy(kategoria, los_kategorie[nr]);
		}
		else {
			nr = rand() % ile;
			int i = 0;
			char test_haslo[DL_HASLA] = { 0 }; //testowe wczytywanie hasel
			char test_kategoria[DL_KATEGORIA] = { 0 }; //testowa kategoria
			ifstream strumien = otworz_plik(nazwa_pliku, false); //strumien otwartego pliku
			while (i != nr && !strumien.eof()) {
				strumien >> test_haslo;
				strumien >> test_kategoria;
				++i;
			}
			strumien.close();
			strcpy(haslo, test_haslo);
			strcpy(kategoria, test_kategoria);
		}

	}

	/*	Wczytuje tryb od uzytkownika.
	*/

	int wczytaj_tryb() {
		int tryb = TRYB_UZYTKOWNIKA; //wczytywany tryb gracza
		while (scanf_s("%d", &tryb) != 1 || (tryb != TRYB_KOMPUTER && tryb != TRYB_UZYTKOWNIKA) || getchar() != '\n') {
			printf("Podany znak nie jest trybem. Popraw: ");
			while (getchar() != '\n')
				;
		}
		return tryb;
	}

	/*	Pobiera od uzytkownika liczbe graczy.
	*/

	void pobierz_ilosc_graczy() {
		ile_graczy = wczytaj_int_zakres(1, MAX_GRACZY);
	}

	/*	Tworzy liste graczy.
	*/

	void stworz_graczy() {
		int tryb = TRYB_UZYTKOWNIKA; //tryb gracza
		printf("Wybierz rodzaj %d gracza (%d - komputer, %d - uzytkownik): ", 1, TRYB_KOMPUTER, TRYB_UZYTKOWNIKA);
		tryb = wczytaj_tryb();
		if (tryb == TRYB_KOMPUTER) {
			pierwszy = new Komputer(0, 0, tryb, 1);
		}
		else if (tryb == TRYB_UZYTKOWNIKA) {
			pierwszy = new Uzytkownik(0, 0, tryb, 1);
		}
		aktualny = pierwszy;
		for (int i = 1; i < ile_graczy; ++i) {
			printf("Wybierz rodzaj %d gracza (%d - komputer, %d - uzytkownik): ", i + 1, TRYB_KOMPUTER, TRYB_UZYTKOWNIKA);
			tryb = wczytaj_tryb();
			if (tryb == TRYB_KOMPUTER) {
				aktualny->nast = new Komputer(0, 0, tryb, i + 1);
			}
			else if (tryb == TRYB_UZYTKOWNIKA) {
				aktualny->nast = new Uzytkownik(0, 0, tryb, i + 1);
			}
			aktualny = aktualny->nast;
		}
		aktualny = pierwszy;
	}

	/*	Wczytuje litere od gracza.
	*/

	void wczytaj_litere() {
		litera = aktualny->pobierz_litere();
		litera = konwersja_na_male(litera);
	}

	/*	Wypisuje koncowe statystyki.
	*/

	void wypisz_statystyki() {
		cout << "Liczba kolejek: " << liczba_kolejek << '\n';
		cout << "Liczba niepowodzen: " << ile_niepowodzen << '\n';
		cout << "Liczba trafionych liter: " << ile_trafionych << '\n';
		cout << "Trafione litery: ";
		wypisz_trafione();
		cout << "\nNietrafione litery: ";
		wypisz_nietrafione();
		cout << '\n';
	}

	/*	Rysuje aktualny rysunek wisielca (zgodnie z liczba niepowodzen).
	*/

	void rysuj_wisielca() {
		//Rysowany wisielec:
		/*   ___
			|/ |
			|  O
			| /|\
			| / \
		   / \     */
		printf(" __________\n");
		printf("|  ");
		if (ile_niepowodzen >= 4)
			printf("  ___");
		else
			printf("     ");
		printf("   |\n");

		printf("|  ");
		if (ile_niepowodzen >= 3) {
			printf(" |");
			if (ile_niepowodzen >= 5) {
				printf("/ ");
				if (ile_niepowodzen >= 6)
					printf("|");
				else
					putchar(' ');
			}
			else
				printf("   ");
		}
		else
			printf("     ");
		printf("   |\n");

		printf("|  ");
		if (ile_niepowodzen >= 3) {
			printf(" |");
			if (ile_niepowodzen >= 7)
				printf("  O");
			else
				printf("   ");
		}
		else
			printf("     ");
		printf("   |\n");

		printf("|  ");
		if (ile_niepowodzen >= 2) {
			printf(" | ");
			if (ile_niepowodzen >= 9)
				printf("/");
			else
				printf(" ");
			if (ile_niepowodzen >= 8) {
				printf("|");
				if (ile_niepowodzen >= 9)
					printf("\\"); // \ (jeden)
				else
					printf(" ");
			}
			else
				printf("  ");
		}
		else
			printf("      ");
		printf("  |\n");

		printf("|  ");
		if (ile_niepowodzen >= 2) {
			printf(" | ");
			if (ile_niepowodzen >= 10)
				printf("/ \\");
			else
				printf("   ");
		}
		else
			printf("      ");
		printf("  |\n");

		printf("|  ");
		if (ile_niepowodzen >= 1)
			printf("/ \\");
		else
			printf("   ");
		printf("     |\n");
		printf("|__________|\n");
	}
};
#endif