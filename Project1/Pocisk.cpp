#include "Pocisk.h"
#include "Wrog.h"
#include "Gracz.h"

#define PRED 6
#define PROM 3
#define SILA 5

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
	sila = SILA;
	promien = PROM;
	pozycja = strzelajacy.gdzie();
	orientacja = strzelajacy.kierunek();
	predkosc = PRED;
}

Pocisk::Pocisk(const Pocisk &wzor)
{
	liczebnoscP++;
	sila = wzor.sila;
	promien = wzor.promien;
	pozycja = wzor.pozycja;
	orientacja = wzor.orientacja;
	predkosc = wzor.predkosc;
}


Pocisk::~Pocisk()
{
	liczebnoscP--;
}