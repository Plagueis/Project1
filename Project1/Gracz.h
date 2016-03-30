#pragma once
#include "Istota.h"
class Gracz : public Istota
{
private:
	int punkty;
	int zycie;
	int zarobek;
public:
	void uderzony(int ile);
	void zdobycz(int ile);
	int zdrowie();
	bool martwy();
	Gracz();
};