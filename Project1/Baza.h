#pragma once
#include "Istota.h"
#include "Zabijalne.h"
class Baza : public Istota, public Zabijalne
{
private:

	int punkty;
	static int liczebnosc;

public:
	static int pokaz_ile();
	

	Baza(const Punkt &lokalizacja);
	Baza(double x, double y);
	Baza(const Punkt & lokalizacja, int trudnosc);
	Baza(double x, double y, int trudnosc);
	Baza(const Baza &wzor);
	~Baza();

	virtual void uderzenie(int ile);

	int pokaz_punkty();
};