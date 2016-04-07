#include "Bonus.h"
#include <cstdlib>
#include <ctime>

#define PROM 8

int Bonus::liczebnoscB = 0;

Bonus::Bonus(Punkt start, int moc, int cena)
{
	liczebnoscB++;
	pozycja = start;
	leczenie = moc;
	wartosc = cena;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Bonus::Bonus(double x, double y, int moc, int cena)
{
	liczebnoscB++;
	Punkt start(x, y);
	pozycja = start;
	leczenie = moc;
	wartosc = cena;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}
Bonus::Bonus(const Bonus &wzor)
{
	liczebnoscB++;
	pozycja = wzor.pozycja;
	leczenie = wzor.leczenie;
	wartosc = wzor.wartosc;
	orientacja = 0;
	predkosc = 0;
	promien = wzor.promien;
}

Bonus::~Bonus()
{
	liczebnoscB--;
}

int Bonus::moc()
{
	return leczenie;
}

int Bonus::lup()
{
	return wartosc;
}

