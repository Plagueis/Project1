#include "Gracz.h"

#define PRED 6
#define SILA 4


void Gracz::dodaj_punkty(int ile)
{
	punkty += ile;
	if (punkty > 5000 * poziom + poziom * poziom * 200)
	{
		this->awans(poziom);
		poziom++;
	}
}

void Gracz::przywroc_zycie(int ile)
{
	zycie += ile;
	if (zycie > limit_zycia)
		zycie = limit_zycia;
}

void Gracz::awans(int ktory)
{
	if(ktory<7)
		limit_zycia += limit_zycia / 10;
	sila++;
}

void Gracz::uderzenie(int ile)
{
	zycie -= ile;
}

int Gracz::pokaz_punkty()
{
	return punkty;
}

int Gracz::pokaz_zycie()
{
	return zycie;
}

int Gracz::pokaz_limit_zycia()
{
	return limit_zycia;
}

int Gracz::pokaz_sile()
{
	return sila;
}

int Gracz::pokaz_poziom()
{
	return poziom;
}

Gracz::Gracz()
{
	limit_zycia = 1000;
	zycie = 1000;
	promien = 10;
	punkty = 0;
	poziom = 1;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
	sila = SILA;
}

Gracz::Gracz(int ile_zycia)
{
	limit_zycia = ile_zycia;
	zycie = ile_zycia;
	promien = 10;
	punkty = 0;
	poziom = 1;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
	sila = SILA;
}
