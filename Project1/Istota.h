#pragma once
#include "Punkt.h"

class Istota
{
protected:
	Punkt pozycja;
	double orientacja;
	int promien;
	double predkosc;
public:
	void obroc(double stopnie);
	void zorientuj(double stopnie);
	void rusz(double czas);
	void popchnij(double dystans);
	Punkt gdzie();
	int rozmiar();
	double kierunek();
	void zorientuj(Punkt &cel);
	bool kontakt(Istota &cel);
	void ustaw(Punkt &miejsce);
	void ustaw(double x, double y);
	void odsun(Istota &cel);
};