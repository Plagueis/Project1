#pragma once
#include "Istota.h"
class Wrog;
class Gracz;
class Baza;
class Pocisk : public Istota
{
private:
	static int sila;
public:
	static int liczebnoscP;
	void atak(Wrog &cel);
	void atak(Baza &cel);
	static void premia();
	Pocisk(Gracz &strzelajacy);
	Pocisk(const Pocisk & wzor);
	~Pocisk();
};