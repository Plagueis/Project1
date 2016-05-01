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
	///Obrot istoty o zadany kat
	void obroc(double stopnie);

	///Zorientowanie istoty w zadanym kierunku
	void zorientuj(double stopnie);

	///Zorientowanie istoty w kierunku zadanego punktu
	void zorientuj(Punkt &cel);

	///Poruszenie istoty w biezacym kierunku w zadanej jednostce czasu
	void rusz(double czas);

	///Poruszenie istoty w biezacym kierunku o zadany dystans
	void popchnij(double dystans);

	///Ustawienie istoty na zadanych koordynatach
	void ustaw(double x, double y);

	///Ustawienie istoty na zadanym punkcie
	void ustaw(Punkt &miejsce);

	///Rozsuniecie potencjalnie zachodzacych na siebie istot
	void rozsun(Istota &cel);

	///Zmiana pozycji istoty, tak aby znajdowala sie wewnatrz prostokata o wspolrzednych (0,0)(x,0)(x,y)(0,y)
	void zamknij_w_prostokacie(int oX, int oY);

	///Sprawdzenie czy istoty sa w kontakcie
	bool w_kontakcie_z(Istota &cel);

	Punkt pokaz_pozycje();
	int pokaz_promien();
	double pokaz_orientacje();
	
	virtual ~Istota();
	
};