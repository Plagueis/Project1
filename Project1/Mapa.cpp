#include "Mapa.h"

Mapa::Mapa(Punkt LG, Punkt PG, Punkt PD, Punkt LD)
{
	rog[0] = LG;
	rog[1] = PG;
	rog[2] = PD;
	rog[3] = LD;
}

Punkt Mapa::pokaz_LG()
{
	return rog[0];
}

Punkt Mapa::pokaz_PG()
{
	return rog[1];
}

Punkt Mapa::pokaz_PD()
{
	return rog[2];
}

Punkt Mapa::pokaz_LD()
{
	return rog[3];
}
