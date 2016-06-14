#include "Panel.h"

Panel::Panel(int szer,int wys)
{
	szerokosc = szer;
	wysokosc = wys;
	dlugosc_paska = 0;
	stan_paska = 0;
	zegar = poziom = punkty = "0";
}

void Panel::aktualizuj(Gracz gracz, sf::Clock czas)
{
	dlugosc_paska = gracz.pokaz_limit_zycia()/4;
	stan_paska = gracz.pokaz_zycie()/4;
	poziom = "Lvl: " + to_string(gracz.pokaz_poziom());
	punkty = "Pts: " + to_string(gracz.pokaz_punkty());
	int czasomierz = int(czas.getElapsedTime().asSeconds());
	zegar = to_string(czasomierz / 3600);
	zegar += ":";
	if (czasomierz / 60 < 10)
	{
		zegar += "0";
		zegar += to_string(czasomierz / 60);
	}
	else
	{
		zegar += to_string(czasomierz / 60);
	}
	zegar += ":";
	if (czasomierz % 60 < 10)
	{
		zegar += "0";
		zegar += to_string(czasomierz % 60);
	}
	else
	{
		zegar += to_string(czasomierz % 60);
	}
}

int Panel::pokaz_szerokosc()
{
	return szerokosc;
}

int Panel::pokaz_wysokosc()
{
	return wysokosc;
}

int Panel::pokaz_dlugosc_paska()
{
	return dlugosc_paska;
}

int Panel::pokaz_stan_paska()
{
	return stan_paska;
}

string Panel::pokaz_zegar()
{
	return zegar;
}

string Panel::pokaz_poziom()
{
	return poziom;
}

string Panel::pokaz_punkty()
{
	return punkty;
}
