#pragma once
#include "Istota.h"
class Wrog;
class Gracz;
class Pocisk : public Istota
{
private:
	int sila;
public:
	static int liczebnoscP;
	void atak(Wrog &cel);
	void premia();
	void oslabienie();
	Pocisk(Gracz &strzelajacy);
	Pocisk(const Pocisk & wzor);
	~Pocisk();
};