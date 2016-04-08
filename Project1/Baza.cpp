#include "Baza.h"

#define PROM 15
#define ZYCIE 20
#define WART 20

int Baza::liczebnosc = 0;



int Baza::pokaz_ile()
{
	return liczebnosc;
}

Baza::Baza(const Punkt & lokalizacja)
{
	liczebnosc++;
	pozycja = lokalizacja;
	zycie = ZYCIE;
	punkty = WART;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(double x, double y)
{
	liczebnosc++;
	Punkt start(x, y);
	pozycja = start;
	zycie = ZYCIE;
	punkty = WART;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(const Punkt & lokalizacja, int trudnosc)
{
	liczebnosc++;
	pozycja = lokalizacja;
	zycie = ZYCIE+trudnosc;
	punkty = WART+trudnosc*2;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(double x, double y, int trudnosc)
{
	liczebnosc++;
	Punkt start(x, y);
	pozycja = start;
	zycie = ZYCIE+trudnosc;
	punkty = WART*2;
	orientacja = 0;
	predkosc = 0;
	promien = PROM;
}

Baza::Baza(const Baza & wzor)
{
	liczebnosc++;
	pozycja = wzor.pozycja;
	zycie = wzor.zycie;
	punkty = wzor.punkty;
	orientacja = 0;
	predkosc = 0;
	promien = wzor.promien;
}

Baza::~Baza()
{
	liczebnosc--;
}

void Baza::uderzenie(int ile)
{
	int zmniejszenie = ile / 2;
	zmniejszenie *= promien;
	zmniejszenie /= zycie;
	promien -= zmniejszenie;
	zycie -= ile;
}

int Baza::pokaz_punkty()
{
	return punkty;
}