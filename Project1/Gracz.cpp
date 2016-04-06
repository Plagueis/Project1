#include "Gracz.h"

#define PRED 6

void Gracz::uderzony(int ile)
{
	zycie -= ile;
}

void Gracz::zdobycz(int ile)
{
	zarobek += ile;
}

void Gracz::lecz(int ile)
{
	zycie += ile;
	if (zycie > zycie_poczatkowe)
		zycie = zycie_poczatkowe;
}

int Gracz::dorobek()
{
	return zarobek;
}

int Gracz::zdrowie()
{
	return zycie;
}

bool Gracz::martwy()
{
	if (zycie > 0)
		return false;
	else
		return true;
}

Gracz::Gracz()
{
	zycie_poczatkowe = 1000;
	zycie = 1000;
	promien = 10;
	zarobek = 0;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Gracz::Gracz(int ile_zycia)
{
	zycie_poczatkowe = ile_zycia;
	zycie = ile_zycia;
	promien = 10;
	zarobek = 0;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}
