#pragma once
#include "Istota.h"
#include "Zabijalne.h"
class Gracz : public Istota, public Zabijalne
{
private:

	int limit_zycia;
	int punkty;
	int sila;

public:

	Gracz();
	Gracz(int ile_zycia);

	void dodaj_punkty(int ile);
	void przywroc_zycie(int ile);
	void awans(int ktory);
	virtual void uderzenie(int ile);

	int pokaz_punkty();
	int pokaz_zycie();
	int pokaz_limit_zycia();
	int pokaz_sile();
};