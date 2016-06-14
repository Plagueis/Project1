#pragma once

class Punkt
{
private:
	double oX;
	double oY;
public:
	///Ustawienie punktu na zadanych koordynatach
	void ustaw (double x, double y);
	///Przesuniecie punktu o zadany wektor
	void przesun(double x, double y);
	///Zwrocenie wartosci X
	int X();
	///Zwrocenie wartosci Y
	int Y();
	///Zwrocenie odleglosci pomiedzy punktami
	double odleglosc(Punkt &punkt);
	Punkt();
	Punkt(double x, double y);
	Punkt(const Punkt &wzor);
	Punkt operator= (const Punkt &wzor);
	bool Punkt::operator!=(const Punkt &porownywany);
};