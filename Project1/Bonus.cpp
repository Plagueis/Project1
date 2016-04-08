#include "Bonus.h"
#include <cstdlib>
#include <ctime>

#define PROM 8

int Bonus::liczebnosc = 0;

int Bonus::pokaz_ile()
{
	return liczebnosc;
}

Bonus::Bonus(Punkt start, int ile, int cena)
{
	liczebnosc++;
	pozycja = start;
	moc = ile;
	punkty = cena;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Bonus::Bonus(double x, double y, int ile, int cena)
{
	liczebnosc++;
	Punkt start(x, y);
	pozycja = start;
	moc = ile;
	punkty = cena;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}
Bonus::Bonus(const Bonus &wzor)
{
	liczebnosc++;
	pozycja = wzor.pozycja;
	moc = wzor.moc;
	punkty = wzor.punkty;
	orientacja = 0;
	predkosc = 0;
	promien = wzor.promien;
}

Bonus::~Bonus()
{
	liczebnosc--;
}

int Bonus::pokaz_moc()
{
	return moc;
}

int Bonus::pokaz_punkty()
{
	return punkty;
}

