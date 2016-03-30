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
	Wrog();
	Wrog(double x, double y);
	Wrog(Punkt &start);
	Wrog(const Wrog &wzor);
	~Wrog();
};