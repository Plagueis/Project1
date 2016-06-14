#include "Punkt.h"
#include <math.h>

void Punkt::ustaw (double x, double y)
{
	oX = x;
	oY = y;
}

void Punkt::przesun (double x, double y)
{
	oX += x;
	oY += y;

}


int Punkt::X()
{
	return int(round(oX));
}

int Punkt::Y()
{
	return int(round(oY));
}

double Punkt::odleglosc(Punkt &punkt)
{
	double wynik, skladowaX, skladowaY;
	skladowaX = punkt.X() - oX;
	skladowaX = skladowaX * skladowaX;
	skladowaY = punkt.Y() - oY;
	skladowaY = skladowaY * skladowaY;
	wynik = sqrt(skladowaX + skladowaY);
	return round(wynik);
}

Punkt::Punkt() : oX(0), oY(0)
{
}

Punkt::Punkt(double x, double y) : oX(x), oY(y)
{
}

Punkt::Punkt(const Punkt &wzor)
{
	oX = wzor.oX;
	oY = wzor.oY;
}

Punkt Punkt::operator=(const Punkt &wzor)
{
	this->oX = wzor.oX;
	this->oY = wzor.oY;
	return *this;
}

bool Punkt::operator!=(const Punkt &porownywany)
{
	if (this->oX != porownywany.oX)
		return true;
	if (this->oY != porownywany.oY)
		return true;
	return false;
}
