#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
#include<vector>

#include"Gracz.h"
#include"Wrog.h"
#include"Pocisk.h"
#include"Bonus.h"

using namespace std;

///////////////////////////////////////////////
//USTANOWIENIE PODSTAWOWYCH PARAMETROW GRY////
/////////////////////////////////////////////
#define POCZ_ILOSC_BAZ 2
#define SZEROKOSC 1000
#define WYSOKOSC 500
#define ZYCIE 1000
#define MAX_BONUS ZYCIE/4

///////////////////////////////////////////////////////////////////////
//CZESTOTLIWOSCI POJAWIANIA SIE POSZCZEGOLNYCH ISTOT WYRAZONE W HZ////
/////////////////////////////////////////////////////////////////////
#define F_POCISK 10
#define F_WROG 1
#define F_BAZA 0.2
#define F_BONUS 0.1



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
	int taktowanie_wrogow = 0, taktowanie_pociskow = 0, taktowanie_bonusow = 0, taktowanie_baz = 0, ilosc_baz = 0;
	double procent_zdrowia = 0;

//////////////////////////////////////
////UTWORZENIE ZMIENNYCH CZASOWYCH///
////////////////////////////////////
	sf::Time czas, dt;
	sf::Clock zegar;
	dt = zegar.getElapsedTime();
	srand(int(time(NULL)));

//////////////////////////////////////////////////
///DEKLARACJA CHARAKTERYSTYCZNYCH PUNKTOW MAPY///
////////////////////////////////////////////////
	Punkt *miejsce;
	vector<Punkt>baza;

	for (int i = 0; i < POCZ_ILOSC_BAZ; i++)
	{	
		miejsce = new Punkt(rand() % SZEROKOSC, rand() % WYSOKOSC);
		baza.push_back(*miejsce);
		delete miejsce;
	}

	ilosc_baz = POCZ_ILOSC_BAZ;

	Punkt mysz;


////////////////////////////////////////////////////////////////////////////////
///STWORZENIE NARZEDZI DO DYNAMICZNEJ OBSLUGI POCISKOW, WROGOW I BONUSOW///////
//////////////////////////////////////////////////////////////////////////////
	Wrog *wsk1;
	vector<Wrog>armia;
	Pocisk *wsk2;
	vector<Pocisk>seria;
	Bonus *wsk3;
	vector<Bonus>apteczka;

///////////////////////////////////////////////
////POWOLANIE DO ZYCIA POCZATKOWYCH WROGOW////
/////////////////////////////////////////////
	wsk1 = new Wrog;

	for (int i = 0; i < POCZ_ILOSC_BAZ; i++)
		armia.push_back(*wsk1);

	delete wsk1;

	for (int i = 0; i < POCZ_ILOSC_BAZ; i++)
		armia[i].ustaw(baza[i]);
	

/////////////////////////////////
////POWOLANIE DO ZYCIA GRACZA///
///////////////////////////////
	Gracz gracz(ZYCIE);
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

/////////////////////////////////
/////STWORZENIE MODELU BAZY/////
///////////////////////////////
	sf::CircleShape Ba(15.f);
	Ba.setFillColor(sf::Color::Yellow);
	Ba.setOrigin(15, 15);

///////////////////////////////////
/////STWORZENIE MODELU BONUSU////
/////////////////////////////////
	sf::CircleShape Bo(8.f);
	Bo.setFillColor(sf::Color::Cyan);
	Bo.setOrigin(8, 8);

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



///////////////////////////////
///GENEROWANIE NOWEJ BAZY/////
/////////////////////////////

		if (taktowanie_baz != int(round(czas.asSeconds()*F_BAZA)))
		{
			if (ilosc_baz <= 10)
			{
				miejsce = new Punkt(rand() % SZEROKOSC, rand() % WYSOKOSC);
				baza.push_back(*miejsce);
				delete miejsce;
				ilosc_baz++;
			}
		}
		taktowanie_baz = int(round(czas.asSeconds()*F_BAZA));



//////////////////////////////////
///GENEROWANIE NOWEGO BONUSU/////
////////////////////////////////

		if (taktowanie_bonusow != int(round(czas.asSeconds()*F_BONUS)))
		{
			if (Bonus::liczebnoscB < 3)
			{
				wsk3 = new Bonus(rand() % SZEROKOSC, rand() % WYSOKOSC, rand() % MAX_BONUS);
				apteczka.push_back(*wsk3);
				delete wsk3;
			}
		}
		taktowanie_bonusow = int(round(czas.asSeconds()*F_BONUS));


/////////////////////////////////
///GENEROWANIE NOWEGO WROGA/////
///////////////////////////////

			if(taktowanie_wrogow != int(round(czas.asSeconds()*(F_WROG+0.1*ilosc_baz))))
			{
				wsk1 = new Wrog(baza[rand() % ilosc_baz]);
				armia.push_back(*wsk1);
				delete wsk1;
			}
			taktowanie_wrogow = int(round(czas.asSeconds()*(F_WROG+0.1*ilosc_baz)));




///////////////////////////////////
///GENEROWANIE NOWEGO POCISKU/////
/////////////////////////////////

			if (taktowanie_pociskow != int(round(czas.asSeconds()*F_POCISK)))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && seria.size() < 5)
				{
				wsk2 = new Pocisk(gracz);
				seria.push_back(*wsk2);
				delete wsk2;

				}
			}
			taktowanie_pociskow = int(round(czas.asSeconds()*F_POCISK));







/////////////////////////////////
///POBRANIE JEDNOSTKI CZASU/////
///////////////////////////////
		dt = zegar.getElapsedTime() - dt;
		



////////////////////////
////RUCH GRACZA////////
//////////////////////
		if (L==1 && P==0 && G==0 && D==0)
		{
			gracz.zorientuj(270);
			gracz.rusz(dt.asSeconds() * 100);
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


////////////////////////
///RYSOWANIE BAZ///////
//////////////////////
			for (int i = 0; i < ilosc_baz; i++)
			{
				Ba.setPosition(float(baza[i].X()), float(baza[i].Y()));
				okno.draw(Ba);
			}

///////////////////////////
///RYSOWANIE BONUSOW//////
/////////////////////////
			if (Bonus::liczebnoscB)
			{
				for (int i = 0; i < Bonus::liczebnoscB; i++)
				{
					Bo.setPosition(float(apteczka[i].gdzie().X()), float(apteczka[i].gdzie().Y()));
					okno.draw(Bo);
				}
			}


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
		procent_zdrowia = (gracz.zdrowie() * 300) / ZYCIE;
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
