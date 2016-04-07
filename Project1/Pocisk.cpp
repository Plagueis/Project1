#include "Pocisk.h"
#include "Wrog.h"
#include "Gracz.h"
#include "Baza.h"

#define PRED 6
#define PROM 3
#define SILA 4

int Pocisk::liczebnoscP = 0;
int Pocisk::sila = SILA;

void Pocisk::atak(Wrog &cel)
{
	cel.uderzony(sila);
}

void Pocisk::atak(Baza & cel)
{
	cel.uderzona(sila);
}

void Pocisk::premia()
{
	sila++;
}


Pocisk::Pocisk(Gracz &strzelajacy)
{
	liczebnoscP++;
	promien = PROM;
	pozycja = strzelajacy.gdzie();
	orientacja = strzelajacy.kierunek();
	predkosc = PRED;
}

Pocisk::Pocisk(const Pocisk &wzor)
{
	liczebnoscP++;
	promien = wzor.promien;
	pozycja = wzor.pozycja;
	orientacja = wzor.orientacja;
	predkosc = wzor.predkosc;
}


Pocisk::~Pocisk()
{
	liczebnoscP--;
}