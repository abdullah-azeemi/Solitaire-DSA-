#pragma once
#include "Utility.h"
#include "Helper.h"
#include "player.h"
#include "Deck.h"

class Tableau {

private:
	sf::Texture& deckSpriteSheet;
	vector<Cascade> cascades;
	int x, y;
	int width, height;

public:
	Tableau(sf::Texture& deckSpriteSheet, int x, int y);
	Tableau& operator=(const Tableau& other);
	void fillCascades(Deck& stock);
	std::vector<Card> getTopCards();
	bool cascadeIsEmpty(sf::Vector2i pos);
	bool containsPos(sf::Vector2i pos);
	bool containsTopCard(Card card);
	Card getCardAt(sf::Vector2i pos);
	void removeCardAt(sf::Vector2i pos);
	void saveCards(sf::Vector2i pos, Card card, std::vector<Card>& savedCards);
	void addCardAt(sf::Vector2i pos, std::vector<Card>& cards);
	void printCascades();
	void draw(sf::RenderWindow& window);

};