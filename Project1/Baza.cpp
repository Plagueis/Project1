#include "Baza.h"

#define PROM 15
#define ZYCIE 20

int Baza::liczebnoscBaz = 0;

Punkt Baza::gdzie()
{
	return pozycja;
}

int Baza::rozmiar()
{
	return promien;
}

Baza::Baza(const Punkt & lokalizacja)
{
	liczebnoscBaz++;
	pozycja = lokalizacja;
	zycie = ZYCIE;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(double x, double y)
{
	liczebnoscBaz++;
	Punkt start(x, y);
	pozycja = start;
	zycie = ZYCIE;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(const Punkt & lokalizacja, int trudnosc)
{
	liczebnoscBaz++;
	pozycja = lokalizacja;
	zycie = ZYCIE+trudnosc;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(double x, double y, int trudnosc)
{
	liczebnoscBaz++;
	Punkt start(x, y);
	pozycja = start;
	zycie = ZYCIE+trudnosc;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(const Baza & wzor)
{
	liczebnoscBaz++;
	pozycja = wzor.pozycja;
	zycie = wzor.zycie;
	orientacja = 0;
	predkosc = 0;
	promien = wzor.promien;
}

Baza::~Baza()
{
	liczebnoscBaz--;
}

void Baza::uderzona(int ile)
{
	promien -= ile/3;
	zycie -= ile;
}

bool Baza::martwa()
{
	if (zycie > 0)
		return false;
	else
		return true;
}
