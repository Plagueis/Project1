#pragma once
#include"Punkt.h"
#include"Istota.h"
class Bonus : public Istota
{
private:
	int leczenie;
	int wartosc;
public:
	static int liczebnoscB;
	Bonus(Punkt start, int moc, int cena);
	Bonus(double x, double y, int moc, int cena);
	Bonus(const Bonus & wzor);
	~Bonus();
	int moc();
	int lup();
};
