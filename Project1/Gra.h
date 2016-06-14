#pragma once
#include"Grupa.h"
#include"Gracz.h"
#include"Wrog.h"
#include"Pocisk.h"
#include"Baza.h"
#include"Bonus.h"
#include"Mapa.h"
#include"Panel.h"
#include"Sterowanie.h"
#include"Punkt.h"
#include <SFML/Graphics.hpp>
class Gra
{
private:
	int trudnosc, taktowanie_wrogow, taktowanie_pociskow, taktowanie_bonusow, taktowanie_baz;
	int max_baz, max_bonus, min_bonus;
	double f_pocisk, f_wrog, f_baza, f_bonus, f_trudnosci;
public:
	Gracz gracz;
	Grupa<Wrog> armia;
	Grupa<Pocisk> seria;
	Grupa<Baza> bazy;
	Grupa<Bonus> apteczka;
	Sterowanie sterowanie;
	Mapa mapa;
	Panel panel;
	sf::Time czas, dt;
	sf::Clock zegar;

	Gra();
	void wystartuj_naliczanie_jednostki_czasu();
	void pobierz_jednostke_czasu();
	void pobierz_biezacy_czas();
	void trafienia_pociskow();
	void zbieranie_bonusow();
	void starcie_gracza_z_wrogami();
	void porusz();
	void koryguj_ustawienie();
	void tworzenie_nowych_istot();

};