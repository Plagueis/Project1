#pragma once
#include "Istota.h"
class Gracz : public Istota
{
private:
	int punkty;
	int zycie;
	int zycie_poczatkowe;
	int zarobek;
public:
	void uderzony(int ile);
	void zdobycz(int ile);
	void lecz(int ile);
	void premia();
	int dorobek();
	int zdrowie();
	int pojemnosc_zdrowia();
	bool martwy();
	Gracz();
	Gracz(int ile_zycia);
};