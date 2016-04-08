#pragma once
class Zabijalne
{
protected:
	int zycie;

public:
	virtual void uderzenie(int ile) = 0;
	bool martwy();
};
