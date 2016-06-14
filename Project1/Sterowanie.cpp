#include "Sterowanie.h"

bool Sterowanie::czy_lewo()
{
	return lewo;
}

bool Sterowanie::czy_prawo()
{
	return prawo;
}

bool Sterowanie::czy_gora()
{
	return gora;
}

bool Sterowanie::czy_dol()
{
	return dol;
}

bool Sterowanie::czy_przycisk_myszy()
{
	return przycisk_myszy;
}

Punkt Sterowanie::pokaz_gdzie_mysz()
{
	return pozycja_myszy;
}

void Sterowanie::aktualizuj_przyciski()
{
	lewo = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	prawo = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	gora = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	dol = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	przycisk_myszy = sf::Mouse::isButtonPressed(sf::Mouse::Left);

}

void Sterowanie::aktualizuj_pozycje_myszy(sf::RenderWindow &okno)
{
	pozycja_myszy.ustaw(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y);
}
