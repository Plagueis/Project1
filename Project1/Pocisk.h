#pragma once
#include "Istota.h"
#include "Grozne.h"
class Wrog;
class Gracz;
class Baza;
class Pocisk : public Istota, public Grozne
{
private:

	static int liczebnosc;
public:
	static int pokaz_ile();
	

	Pocisk(Gracz &strzelajacy);
	Pocisk(const Pocisk & wzor);
	~Pocisk();


};