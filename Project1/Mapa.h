#pragma once
#include "Punkt.h"
class Mapa
{
private:
	Punkt rog[4];
public:
	Mapa(Punkt LG, Punkt PG, Punkt PD, Punkt LD);
	Punkt pokaz_LG();
	Punkt pokaz_PG();
	Punkt pokaz_PD();
	Punkt pokaz_LD();
};