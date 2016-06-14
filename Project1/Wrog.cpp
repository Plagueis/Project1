#include "Wrog.h"
#include "Gracz.h"

#define PRED 1
#define PROM 10
#define SILA 1
#define ZYCIE 4
#define WART 10

int Wrog::liczebnosc = 0;


void Wrog::uderzenie(int ile)
{
	zycie -= ile;
}

int Wrog::pokaz_punkty()
{
	return punkty;
}

int Wrog::pokaz_ile()
{
	return liczebnosc;
}

Wrog::Wrog()
{
	liczebnosc++;
	sila = SILA;
	punkty = WART;
	zycie = ZYCIE;
	promien = PROM;
	Punkt start(promien, promien);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(double x, double y)
{
	liczebnosc++;
	sila = SILA;
	punkty = WART;
	zycie = ZYCIE;
	promien = PROM;
	Punkt start(x, y);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(Punkt &start)
{
	liczebnosc++;
	sila = SILA;
	punkty = WART;
	zycie = ZYCIE;
	promien = PROM;
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(double x, double y, int trudnosc)
{
	liczebnosc++;
	sila = SILA;
	punkty = WART+trudnosc;
	zycie = int(ZYCIE+0.5*trudnosc);
	promien = PROM;
	Punkt start(x, y);
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(Punkt & start, int trudnosc)
{
	liczebnosc++;
	sila = SILA;
	punkty = WART+trudnosc;
	zycie = int(ZYCIE+0.5*trudnosc);
	promien = PROM;
	pozycja = start;
	orientacja = 0;
	predkosc = PRED;
}

Wrog::Wrog(const Wrog & wzor)
{

	liczebnosc++;
	sila = wzor.sila;
	punkty = wzor.punkty;
	zycie = wzor.zycie;
	promien = wzor.promien;
	pozycja = wzor.pozycja;
	orientacja = wzor.orientacja;
	predkosc = wzor.predkosc;

}

Wrog::~Wrog()
{
	liczebnosc--;
}

