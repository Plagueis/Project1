#include "Zabijalne.h"

bool Zabijalne::martwy()
{
	if (zycie > 0)
		return false;
	else
		return true;
}

Zabijalne::~Zabijalne()
{
}
