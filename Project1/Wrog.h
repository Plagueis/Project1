#pragma once
#include "Istota.h"
class Gracz;
class Wrog : public Istota
{
private:
	
	int sila;
	int wartosc;
	int zycie;

public:
	static int liczebnoscW;
	void atak(Gracz &cel);
	void uderzony(int ile);
	bool martwy();
	int lup();
	Wrog();
	Wrog(double x, double y);
	Wrog(Punkt &start);
	Wrog(double x, double y, int trudnosc);
	Wrog(Punkt &start, int trudnosc);
	Wrog(const Wrog &wzor);
	~Wrog();
};