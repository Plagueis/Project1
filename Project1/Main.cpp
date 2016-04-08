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
		armia[i].ustaw(baza[i].pokaz_pozycje());
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
	sf::CircleShape Gr(float(gracz.pokaz_promien()), 3);
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
	sf::RectangleShape zielony(sf::Vector2f(float(gracz.pokaz_limit_zycia()/4), float(PANEL/2)));
	sf::RectangleShape czerwony(sf::Vector2f(float(gracz.pokaz_zycie()/4), float(PANEL/2)));
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
			if (Baza::pokaz_ile() <= MAX_BAZ)
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
			if (Bonus::pokaz_ile() < 3)
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
		if (Baza::pokaz_ile())
		{
			if(taktowanie_wrogow != int(round(czas.asSeconds()*(F_WROG+0.1*Baza::pokaz_ile()))))
			{
				nowy_wrog = new Wrog(baza[rand() % Baza::pokaz_ile()].pokaz_pozycje(), trudnosc);
				armia.push_back(*nowy_wrog);
				delete nowy_wrog;
			}
			taktowanie_wrogow = int(round(czas.asSeconds()*(F_WROG+0.1*Baza::pokaz_ile())));
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
		if (Wrog::pokaz_ile())
		{
			for (int i = 0; i < Wrog::pokaz_ile(); i++)
				{
					armia[i].zorientuj(gracz.pokaz_pozycje());
					armia[i].rusz(dt.asSeconds() * 100);

					if (armia[i].w_kontakcie_z(gracz))
						{
							armia[i].atak(gracz);
							Gr.setFillColor(sf::Color::Red);
						}
				}
		}


/////////////////////////
///RUCH POCISKOW////////
///////////////////////
		if (Pocisk::pokaz_ile())
		{
			for (int i = 0; i < Pocisk::pokaz_ile(); i++)
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
		if (gracz.pokaz_pozycje().X() < gracz.pokaz_promien())
		{
			gracz.ustaw(gracz.pokaz_promien(), gracz.pokaz_pozycje().Y());
		}
		if (gracz.pokaz_pozycje().Y() < gracz.pokaz_promien())
		{
			gracz.ustaw(gracz.pokaz_pozycje().X(), gracz.pokaz_promien());
		}
		if (gracz.pokaz_pozycje().X() > SZEROKOSC - gracz.pokaz_promien())
		{
			gracz.ustaw(SZEROKOSC - gracz.pokaz_promien(), gracz.pokaz_pozycje().Y());
		}
		if (gracz.pokaz_pozycje().Y() > WYSOKOSC-gracz.pokaz_promien())
		{
			gracz.ustaw(gracz.pokaz_pozycje().X(), WYSOKOSC - gracz.pokaz_promien());
		}



//////////////////////////////////
//SERIA OPERACJI NA WROGACH//////
////////////////////////////////
		if (Wrog::pokaz_ile())
		{
			//////////////////////////
			////POROZSUWANIE WROGOW///
			//////////////////////////
			for (int i = 0; i < Wrog::pokaz_ile(); i++)
			{
				for (int j = i + 1; j < Wrog::pokaz_ile(); j++)
				{
					armia[i].rozsun(armia[j]);
				}

			}

			//////////////////////////////
			//WROGOWIE ATAKUJA GRACZA/////
			//////////////////////////////
			for (int i = 0; i < Wrog::pokaz_ile(); i++)
			{
				if (armia[i].w_kontakcie_z(gracz))
				{
					armia[i].atak(gracz);
					Gr.setFillColor(sf::Color::Red);
				}
			}


			/////////////////////////////////
			////WROGOWIE PRZYJMUJA POCISKI///
			/////////////////////////////////
			for (int i = 0; i < Wrog::pokaz_ile(); i++)
			{

				for (int j = 0; j < Pocisk::pokaz_ile(); j++)
				{
					if(Wrog::pokaz_ile() && Pocisk::pokaz_ile())
					{
						if(armia[i].w_kontakcie_z(seria[j]))
							{
								seria[j].atak(armia[i]);
								seria.erase(seria.begin() + j);
								
								if (armia[i].martwy())
								{
									gracz.dodaj_punkty(armia[i].pokaz_punkty());
									armia.erase(armia.begin() + i);
								}
									
								
								
								if (Wrog::pokaz_ile() && Pocisk::pokaz_ile())
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
		for (int i = 0; i < Baza::pokaz_ile(); i++)
		{

			for (int j = 0; j < Pocisk::pokaz_ile(); j++)
			{
				if (Baza::pokaz_ile() && Pocisk::pokaz_ile())
				{
					if (baza[i].w_kontakcie_z(seria[j]))
					{
						seria[j].atak(baza[i]);
						seria.erase(seria.begin() + j);

						if (baza[i].martwy())
						{
							gracz.dodaj_punkty(baza[i].pokaz_punkty());
							baza.erase(baza.begin() + i);
						}
							


						if (Baza::pokaz_ile() && Pocisk::pokaz_ile())
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
		for (int i = 0; i < Bonus::pokaz_ile(); i++)
		{
			if (apteczka[i].w_kontakcie_z(gracz))
			{
				gracz.przywroc_zycie(apteczka[i].pokaz_moc());
				gracz.dodaj_punkty(apteczka[i].pokaz_punkty());
				apteczka.erase(apteczka.begin() + i);
			}
		}

///////////////////////////////////
//USUNIECIE POCISKOW POZA MAPA/////
///////////////////////////////////
		if(Pocisk::pokaz_ile())
		{
			for (int j = 0; j < Pocisk::pokaz_ile(); j++)
			{
				if (seria[j].pokaz_pozycje().X() < 0)
				{
					seria.erase(seria.begin() + j);
				}
				else if (seria[j].pokaz_pozycje().Y() < 0)
				{
					seria.erase(seria.begin() + j);
				}
				else if (seria[j].pokaz_pozycje().X() > SZEROKOSC)
				{
					seria.erase(seria.begin() + j);
				}
				else if (seria[j].pokaz_pozycje().Y() > WYSOKOSC)
				{
					seria.erase(seria.begin() + j);
				}
					
				
			}
		}

//////////////////////////////
//PRZYDZIELENIE ULEPSZENIA///
////////////////////////////
		if (gracz.pokaz_punkty() > 5000 * kolejne_ulepszenia + kolejne_ulepszenia * kolejne_ulepszenia * 200)
		{
			gracz.awans(kolejne_ulepszenia);
			kolejne_ulepszenia++;
		}
		
		
//////////////////////////
///WYCZYSZCZENIE OKNA////
////////////////////////		
		okno.clear();


////////////////////////
///RYSOWANIE BAZ///////
//////////////////////
			for (int i = 0; i < Baza::pokaz_ile(); i++)
			{
				
				Ba.setPosition(float(baza[i].pokaz_pozycje().X()), float(baza[i].pokaz_pozycje().Y()));
				Ba.setOrigin(float(baza[i].pokaz_promien()), float(baza[i].pokaz_promien()));
				Ba.setRadius(float(baza[i].pokaz_promien()));
				Ba.setFillColor(sf::Color::Yellow);
				okno.draw(Ba);
			}

///////////////////////////
///RYSOWANIE BONUSOW//////
/////////////////////////
			if (Bonus::pokaz_ile())
			{
				for (int i = 0; i < Bonus::pokaz_ile(); i++)
				{
					Bo.setPosition(float(apteczka[i].pokaz_pozycje().X()), float(apteczka[i].pokaz_pozycje().Y()));
					okno.draw(Bo);
				}
			}


///////////////////////////
///RYSOWANIE WROGOW///////
/////////////////////////
		if (Wrog::pokaz_ile())
		{
			for (int i = 0; i < Wrog::pokaz_ile(); i++)
			{
				Wr.setPosition(float(armia[i].pokaz_pozycje().X()), float(armia[i].pokaz_pozycje().Y()));
				Wr.setRotation(float(armia[i].pokaz_orientacje()));
				okno.draw(Wr);
			}
		}

////////////////////////////
//RYSOWANIE POCISKOW///////
//////////////////////////	
		if (Pocisk::pokaz_ile())
		{
			for (int i = 0; i < Pocisk::pokaz_ile(); i++)
			{
				Po.setPosition(float(seria[i].pokaz_pozycje().X()), float(seria[i].pokaz_pozycje().Y()));
				Po.setRotation(float(seria[i].pokaz_orientacje()));
				okno.draw(Po);
			}
		}

///////////////////////////
//RYSOWANIE GRACZA////////
/////////////////////////
		Gr.setPosition(float(gracz.pokaz_pozycje().X()), float(gracz.pokaz_pozycje().Y()));
		Gr.setRotation(float(gracz.pokaz_orientacje()));
		okno.draw(Gr);


/////////////////////////
////RYSOWANIE PASKA/////
///////////////////////
		czerwony.setSize(sf::Vector2f(float(gracz.pokaz_limit_zycia()/4), float(PANEL/2)));
		zielony.setSize(sf::Vector2f(float(gracz.pokaz_zycie()/4), float(PANEL/2)));
		zielony.setPosition(0, WYSOKOSC+ PANEL / 2);
		czerwony.setPosition(0, WYSOKOSC+ PANEL / 2);
		pasek.setPosition(0, WYSOKOSC);
		okno.draw(pasek);
		okno.draw(czerwony);
		okno.draw(zielony);

///////////////////////
///RYSOWANIE NAPISOW//
/////////////////////

		czasomierz = int(zegar.getElapsedTime().asSeconds());
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
		pisak += to_string(gracz.pokaz_punkty());
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
	cout << gracz.pokaz_punkty() << endl;
	return 0;
}
