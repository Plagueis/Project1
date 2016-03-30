#include "Istota.h"
#include <math.h>
#include<iostream>
#define PI 3.14159

void Istota::obroc(double stopnie)
{
	orientacja += stopnie;
	while(orientacja >= 360)
		orientacja -= 360;
}

void Istota::zorientuj(double stopnie)
{
	orientacja = stopnie;
}

void Istota::rusz(double czas)
{
	double ileX, ileY;
	double dystans;
	dystans = predkosc * czas;
	ileX = dystans * sin((orientacja * PI) / 180);
	ileY = dystans * cos((orientacja * PI) / 180);
	pozycja.przesun(ileX, -ileY);
}

void Istota::popchnij(double dystans)
{
	double ileX, ileY;
	ileX = dystans * sin((orientacja * PI) / 180);
	ileY = dystans * cos((orientacja * PI) / 180);
	pozycja.przesun(ileX, -ileY);
}

Punkt Istota::gdzie()
{
	return pozycja;
}

int Istota::rozmiar()
{
	return promien;
}

double Istota::kierunek()
{
	return orientacja;
}

void Istota::zorientuj(Punkt &cel)
{
	Punkt lokalizacja(pozycja);
	double przeciwprostokatna = cel.odleglosc(lokalizacja);
	double argument, stara;
	stara = orientacja;



	if (abs(cel.X() - lokalizacja.X())<1)
	{
		if (cel.Y() > lokalizacja.Y())
			orientacja = 180;
		
		if (cel.Y() < lokalizacja.Y())
			orientacja = 0;

	}
	else if (abs(cel.Y() - lokalizacja.Y())<1)
	{
		if (cel.X() > lokalizacja.X())
			orientacja = 90;

		if (cel.X() < lokalizacja.X())
			orientacja = 270;

	}
	else
	{
		if (cel.Y() < lokalizacja.Y() && cel.X() > lokalizacja.X())
		{
			argument = abs(cel.X() - lokalizacja.X());
			argument /= przeciwprostokatna;
			orientacja = asin(argument);
			orientacja /= PI;
			orientacja *= 180;

		}
		if (cel.Y() > lokalizacja.Y() && cel.X() > lokalizacja.X())
		{
			argument = abs(cel.Y() - lokalizacja.Y());
			argument /= przeciwprostokatna;
			orientacja = asin(argument);
			orientacja /= PI;
			orientacja *= 180;
			orientacja += 90;
		}
		if (cel.Y() > lokalizacja.Y() && cel.X() < lokalizacja.X())
		{
			argument = abs(cel.X() - lokalizacja.X());
			argument /= przeciwprostokatna;
			orientacja = asin(argument);
			orientacja /= PI;
			orientacja *= 180;
			orientacja += 180;
		}
		if (cel.Y() < lokalizacja.Y() && cel.X() < lokalizacja.X())
		{
			argument = abs(cel.Y() - lokalizacja.Y());
			argument /= przeciwprostokatna;
			orientacja = asin(argument);
			orientacja /= PI;
			orientacja *= 180;
			orientacja += 270;
		}



	}
	if (isnan(orientacja))
		orientacja = stara;

}

bool Istota::kontakt(Istota &cel)
{
	if (pozycja.odleglosc(cel.pozycja) > promien + cel.rozmiar())
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

void Istota::ustaw(Punkt &miejsce)
{
	pozycja = miejsce;
}

void Istota::ustaw(double x, double y)
{
	Punkt miejsce(x, y);
	pozycja = miejsce;
}
//aaaa
void Istota::odsun(Istota &cel)
{
	Istota nasza = *this;
	if (nasza.kontakt(cel))
	{
		double ile = double((promien + cel.rozmiar())) - pozycja.odleglosc(cel.pozycja);
		
		double pierwotnie = nasza.kierunek();
		nasza.zorientuj(cel.gdzie());
		nasza.obroc(180);
		nasza.popchnij(ile/2);
		nasza.zorientuj(pierwotnie);

		pierwotnie = cel.kierunek();
		cel.zorientuj(nasza.gdzie());
		cel.obroc(180);
		cel.popchnij(ile / 2);
		cel.zorientuj(pierwotnie);

		*this = nasza;


	}
}


