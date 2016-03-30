#pragma once

class Punkt
{
private:
	double oX;
	double oY;
public:
	void ustaw (double x, double y);
	void przesun(double x, double y);
	int X();
	int Y();
	double odleglosc(Punkt &punkt);
	Punkt();
	Punkt(double x, double y);
	Punkt(const Punkt &wzor);
	Punkt operator= (const Punkt &wzor);
};