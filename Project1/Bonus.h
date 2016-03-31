#pragma once
#include"Punkt.h"
#include"Istota.h"
class Bonus : public Istota
{
private:
	int wartosc;
public:
	static int liczebnoscB;
	Bonus(Punkt start, int wartosc);
	Bonus(double x, double y, int moc);
	Bonus(const Bonus & wzor);
	~Bonus();
	int moc();
};
