#pragma once
#include "Istota.h"
#include "Grozne.h"
#include "Zabijalne.h"
class Gracz;
class Wrog : public Istota, public Grozne, public Zabijalne
{
private:
	
	int punkty;
	static int liczebnosc;
public:
	static int pokaz_ile();
	
	Wrog();
	Wrog(double x, double y);
	Wrog(Punkt &start);
	Wrog(double x, double y, int trudnosc);
	Wrog(Punkt &start, int trudnosc);
	Wrog(const Wrog &wzor);
	~Wrog();

	virtual void uderzenie(int ile);
	
	int pokaz_punkty();
};