#include "Wrog.h"
#include "Gracz.h"

#define PRED 2

int Wrog::liczebnoscW = 0;


void Wrog::atak(Gracz &cel)
{
	cel.uderzony(sila);
}

void Wrog::uderzony(int ile)
{
	zycie -= ile;
}

bool Wrog::martwy()
{
	if (zycie > 0)
		return false;
	else
		return true;
}

Wrog::Wrog()
{
	liczebnoscW++;
	sila = 1;
	wartosc = 10;
	zycie = 5;
	promien = 10;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(double x, double y)
{
	liczebnoscW++;
	sila = 1;
	wartosc = 10;
	zycie = 5;
	promien = 10;
	Punkt start(x, y);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(Punkt &start)
{
	liczebnoscW++;
	sila = 1;
	wartosc = 10;
	zycie = 5;
	promien = 10;
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(const Wrog & wzor)
{

	liczebnoscW++;
	sila = wzor.sila;
	wartosc = wzor.wartosc;
	zycie = wzor.zycie;
	promien = wzor.promien;
	pozycja = wzor.pozycja;
	orientacja = wzor.orientacja;
	predkosc = wzor.predkosc;

}

Wrog::~Wrog()
{
	liczebnoscW--;
}

