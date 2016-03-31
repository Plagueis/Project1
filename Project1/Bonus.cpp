#include "Bonus.h"
#include <cstdlib>
#include <ctime>

#define PROM 8

int Bonus::liczebnoscB = 0;

Bonus::Bonus(Punkt start, int moc)
{
	liczebnoscB++;
	pozycja = start;
	wartosc = moc;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Bonus::Bonus(double x, double y, int moc)
{
	liczebnoscB++;
	Punkt start(x, y);
	pozycja = start;
	wartosc = moc;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}
Bonus::Bonus(const Bonus &wzor)
{
	liczebnoscB++;
	pozycja = wzor.pozycja;
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
	return wartosc;
}

