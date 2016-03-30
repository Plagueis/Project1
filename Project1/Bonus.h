#pragma once
#include"Punkt.h"
class Bonus
{
private:
	Punkt pozycja;
	int typ;
public:
	Bonus(Punkt start, int los);
	int jaki();
};
