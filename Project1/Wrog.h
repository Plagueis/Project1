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
	///Zwrocenie biezacej liczby istniejacych wrogow
	static int pokaz_ile();
	
	Wrog();
	Wrog(double x, double y);
	Wrog(Punkt &start);
	Wrog(double x, double y, int trudnosc);
	Wrog(Punkt &start, int trudnosc);
	Wrog(const Wrog &wzor);
	~Wrog();

	///Zmniejszenie parametru zycie o zadana wartosc
	virtual void uderzenie(int ile);
	///Zwrocenie parametru punkty
	int pokaz_punkty();
};