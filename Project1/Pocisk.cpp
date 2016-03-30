#include "Pocisk.h"
#include "Wrog.h"
#include "Gracz.h"

int Pocisk::liczebnoscP = 0;

void Pocisk::atak(Wrog &cel)
{
	cel.uderzony(sila);
}

void Pocisk::premia()
{
	sila *= 2;
}

void Pocisk::oslabienie()
{
	sila /= 2;
}

Pocisk::Pocisk(Gracz &strzelajacy)
{
	liczebnoscP++;
	sila = 5;
	promien = 3;
	pozycja = strzelajacy.gdzie();
	orientacja = strzelajacy.kierunek();
	predkosc = 6;
}

Pocisk::Pocisk(const Pocisk &wzor)
{
	liczebnoscP++;
	sila = 5;
	promien = 3;
	pozycja = wzor.pozycja;
	orientacja = wzor.orientacja;
	predkosc = 6;
}


Pocisk::~Pocisk()
{
	liczebnoscP--;
}