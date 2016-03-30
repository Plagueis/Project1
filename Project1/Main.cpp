#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
#include<vector>

#include"Gracz.h"
#include"Wrog.h"
#include"Pocisk.h"

#define ILOSC_BAZ 4
#define SZEROKOSC 1000
#define WYSOKOSC 500

using namespace std;

int main()
{

///////////////////////////
///STWORZENIE OKNA////////
/////////////////////////
	sf::RenderWindow okno(sf::VideoMode(SZEROKOSC, WYSOKOSC), "Prototyp", sf::Style::Close);

///////////////////////////////////////////	
////DEKLARACJA ZMIENNYCH POMOCNICZYCH/////
/////////////////////////////////////////
	bool L, P, G, D;
	int taktowanie_wrogow=0, taktowanie_pociskow=0;

//////////////////////////////////////////////////
///DEKLARACJA CHARAKTERYSTYCZNYCH PUNKTOW MAPY///
////////////////////////////////////////////////
	Punkt baza[ILOSC_BAZ];
	baza[0].ustaw(100, 100);
	baza[1].ustaw(800, 100);
	baza[2].ustaw(100, 400);
	baza[3].ustaw(800, 400);
	Punkt mysz;


///////////////////////////////////////////////////////////////////////
///STWORZENIE NARZEDZI DO DYNAMICZNEJ OBSLUGI POCISKOW I WROGOW///////
/////////////////////////////////////////////////////////////////////
	Pocisk *wsk2;
	vector<Pocisk>seria;
	Wrog *wsk1;
	vector<Wrog>armia;

///////////////////////////////////////////////
////POWOLANIE DO ZYCIA POCZATKOWYCH WROGOW////
/////////////////////////////////////////////
	wsk1 = new Wrog;
	armia.push_back(*wsk1);
	armia.push_back(*wsk1);
	armia.push_back(*wsk1);
	armia.push_back(*wsk1);
	delete wsk1;
	armia[0].ustaw(baza[0]);
	armia[1].ustaw(baza[1]);
	armia[2].ustaw(baza[2]);
	armia[3].ustaw(baza[3]);
	

/////////////////////////////////
////POWOLANIE DO ZYCIA GRACZA///
///////////////////////////////
	Gracz gracz;
	Punkt start(SZEROKOSC/2, WYSOKOSC/2);
	gracz.ustaw(start);


///////////////////////////////////
/////STWORZENIE MODELU GRACZA/////
/////////////////////////////////
	sf::CircleShape Gr(float(gracz.rozmiar()), 3);
	Gr.setOrigin(10, 10);
	Gr.setFillColor(sf::Color::Green);

//////////////////////////////////
/////STWORZENIE MODELU WROGA/////
////////////////////////////////
	sf::CircleShape Wr(10.f, 3);
	Wr.setFillColor(sf::Color::Blue);
	Wr.setOrigin(10, 10);

////////////////////////////////////
/////STWORZENIE MODELU POCISKU/////
//////////////////////////////////
	sf::CircleShape Po(3.f);
	Po.setFillColor(sf::Color::White);
	Po.setOrigin(3, 3);

///////////////////////////////////
///////STWORZENIE MODELU PASKA////
/////////////////////////////////
	sf::RectangleShape zielony(sf::Vector2f(300, 30));
	sf::RectangleShape czerwony(sf::Vector2f(300, 30));
	zielony.setPosition(0, 0);
	czerwony.setPosition(0, 0);
	zielony.setFillColor(sf::Color::Green);
	czerwony.setFillColor(sf::Color::Red);

//////////////////////////////////////
////UTWORZENIE ZMIENNYCH CZASOWYCH///
////////////////////////////////////
	sf::Time czas, dt;
	sf::Clock zegar;
	dt = zegar.getElapsedTime();
	srand(int(time(NULL)));


//////////////////////////////////
/////WEJSCIE DO PETLI GLOWNEJ////
////////////////////////////////
	while (1)
	{

///////////////////////////
////RESET STANU GRACZA////
/////////////////////////
		Gr.setFillColor(sf::Color::Green);

//////////////////////////////////////
////POBRANIE BIEZACEGO CZASU GRY/////
////////////////////////////////////
		czas = zegar.getElapsedTime();

/////////////////////////////////		
///POBRANIE DANYCH STEROWANIA///
///////////////////////////////
		L = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		P = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		G = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		D = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		mysz.ustaw(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y);

/////////////////////////////////
///GENEROWANIE NOWEGO WROGA/////
///////////////////////////////

			if(taktowanie_wrogow != int(round(czas.asSeconds())))
			{
				wsk1 = new Wrog(baza[rand() % ILOSC_BAZ]);
				armia.push_back(*wsk1);
				delete wsk1;
			}
			taktowanie_wrogow = int(round(czas.asSeconds()));




///////////////////////////////////
///GENEROWANIE NOWEGO POCISKU/////
/////////////////////////////////

			if (taktowanie_pociskow != int(round(czas.asSeconds()*10)))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && seria.size() < 5)
				{
				wsk2 = new Pocisk(gracz);
				seria.push_back(*wsk2);
				delete wsk2;

				}
				
			
			}
			taktowanie_pociskow = int(round(czas.asSeconds()*10));







/////////////////////////////////
///POBRANIE JEDNOSTKI CZASU/////
///////////////////////////////
		dt = zegar.getElapsedTime() - dt;
		



////////////////////////
////RUCH GRACZA////////
//////////////////////
		if (L==1 && P==0 && G==0 && D==0)
		{ 		gracz.zorientuj(270);
				gracz.rusz(dt.asSeconds()*100);
		}
		if (L == 0 && P == 1 && G == 0 && D == 0)
		{
			gracz.zorientuj(90);
			gracz.rusz(dt.asSeconds() * 100);
		}
		if (L == 0 && P == 0 && G == 1 && D == 0)
		{
			gracz.zorientuj(0);
			gracz.rusz(dt.asSeconds() * 100);
		}
		if (L == 0 && P == 0 && G == 0 && D == 1)
		{
			gracz.zorientuj(180);
			gracz.rusz(dt.asSeconds() * 100);
		}
		if (L == 0 && P == 1 && G == 1 && D == 0)
		{
			gracz.zorientuj(45);
			gracz.rusz(dt.asSeconds() * 100);
		}
		if (L == 0 && P == 1 && G == 0 && D == 1)
		{
			gracz.zorientuj(135);
			gracz.rusz(dt.asSeconds() * 100);
		}
		if (L == 1 && P == 0 && G == 0 && D == 1)
		{
			gracz.zorientuj(225);
			gracz.rusz(dt.asSeconds() * 100);
		}
		if (L == 1 && P == 0 && G == 1 && D == 0)
		{
			gracz.zorientuj(315);
			gracz.rusz(dt.asSeconds() * 100);
		}
		





/////////////////////
///RUCH WROGOW//////
///////////////////
		if (Wrog::liczebnoscW)
		{
			for (int i = 0; i < Wrog::liczebnoscW; i++)
				{
					armia[i].zorientuj(gracz.gdzie());
					armia[i].rusz(dt.asSeconds() * 100);

					if (armia[i].kontakt(gracz))
						{
							armia[i].atak(gracz);
							Gr.setFillColor(sf::Color::Red);
						}
				}
		}


/////////////////////////
///RUCH POCISKOW////////
///////////////////////
		if (Pocisk::liczebnoscP)
		{
			for (int i = 0; i < Pocisk::liczebnoscP; i++)
				seria[i].rusz(dt.asSeconds() * 100);
		}


////////////////////////////
//START JEDNOSTKI CZASU////
//////////////////////////
		dt = zegar.getElapsedTime();

//////////////////////////////////
//OBROT GRACZA W STRONE MYSZY////
////////////////////////////////
		gracz.zorientuj(mysz);


		
////////////////////////////////////
/////ZAMKNIECIE GRACZA W PLANSZY///
//////////////////////////////////
		if (gracz.gdzie().X() < gracz.rozmiar())
		{
			gracz.ustaw(gracz.rozmiar(), gracz.gdzie().Y());
		}
		if (gracz.gdzie().Y() < gracz.rozmiar())
		{
			gracz.ustaw(gracz.gdzie().X(), gracz.rozmiar());
		}
		if (gracz.gdzie().X() > SZEROKOSC - gracz.rozmiar())
		{
			gracz.ustaw(SZEROKOSC - gracz.rozmiar(), gracz.gdzie().Y());
		}
		if (gracz.gdzie().Y() > WYSOKOSC-gracz.rozmiar())
		{
			gracz.ustaw(gracz.gdzie().X(), WYSOKOSC - gracz.rozmiar());
		}



//////////////////////////////////
//SERIA OPERACJI NA WROGACH//////
////////////////////////////////
		if (Wrog::liczebnoscW)
		{
			//////////////////////////
			////POROZSUWANIE WROGOW///
			//////////////////////////
			for (int i = 0; i < Wrog::liczebnoscW; i++)
			{
				for (int j = i + 1; j < Wrog::liczebnoscW; j++)
				{
					armia[i].odsun(armia[j]);
				}

			}

			//////////////////////////////
			//WROGOWIE ATAKUJA GRACZA/////
			//////////////////////////////
			for (int i = 0; i < Wrog::liczebnoscW; i++)
			{
				if (armia[i].kontakt(gracz))
				{
					armia[i].atak(gracz);
					Gr.setFillColor(sf::Color::Red);
				}
			}


			/////////////////////////////////
			////WROGOWIE PRZYJMUJA POCISKI///
			/////////////////////////////////
			for (int i = 0; i < Wrog::liczebnoscW; i++)
			{

				for (int j = 0; j < Pocisk::liczebnoscP; j++)
				{
					if(Wrog::liczebnoscW && Pocisk::liczebnoscP)
					{
						if(armia[i].kontakt(seria[j]))
							{
								armia.erase(armia.begin() + i);
								seria.erase(seria.begin() + j);
								if (Wrog::liczebnoscW && Pocisk::liczebnoscP)
								{
									i = 0;
									j = 0;
								}
								else
								{
									break;
								}
							}
					}
					else
					{
						break;
					}
				}
			}
		}


///////////////////////////////////
//USUNIECIE POCISKOW POZA MAPA/////
///////////////////////////////////
		if(Pocisk::liczebnoscP)
		{
			for (int j = 0; j < Pocisk::liczebnoscP; j++)
			{
				if (seria[j].gdzie().X() < 0)
				{
					seria.erase(seria.begin() + j);
				}
				else if (seria[j].gdzie().Y() < 0)
				{
					seria.erase(seria.begin() + j);
				}
				else if (seria[j].gdzie().X() > SZEROKOSC)
				{
					seria.erase(seria.begin() + j);
				}
				else if (seria[j].gdzie().Y() > WYSOKOSC)
				{
					seria.erase(seria.begin() + j);
				}
					
				
			}
		}
		
		
//////////////////////////
///WYCZYSZCZENIE OKNA////
////////////////////////		
		okno.clear();

///////////////////////////
///RYSOWANIE WROGOW///////
/////////////////////////
		if (Wrog::liczebnoscW)
		{
			for (int i = 0; i < Wrog::liczebnoscW; i++)
			{
				Wr.setPosition(float(armia[i].gdzie().X()), float(armia[i].gdzie().Y()));
				Wr.setRotation(float(armia[i].kierunek()));
				okno.draw(Wr);
			}
		}

////////////////////////////
//RYSOWANIE POCISKOW///////
//////////////////////////	
		if (Pocisk::liczebnoscP)
		{
			for (int i = 0; i < Pocisk::liczebnoscP; i++)
			{
				Po.setPosition(float(seria[i].gdzie().X()), float(seria[i].gdzie().Y()));
				Po.setRotation(float(seria[i].kierunek()));
				okno.draw(Po);
			}
		}

///////////////////////////
//RYSOWANIE GRACZA////////
/////////////////////////
		Gr.setPosition(float(gracz.gdzie().X()), float(gracz.gdzie().Y()));
		Gr.setRotation(float(gracz.kierunek()));
		okno.draw(Gr);


/////////////////////////
////RYSOWANIE PASKA/////
///////////////////////
		double procent_zdrowia = (gracz.zdrowie() * 300) / SZEROKOSC;
		czerwony.setSize(sf::Vector2f(300, 30));
		zielony.setSize(sf::Vector2f(float(procent_zdrowia), 30));
		czerwony.setPosition(0, 0);
		zielony.setPosition(0, 0);
		okno.draw(czerwony);
		okno.draw(zielony);

///////////////////////////
////WYSWIETLENIE OKNA/////
/////////////////////////
		okno.display();

//////////////////////////////////
///SPRAWDZENIE CZY GRACZ ZYJE////
////////////////////////////////
		if (gracz.martwy())
			break;


////////////////////////////
////KONIEC PETLI GLOWEJ////
//////////////////////////		
	}


///////////////////////
///ZAMKNIECIE/////////
/////////////////////
	okno.close();
	cout << "YOU LOST" << endl;
	system("PAUSE");
	return 0;
}