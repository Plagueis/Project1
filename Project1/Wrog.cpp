#include "Wrog.h"
#include "Gracz.h"

#define PRED 2
#define PROM 10
#define SILA 1
#define ZYCIE 4
#define WART 10

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

int Wrog::lup()
{
	return wartosc;
}

Wrog::Wrog()
{
	liczebnoscW++;
	sila = SILA;
	wartosc = WART;
	zycie = ZYCIE;
	promien = PROM;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(double x, double y)
{
	liczebnoscW++;
	sila = SILA;
	wartosc = WART;
	zycie = ZYCIE;
	promien = PROM;
	Punkt start(x, y);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(Punkt &start)
{
	liczebnoscW++;
	sila = SILA;
	wartosc = WART;
	zycie = ZYCIE;
	promien = PROM;
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(double x, double y, int trudnosc)
{
	liczebnoscW++;
	sila = SILA;
	wartosc = WART+trudnosc;
	zycie = ZYCIE+0.5*trudnosc;
	promien = PROM;
	Punkt start(x, y);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(Punkt & start, int trudnosc)
{
	liczebnoscW++;
	sila = SILA;
	wartosc = WART+trudnosc;
	zycie = ZYCIE+0.5*trudnosc;
	promien = PROM;
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

