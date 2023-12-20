#include <iostream>

#ifndef OperacjeNaInt_cpp
#define OperacjeNaInt_cpp

/*	"Losuje" liczbe naturalna z zakresu i zwraca ja.
*	lewy - najmniejszy element w zakresie
*	prawy - najwiekszy element w zakresie
*	return liczba - wylosowana liczba
*/

int losuj_naturalna_zakres(int lewy, int prawy) {
	int liczba = 0;//losowana liczba
	liczba = rand();
	int pom = prawy - lewy;
	liczba = liczba % pom;
	liczba += lewy;
	return liczba;
}


/*	Pobiera od uzytkownika int z zakresu.
*	return liczba - wczytana liczba
*/

int wczytaj_int_zakres(int lewy, int prawy) {
	int liczba = 0; //wczytywana liczba
	while (scanf_s("%d", &liczba) != 1 || liczba < lewy || liczba > prawy || getchar() != '\n') {
		printf("Podana liczba jest bledna. Popraw: ");
		while (getchar() != '\n')
			;
	}
	return liczba;
}
#endif