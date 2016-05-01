#pragma once
#include "Istota.h"
#include "Grozne.h"
class Gracz;
class Baza;
class Pocisk : public Istota, public Grozne
{
private:

	static int liczebnosc;
public:
	///Zwrocenie biezacej ilosci istniejacych pociskow
	static int pokaz_ile();
	

	Pocisk(Gracz &strzelajacy);
	Pocisk(const Pocisk & wzor);
	~Pocisk();


};