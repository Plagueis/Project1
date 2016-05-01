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
	///Zwrocenie ilosci aktualnie istniejacych bonusow
	static int pokaz_ile();

	Bonus(Punkt start, int ile, int cena);
	Bonus(double x, double y, int ile, int cena);
	Bonus(const Bonus & wzor);
	~Bonus();

	///Zwrocenie mocy
	int pokaz_moc();
	///Zwrocenie wartosci punktowej
	int pokaz_punkty();
};
