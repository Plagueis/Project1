#include "Gra.h"

Gra::Gra() : mapa(Mapa(Punkt(0, 0), Punkt(1000, 0), Punkt(1000, 500), Punkt(0, 500))), panel(Panel(1000, 60)), gracz(Gracz(1000))
{
	min_bonus = gracz.pokaz_zycie() / 4;
	max_bonus = gracz.pokaz_zycie() / 2;
	max_baz = 15;
	f_pocisk = 10;
	f_wrog = 1;
	f_baza = 0.3;
	f_bonus = 0.1;
	f_trudnosci = 0.2;
	trudnosc = 1;
	gracz.ustaw(Punkt(mapa.pokaz_szerokosc(), mapa.pokaz_wysokosc()));
	bazy.dodaj(Baza(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), trudnosc));
	bazy.dodaj(Baza(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), trudnosc));
	bazy.dodaj(Baza(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), trudnosc));
	bazy.dodaj(Baza(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), trudnosc));
	bazy.dodaj(Baza(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), trudnosc));
	armia.dodaj(Wrog(bazy[0]->pokaz_pozycje()));
	armia.dodaj(Wrog(bazy[1]->pokaz_pozycje()));
	armia.dodaj(Wrog(bazy[2]->pokaz_pozycje()));
	armia.dodaj(Wrog(bazy[3]->pokaz_pozycje()));
	armia.dodaj(Wrog(bazy[4]->pokaz_pozycje()));
}

void Gra::wystartuj_naliczanie_jednostki_czasu()
{
	dt = zegar.getElapsedTime();
}

void Gra::pobierz_jednostke_czasu()
{
	dt = zegar.getElapsedTime() - dt;
}

void Gra::pobierz_biezacy_czas()
{
	czas = zegar.getElapsedTime();
	trudnosc = int(floor(czas.asSeconds() * f_trudnosci));
}

void Gra::trafienia_pociskow()
{
	if(armia.rozmiar())
	for (int i = 0; i < armia.rozmiar(); i++)
	{

		for (int j = 0; j < seria.rozmiar(); j++)
		{
			if (armia.rozmiar() && seria.rozmiar())
			{
				if (armia[i]->w_kontakcie_z(*seria[j]))
				{
					seria[j]->atak(*armia[i]);
					seria.usun(j);

					if (armia[i]->martwy())
					{
						gracz.dodaj_punkty(armia[i]->pokaz_punkty());
						armia.usun(i);
					}



					if (armia.rozmiar() && seria.rozmiar())
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

	if (bazy.rozmiar())
		for (int i = 0; i < bazy.rozmiar(); i++)
		{

			for (int j = 0; j < seria.rozmiar(); j++)
			{
				if (bazy.rozmiar() && seria.rozmiar())
				{
					if (bazy[i]->w_kontakcie_z(*seria[j]))
					{
						seria[j]->atak(*bazy[i]);
						seria.usun(j);

						if (bazy[i]->martwy())
						{
							gracz.dodaj_punkty(bazy[i]->pokaz_punkty());
							bazy.usun(i);
						}



						if (bazy.rozmiar() && seria.rozmiar())
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

void Gra::zbieranie_bonusow()
{
	for (int i = 0; i <apteczka.rozmiar(); i++)
	{
		if (apteczka[i]->w_kontakcie_z(gracz))
		{
			gracz.przywroc_zycie(apteczka[i]->pokaz_moc());
			gracz.dodaj_punkty(apteczka[i]->pokaz_punkty());
			apteczka.usun(i);
		}
	}
}

void Gra::starcie_gracza_z_wrogami()
{
	if(armia.rozmiar())
	for (int i = 0; i < armia.rozmiar(); i++)
	{
		if (armia[i]->w_kontakcie_z(gracz))
		{
			armia[i]->atak(gracz);
			gracz.trafiony = 1;
		}
	}

}

void Gra::porusz()
{
	bool L = sterowanie.czy_lewo();
	bool P = sterowanie.czy_prawo();
	bool D = sterowanie.czy_dol();
	bool G = sterowanie.czy_gora();

	if (L == 1 && P == 0 && G == 0 && D == 0)
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

	if(armia.rozmiar())
	{ 
		for (int i = 0; i < armia.rozmiar(); i++)
		{
			armia[i]->zorientuj(gracz.pokaz_pozycje());
			armia[i]->rusz(dt.asSeconds() * 100);

		}
	}
	if (seria.rozmiar())
	{
		for (int i = 0; i < seria.rozmiar(); i++)
			seria[i]->rusz(dt.asSeconds() * 100);
	}
}

void Gra::koryguj_ustawienie()
{
	gracz.zamknij_w_prostokacie(mapa);
	for ( int i = 0; i < armia.rozmiar(); i++)
	{
		armia[i]->zamknij_w_prostokacie(mapa);
	}
	Punkt stara_pozycja;
	for (int i = 0; i < seria.rozmiar(); i++)
	{
		stara_pozycja = seria[i]->pokaz_pozycje();
		seria[i]->zamknij_w_prostokacie(mapa);
		if (seria[i]->pokaz_pozycje() != stara_pozycja)
		{
			seria.usun(i);
		}

	}
	armia.porozsuwaj();
	gracz.zorientuj(sterowanie.pokaz_gdzie_mysz());
}

void Gra::tworzenie_nowych_istot()
{
	if (taktowanie_baz != int(round(czas.asSeconds()*f_baza)))
	{
		if (bazy.rozmiar() <= max_baz)
		{
			Baza *nowa_baza = new Baza(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), trudnosc);
			bazy.dodaj(*nowa_baza);
			delete nowa_baza;
		}
	}
	taktowanie_baz = int(round(czas.asSeconds()*f_baza));


	if (taktowanie_bonusow != int(round(czas.asSeconds()*f_bonus)))
	{
		if (apteczka.rozmiar() < 3)
		{
			Bonus *nowy_bonus = new Bonus(rand() % mapa.pokaz_szerokosc(), rand() % mapa.pokaz_wysokosc(), (rand() % (max_bonus - min_bonus)) + min_bonus, rand() % (trudnosc * 100));
			apteczka.dodaj(*nowy_bonus);
			delete nowy_bonus;
		}
	}
	taktowanie_bonusow = int(round(czas.asSeconds()*f_bonus));

	if (bazy.rozmiar())
	{
		if (taktowanie_wrogow != int(round(czas.asSeconds()*(f_wrog + 0.1*bazy.rozmiar()))))
		{
			Wrog *nowy_wrog = new Wrog(bazy[rand() % bazy.rozmiar()]->pokaz_pozycje(), trudnosc);
			armia.dodaj(*nowy_wrog);
			delete nowy_wrog;
		}
		taktowanie_wrogow = int(round(czas.asSeconds()*(f_wrog + 0.1*bazy.rozmiar())));
	}


	if (taktowanie_pociskow != int(round(czas.asSeconds()*f_pocisk)))
	{
		if (sterowanie.czy_przycisk_myszy() && seria.rozmiar() < 5)
		{
			Pocisk *nowy_pocisk = new Pocisk(gracz);
			seria.dodaj(*nowy_pocisk);
			delete nowy_pocisk;

		}
	}
	taktowanie_pociskow = int(round(czas.asSeconds()*f_pocisk));

}
