#pragma once
#include "Istota.h"
#include "Zabijalne.h"
class Gracz : public Istota, public Zabijalne
{
private:

	int limit_zycia;
	int punkty;
	int sila;
	int poziom;

public:

	bool trafiony;
	Gracz();
	Gracz(int ile_zycia);
	///Dodanie zadanej ilosci punktow
	void dodaj_punkty(int ile);
	///Przywrocenie zadanej ilosci zycia
	void przywroc_zycie(int ile);
	///Zwiekszenie poziomu
	void awans(int ktory);
	///Zmniejszenie zycia o zadana wartosc
	virtual void uderzenie(int ile);

	///Zwrocenie biezacej ilosci punktow
	int pokaz_punkty();
	///Zwrocenie biezacej ilosci zycia
	int pokaz_zycie();
	///Zwrocenie biezacego limitu zycia
	int pokaz_limit_zycia();
	///Zwrocenie biezacej sily
	int pokaz_sile();
	///Zwrocenie biezacego poziomu
	int pokaz_poziom();
};