#include "Zabijalne.h"

void Zabijalne::uderzenie(int ile)
{
	zycie -= ile;
}
bool Zabijalne::martwy()
{
	if (zycie > 0)
		return false;
	else
		return true;
}