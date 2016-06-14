#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
#include<vector>
#include<string>

#include"Gracz.h"
#include"Wrog.h"
#include"Pocisk.h"
#include"Bonus.h"
#include"Baza.h"
#include"Grupa.h"
#include"Gra.h"
#include"Sterowanie.h"
#include"Panel.h"

using namespace std;



int main()
{
	srand(int(time(NULL)));

	Gra gra;

	sf::RenderWindow okno(sf::VideoMode(gra.mapa.pokaz_szerokosc(), gra.mapa.pokaz_wysokosc()+gra.panel.pokaz_wysokosc()), "Prototyp", sf::Style::Close);

	sf::CircleShape Gr(float(gra.gracz.pokaz_promien()), 3);
	Gr.setOrigin(10, 10);
	Gr.setFillColor(sf::Color::Green);

	sf::CircleShape Wr(10.f, 3);
	Wr.setFillColor(sf::Color::Blue);
	Wr.setOrigin(10, 10);

	sf::CircleShape Ba(15.f);
	Ba.setFillColor(sf::Color::Yellow);
	Ba.setOrigin(15, 15);

	sf::CircleShape Bo(8.f);
	Bo.setFillColor(sf::Color::Cyan);
	Bo.setOrigin(8, 8);

	sf::CircleShape Po(3.f);
	Po.setFillColor(sf::Color::White);
	Po.setOrigin(3, 3);

	sf::RectangleShape zielony(sf::Vector2f(float(gra.panel.pokaz_dlugosc_paska()), float(gra.panel.pokaz_wysokosc()/2)));
	sf::RectangleShape czerwony(sf::Vector2f(float(gra.panel.pokaz_stan_paska()), float(gra.panel.pokaz_wysokosc()/2)));
	sf::RectangleShape pasek(sf::Vector2f(gra.panel.pokaz_szerokosc(), gra.panel.pokaz_wysokosc()));
	zielony.setPosition(0, gra.mapa.pokaz_wysokosc()+ gra.panel.pokaz_wysokosc() / 2);
	czerwony.setPosition(0, gra.mapa.pokaz_wysokosc()+ gra.panel.pokaz_wysokosc() / 2);
	pasek.setPosition(0, gra.mapa.pokaz_wysokosc());
	zielony.setFillColor(sf::Color::Green);
	czerwony.setFillColor(sf::Color::Red);
	pasek.setFillColor(sf::Color::Magenta);

	sf::Text licznik_czasu, licznik_pkt, licznik_ulepszen;
	sf::Font czcionka;

	czcionka.loadFromFile("arial.ttf");
	
	licznik_czasu.setFont(czcionka);
	licznik_pkt.setFont(czcionka);
	licznik_ulepszen.setFont(czcionka);
	
	licznik_czasu.setCharacterSize(gra.panel.pokaz_wysokosc() / 2);
	licznik_pkt.setCharacterSize(gra.panel.pokaz_wysokosc() / 2);
	licznik_ulepszen.setCharacterSize(gra.panel.pokaz_wysokosc() / 2);
	
	licznik_czasu.setPosition(gra.mapa.pokaz_szerokosc() * 2 / 3, gra.mapa.pokaz_wysokosc() + gra.panel.pokaz_wysokosc() / 2);
	licznik_pkt.setPosition(gra.mapa.pokaz_szerokosc() * 2 / 3, gra.mapa.pokaz_wysokosc());
	licznik_ulepszen.setPosition(0, gra.mapa.pokaz_wysokosc());


	while (1)
	{

		Gr.setFillColor(sf::Color::Green);
		gra.gracz.trafiony = 0;

		gra.pobierz_biezacy_czas();

		gra.sterowanie.aktualizuj_przyciski();
		gra.sterowanie.aktualizuj_pozycje_myszy(okno);


		gra.tworzenie_nowych_istot();

		gra.pobierz_jednostke_czasu();
		gra.porusz();

		gra.wystartuj_naliczanie_jednostki_czasu();

		gra.trafienia_pociskow();
		gra.starcie_gracza_z_wrogami();
		gra.zbieranie_bonusow();

		gra.koryguj_ustawienie();

		gra.panel.aktualizuj(gra.gracz, gra.zegar);

		okno.clear();

		if(gra.gracz.trafiony)
			Gr.setFillColor(sf::Color::Red);

			for (int i = 0; i < gra.bazy.rozmiar(); i++)
			{
				
				Ba.setPosition(float(gra.bazy[i]->pokaz_pozycje().X()), float(gra.bazy[i]->pokaz_pozycje().Y()));
				Ba.setOrigin(float(gra.bazy[i]->pokaz_promien()), float(gra.bazy[i]->pokaz_promien()));
				Ba.setRadius(float(gra.bazy[i]->pokaz_promien()));
				Ba.setFillColor(sf::Color::Yellow);
				okno.draw(Ba);
			}


			for (int i = 0; i < gra.apteczka.rozmiar(); i++)
			{
					Bo.setPosition(float(gra.apteczka[i]->pokaz_pozycje().X()), float(gra.apteczka[i]->pokaz_pozycje().Y()));
					okno.draw(Bo);
			}


			for (int i = 0; i < gra.armia.rozmiar(); i++)
			{
				Wr.setPosition(float(gra.armia[i]->pokaz_pozycje().X()), float(gra.armia[i]->pokaz_pozycje().Y()));
				Wr.setRotation(float(gra.armia[i]->pokaz_orientacje()));
				okno.draw(Wr);
			}

			for (int i = 0; i < gra.seria.rozmiar(); i++)
			{
				Po.setPosition(float(gra.seria[i]->pokaz_pozycje().X()), float(gra.seria[i]->pokaz_pozycje().Y()));
				Po.setRotation(float(gra.seria[i]->pokaz_orientacje()));
				okno.draw(Po);
			}

		Gr.setPosition(float(gra.gracz.pokaz_pozycje().X()), float(gra.gracz.pokaz_pozycje().Y()));
		Gr.setRotation(float(gra.gracz.pokaz_orientacje()));
		okno.draw(Gr);


		czerwony.setSize(sf::Vector2f(float(gra.panel.pokaz_dlugosc_paska()), float(gra.panel.pokaz_wysokosc()/2)));
		zielony.setSize(sf::Vector2f(float(gra.panel.pokaz_stan_paska()), float(gra.panel.pokaz_wysokosc() /2)));
		zielony.setPosition(0, gra.mapa.pokaz_wysokosc() + gra.panel.pokaz_wysokosc() / 2);
		czerwony.setPosition(0, gra.mapa.pokaz_wysokosc() + gra.panel.pokaz_wysokosc() / 2);
		pasek.setPosition(0, gra.mapa.pokaz_wysokosc());
		okno.draw(pasek);
		okno.draw(czerwony);
		okno.draw(zielony);


		licznik_czasu.setString(gra.panel.pokaz_zegar());

		licznik_pkt.setString(gra.panel.pokaz_punkty());

		licznik_ulepszen.setString(gra.panel.pokaz_poziom());

		okno.draw(licznik_czasu);
		okno.draw(licznik_pkt);
		okno.draw(licznik_ulepszen);

		okno.display();

		if (gra.gracz.martwy())
			break;

	
	}

	okno.close();
	cout << "YOU LOST" << endl;
	cout << gra.gracz.pokaz_punkty() << endl;
	system("PAUSE");
	return 0;
}
