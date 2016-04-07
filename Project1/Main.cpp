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

using namespace std;

///////////////////////////////////////////////
//USTANOWIENIE PODSTAWOWYCH PARAMETROW GRY////
/////////////////////////////////////////////
#define POCZ_ILOSC_BAZ 5
#define SZEROKOSC 1000
#define WYSOKOSC 500
#define PANEL 60
#define ZYCIE 1000
#define MIN_BONUS ZYCIE/4
#define MAX_BONUS ZYCIE/2
#define MAX_BAZ 15

///////////////////////////////////////////////////////////////////////
//CZESTOTLIWOSCI POJAWIANIA SIE POSZCZEGOLNYCH ISTOT WYRAZONE W HZ////
/////////////////////////////////////////////////////////////////////
#define F_POCISK 10
#define F_WROG 1
#define F_BAZA 0.3
#define F_BONUS 0.1
#define F_TRUDNOSCI 0.2



int main()
{

///////////////////////////
///STWORZENIE OKNA////////
/////////////////////////

	sf::RenderWindow okno(sf::VideoMode(SZEROKOSC, WYSOKOSC+PANEL), "Prototyp", sf::Style::Close);

///////////////////////////////////////////	
////DEKLARACJA ZMIENNYCH POMOCNICZYCH/////
/////////////////////////////////////////

	bool L, P, G, D;
	int taktowanie_wrogow = 0, taktowanie_pociskow = 0, taktowanie_bonusow = 0, taktowanie_baz = 0;
	int trudnosc = 0, kolejne_ulepszenia = 1, czasomierz=0;
	Punkt mysz;
	string pisak;

//////////////////////////////////////
////UTWORZENIE ZMIENNYCH CZASOWYCH///
////////////////////////////////////

	sf::Time czas, dt;
	sf::Clock zegar;
	dt = zegar.getElapsedTime();
	srand(int(time(NULL)));


//////////////////////////////////////////////////////////////////////////////////
///STWORZENIE NARZEDZI DO DYNAMICZNEJ OBSLUGI POCISKOW, WROGOW, BONUSOW I BAZ////
////////////////////////////////////////////////////////////////////////////////

	Wrog *nowy_wrog;
	vector<Wrog>armia;
	Pocisk *nowy_pocisk;
	vector<Pocisk>seria;
	Bonus *nowy_bonus;
	vector<Bonus>apteczka;
	Baza *nowa_baza;
	vector<Baza>baza;


/////////////////////////////////////////////
////POWOLANIE DO ZYCIA POCZATKOWYCH BAZ/////
///////////////////////////////////////////

	for (int i = 0; i < POCZ_ILOSC_BAZ; i++)
	{
		nowa_baza = new Baza(rand() % SZEROKOSC, rand() % WYSOKOSC);
		baza.push_back(*nowa_baza);
		delete nowa_baza;
	}

///////////////////////////////////////////////
////POWOLANIE DO ZYCIA POCZATKOWYCH WROGOW////
/////////////////////////////////////////////
	nowy_wrog = new Wrog();
	for (int i = 0; i < POCZ_ILOSC_BAZ; i++)
	{
		armia.push_back(*nowy_wrog);
		armia[i].ustaw(baza[i].gdzie());
	}
	delete nowy_wrog;
		
	

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

////////////////////////////////////
///////STWORZENIE MODELU PANELU////
//////////////////////////////////
	sf::RectangleShape zielony(sf::Vector2f(gracz.pojemnosc_zdrowia()/4, PANEL/2));
	sf::RectangleShape czerwony(sf::Vector2f(gracz.zdrowie()/4, PANEL/2));
	sf::RectangleShape pasek(sf::Vector2f(SZEROKOSC, PANEL));
	zielony.setPosition(0, WYSOKOSC+ PANEL / 2);
	czerwony.setPosition(0, WYSOKOSC+ PANEL / 2);
	pasek.setPosition(0, WYSOKOSC);
	zielony.setFillColor(sf::Color::Green);
	czerwony.setFillColor(sf::Color::Red);
	pasek.setFillColor(sf::Color::Magenta);

///////////////////////////
///STWORZENIE NAPISOW/////
/////////////////////////

	sf::Text licznik_czasu, licznik_pkt, licznik_ulepszen;
	sf::Font czcionka;

	czcionka.loadFromFile("arial.ttf");
	
	licznik_czasu.setFont(czcionka);
	licznik_pkt.setFont(czcionka);
	licznik_ulepszen.setFont(czcionka);
	
	licznik_czasu.setCharacterSize(PANEL/2);
	licznik_pkt.setCharacterSize(PANEL/2);
	licznik_ulepszen.setCharacterSize(PANEL/2);
	
	licznik_czasu.setPosition(SZEROKOSC * 2 / 3, WYSOKOSC + PANEL / 2);
	licznik_pkt.setPosition(SZEROKOSC * 2 / 3, WYSOKOSC);
	licznik_ulepszen.setPosition(0, WYSOKOSC);


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
		trudnosc = int(floor(czas.asSeconds() * F_TRUDNOSCI));


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
		int qwerty = 0;
		if (taktowanie_baz != int(round(czas.asSeconds()*F_BAZA)))
		{
			if (Baza::liczebnoscBaz <= MAX_BAZ)
			{
				nowa_baza = new Baza(rand() % SZEROKOSC, rand() % WYSOKOSC, trudnosc);
				baza.push_back(*nowa_baza);
				delete nowa_baza;
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
				nowy_bonus = new Bonus(rand() % SZEROKOSC, rand() % WYSOKOSC, (rand()%(MAX_BONUS-MIN_BONUS))+MIN_BONUS, rand()%(trudnosc*100));
				apteczka.push_back(*nowy_bonus);
				delete nowy_bonus;
			}
		}
		taktowanie_bonusow = int(round(czas.asSeconds()*F_BONUS));


/////////////////////////////////
///GENEROWANIE NOWEGO WROGA/////
///////////////////////////////
		if (Baza::liczebnoscBaz)
		{
			if(taktowanie_wrogow != int(round(czas.asSeconds()*(F_WROG+0.1*Baza::liczebnoscBaz))))
			{
				nowy_wrog = new Wrog(baza[rand() % Baza::liczebnoscBaz].gdzie(), trudnosc);
				armia.push_back(*nowy_wrog);
				delete nowy_wrog;
			}
			taktowanie_wrogow = int(round(czas.asSeconds()*(F_WROG+0.1*Baza::liczebnoscBaz)));
		}
			




///////////////////////////////////
///GENEROWANIE NOWEGO POCISKU/////
/////////////////////////////////

			if (taktowanie_pociskow != int(round(czas.asSeconds()*F_POCISK)))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && seria.size() < 5)
				{
				nowy_pocisk = new Pocisk(gracz);
				seria.push_back(*nowy_pocisk);
				delete nowy_pocisk;

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
								seria[j].atak(armia[i]);
								seria.erase(seria.begin() + j);
								
								if (armia[i].martwy())
								{
									gracz.zdobycz(armia[i].lup());
									armia.erase(armia.begin() + i);
								}
									
								
								
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


/////////////////////////////////
////BAZY PRZYJMUJA POCISKI//////
///////////////////////////////
		for (int i = 0; i < Baza::liczebnoscBaz; i++)
		{

			for (int j = 0; j < Pocisk::liczebnoscP; j++)
			{
				if (Baza::liczebnoscBaz && Pocisk::liczebnoscP)
				{
					if (baza[i].kontakt(seria[j]))
					{
						seria[j].atak(baza[i]);
						seria.erase(seria.begin() + j);

						if (baza[i].martwa())
						{
							gracz.zdobycz(baza[i].lup());
							baza.erase(baza.begin() + i);
						}
							


						if (Baza::liczebnoscBaz && Pocisk::liczebnoscP)
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

/////////////////////////////
//GRACZ ZBIERA BONUSY///////
///////////////////////////
		for (int i = 0; i < Bonus::liczebnoscB; i++)
		{
			if (apteczka[i].kontakt(gracz))
			{
				gracz.lecz(apteczka[i].moc());
				gracz.zdobycz(apteczka[i].lup());
				apteczka.erase(apteczka.begin() + i);
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

//////////////////////////////
//PRZYDZIELENIE ULEPSZENIA///
////////////////////////////
		if (gracz.dorobek() > 5000 * kolejne_ulepszenia + kolejne_ulepszenia * kolejne_ulepszenia * 200)
		{
			Pocisk::premia();
			if(kolejne_ulepszenia<7)
				gracz.premia();
			kolejne_ulepszenia++;
		}
		
		
//////////////////////////
///WYCZYSZCZENIE OKNA////
////////////////////////		
		okno.clear();


////////////////////////
///RYSOWANIE BAZ///////
//////////////////////
			for (int i = 0; i < Baza::liczebnoscBaz; i++)
			{
				
				Ba.setPosition(float(baza[i].gdzie().X()), float(baza[i].gdzie().Y()));
				Ba.setOrigin(float(baza[i].rozmiar()), float(baza[i].rozmiar()));
				Ba.setRadius(float(baza[i].rozmiar()));
				Ba.setFillColor(sf::Color::Yellow);
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
		czerwony.setSize(sf::Vector2f(gracz.pojemnosc_zdrowia()/4, PANEL/2));
		zielony.setSize(sf::Vector2f(gracz.zdrowie()/4, PANEL/2));
		zielony.setPosition(0, WYSOKOSC+ PANEL / 2);
		czerwony.setPosition(0, WYSOKOSC+ PANEL / 2);
		pasek.setPosition(0, WYSOKOSC);
		okno.draw(pasek);
		okno.draw(czerwony);
		okno.draw(zielony);

///////////////////////
///RYSOWANIE NAPISOW//
/////////////////////

		czasomierz = zegar.getElapsedTime().asSeconds();
		pisak = to_string(czasomierz / 3600);
		pisak += ":";
		if (czasomierz / 60 < 10)
		{
			pisak += "0";
			pisak += to_string(czasomierz / 60);
		}
		else
		{
			pisak += to_string(czasomierz / 60);
		}
		pisak += ":";
		if (czasomierz % 60 < 10)
		{
			pisak += "0";
			pisak += to_string(czasomierz%60);
		}
		else
		{
			pisak += to_string(czasomierz%60);
		}
			
		licznik_czasu.setString(pisak);

		pisak = "Pts: ";
		pisak += to_string(gracz.dorobek());
		licznik_pkt.setString(pisak);

		pisak = "Lvl: ";
		pisak += to_string(kolejne_ulepszenia);
		licznik_ulepszen.setString(pisak);

		okno.draw(licznik_czasu);
		okno.draw(licznik_pkt);
		okno.draw(licznik_ulepszen);

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
	cout << gracz.dorobek() << endl;
	cin >> trudnosc;
	return 0;
}
