#pragma once
class Zabijalne
{
protected:
	int zycie;

public:
	///Zmniejszenie parametru zycie o zadana zartosc
	virtual void uderzenie(int ile) = 0;
	///Sprawdzenie czy obiekt jest zywy czy martwy
	bool martwy();
	virtual ~Zabijalne();
};
