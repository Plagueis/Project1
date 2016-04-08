#pragma once
#include"Punkt.h"
#include"Istota.h"
class Bonus : public Istota
{
private:
	int moc;
	int punkty;
	static int liczebnosc;
public:
	static int pokaz_ile();

	Bonus(Punkt start, int ile, int cena);
	Bonus(double x, double y, int ile, int cena);
	Bonus(const Bonus & wzor);
	~Bonus();

	int pokaz_moc();
	int pokaz_punkty();
};
