#include "Gracz.h"

void Gracz::uderzony(int ile)
{
	zycie -= ile;
}

void Gracz::zdobycz(int ile)
{
	zarobek += ile;
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
	zycie = 1000;
	promien = 10;
	zarobek = 0;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = 6;
}
