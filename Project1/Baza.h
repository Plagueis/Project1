#pragma once
#include "Istota.h"
class Baza : public Istota
{
private:
	int zycie;
	int wartosc;
public:
	static int liczebnoscBaz;
	Punkt gdzie();
	int rozmiar();
	Baza(const Punkt &lokalizacja);
	Baza(double x, double y);
	Baza(const Punkt & lokalizacja, int trudnosc);
	Baza(double x, double y, int trudnosc);
	Baza(const Baza &wzor);
	~Baza();
	void uderzona(int ile);
	bool martwa();
	int lup();
};