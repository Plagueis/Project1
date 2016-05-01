#pragma once
class Zabijalne;
class Grozne
{
protected:
	int sila;
public:
	//Zadanie obrazen wybranemu celowi
	void atak(Zabijalne &cel);
	virtual ~Grozne();
};
