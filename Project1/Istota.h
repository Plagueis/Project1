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
	void zorientuj(Punkt &cel);
	void rusz(double czas);
	void popchnij(double dystans);
	void ustaw(double x, double y);
	void ustaw(Punkt &miejsce);
	void rozsun(Istota &cel);
	bool w_kontakcie_z(Istota &cel);

	Punkt pokaz_pozycje();
	int pokaz_promien();
	double pokaz_orientacje();
	
	
	
};