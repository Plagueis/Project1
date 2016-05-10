#pragma once
#include "Punkt.h"
#include <SFML/Graphics.hpp>
class Sterowanie
{

private:
	bool lewo, prawo, gora, dol, przycisk_myszy;
	Punkt pozycja_myszy;
public:
	bool czy_lewo();
	bool czy_prawo();
	bool czy_gora();
	bool czy_dol();
	bool czy_przycisk_myszy();
	Punkt pokaz_gdzie_mysz();
	void aktualizuj_przyciski();
	void aktualizuj_pozycje_myszy(sf::RenderWindow okno);
};
