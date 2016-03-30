#include "Bonus.h"
#include <cstdlib>
#include <ctime>


Bonus::Bonus(Punkt start, int los)
{
	pozycja = start;
	typ = los % 4;
}

int Bonus::jaki()
{
	return typ;
}
