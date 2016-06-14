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

Punkt Istota::pokaz_pozycje()
{
	return pozycja;
}

int Istota::pokaz_promien()
{
	return promien;
}

double Istota::pokaz_orientacje()
{
	return orientacja;
}

Istota::~Istota()
{
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

bool Istota::w_kontakcie_z(Istota &cel)
{
	if (pozycja.odleglosc(cel.pozycja) > promien + cel.pokaz_promien())
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

void Istota::rozsun(Istota &cel)
{
	if (this->w_kontakcie_z(cel))
	{
		if (pozycja.X() == cel.pokaz_pozycje().X())
			if (pozycja.Y() == cel.pokaz_pozycje().Y())
				cel.popchnij(5);

		double ile = double((promien + cel.pokaz_promien())) - pozycja.odleglosc(cel.pozycja);
		
		double pierwotnie = this->pokaz_orientacje();
		this->zorientuj(cel.pokaz_pozycje());
		this->obroc(180);
		this->popchnij(ile/2);
		this->zorientuj(pierwotnie);

		pierwotnie = cel.pokaz_orientacje();
		cel.zorientuj(this->pokaz_pozycje());
		cel.obroc(180);
		cel.popchnij(ile / 2);
		cel.zorientuj(pierwotnie);


	}
}

void Istota::zamknij_w_prostokacie(int oX, int oY)
{
	if (pozycja.X() < promien)
	{
		this->ustaw(promien, pozycja.Y());
	}
	if (pozycja.Y() < promien)
	{
		this->ustaw(pozycja.X(), promien);
	}
	if (pozycja.X() > oX - promien)
	{
		this->ustaw(oX - promien, pozycja.Y());
	}
	if (pozycja.Y() > oY - promien)
	{
		this->ustaw(pozycja.X(), oY - promien);
	}
}

void Istota::zamknij_w_prostokacie(Mapa mapa)
{
	if (pozycja.X() < promien + mapa.pokaz_LD().X())
	{
		this->ustaw(promien, pozycja.Y());
	}
	if (pozycja.Y() < promien + mapa.pokaz_LG().Y())
	{
		this->ustaw(pozycja.X(), promien);
	}
	if (pozycja.X() > mapa.pokaz_PD().X() - promien)
	{
		this->ustaw(mapa.pokaz_PD().X() - promien, pozycja.Y());
	}
	if (pozycja.Y() > mapa.pokaz_PD().Y() - promien)
	{
		this->ustaw(pozycja.X(), mapa.pokaz_PD().Y() - promien);
	}
}


