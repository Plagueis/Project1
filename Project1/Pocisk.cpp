#include "Pocisk.h"
#include "Wrog.h"
#include "Gracz.h"
#include "Baza.h"
#include "Grozne.h"

#define PRED 6
#define PROM 3

int Pocisk::liczebnosc = 0;



int Pocisk::pokaz_ile()
{
	return liczebnosc;
}

Pocisk::Pocisk(Gracz &strzelajacy)
{
	liczebnosc++;
	promien = PROM;
	pozycja = strzelajacy.pokaz_pozycje();
	orientacja = strzelajacy.pokaz_orientacje();
	predkosc = PRED;
	sila = strzelajacy.pokaz_sile();
}

Pocisk::Pocisk(const Pocisk &wzor)
{
	liczebnosc++;
	promien = wzor.promien;
	pozycja = wzor.pozycja;
	orientacja = wzor.orientacja;
	predkosc = wzor.predkosc;
	sila = wzor.sila;
}


Pocisk::~Pocisk()
{
	liczebnosc--;
}