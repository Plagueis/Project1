#pragma once
#include<vector>
#include<iostream>
#include"Punkt.h"

using namespace std;

template <class Podmiot> class Grupa
{
private:
	vector<Podmiot*> zbiornik;
public:
	void dodaj(Podmiot nowy);
	void usun(int ktory);
	void porozsuwaj();
	void rusz(double czas);
	void zorientuj(Punkt &cel);
	Podmiot* operator[](int indeks);
	int rozmiar();
	~Grupa();
};

template<class Podmiot>
void Grupa<Podmiot>::dodaj(Podmiot nowy)
{
	Podmiot *wskaznik = new Podmiot(nowy);
	zbiornik.push_back(wskaznik);
	//cout << "Dodalem " << zbiornik.size() << endl;
}

template<class Podmiot>
void Grupa<Podmiot>::usun(int ktory)
{
	delete zbiornik[ktory];
	zbiornik.erase(zbiornik.begin() + ktory);
	//cout << "Usunalem " << ktory<<" Zostalo "<<zbiornik.size() << endl;
}

template<class Podmiot>
void Grupa<Podmiot>::porozsuwaj()
{
	if (zbiornik.size() > 1)
		{
		if (dynamic_cast<Istota*>(zbiornik[0]))
			{	
				for (int i = 0; i < zbiornik.size(); i++)
				{
					for (int j = i + 1; j < zbiornik.size(); j++)
					{
						zbiornik[i]->rozsun((*zbiornik[j]));
						//cout << "Rozsuwam " << i << " i " << j << endl;
					}
				}
			}
			else
			{
				//cout << "Nie dalo sie" << endl;
			}
		}
}

template<class Podmiot>
void Grupa<Podmiot>::rusz(double czas)
{
	for (int i = 0; i < zbiornik.size(); i++)
	{
		if (dynamic_cast<Istota*>(zbiornik[i]))
		{
			zbiornik[i]->rusz(czas);
		}
	}
}

template<class Podmiot>
void Grupa<Podmiot>::zorientuj(Punkt & cel)
{
	for (int i = 0; i < zbiornik.size(); i++)
	{
		if (dynamic_cast<Istota*>(zbiornik[i]))
		{
			zbiornik[i]->zorientuj(cel);
		}
	}
}

template<class Podmiot>
Podmiot * Grupa<Podmiot>::operator[](int indeks)
{
	return zbiornik[indeks];
}

template<class Podmiot>
int Grupa<Podmiot>::rozmiar()
{
	return zbiornik.size();
}

template<class Podmiot>
Grupa<Podmiot>::~Grupa()
{
	if (zbiornik.size())
	{
		for (int i = 0; i < zbiornik.size(); i++)
		{
			delete zbiornik[i];
		}
	}
}
