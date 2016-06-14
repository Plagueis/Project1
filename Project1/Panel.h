#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include"gracz.h"

using namespace std;

class Panel
{
private:
	int szerokosc, wysokosc, dlugosc_paska, stan_paska;
	string zegar, poziom, punkty;


public:
	Panel(int szer, int wys);
	void aktualizuj(Gracz gracz, sf::Clock czas);
};
