#pragma once
#include "Card.h"
#include "Utility.h"

class Deck {
	friend class DrawnCards;
	friend class Cascade;
private:
	vector<Card> cards;
	sf::Texture& deckSpriteSheet;
	int x, y;

public:
	Deck(sf::Texture& deckSpriteSheet, int x, int y);
	Deck& operator=(const Deck& other);
	void fill();
	void shuffle();

	void printCards();
	Card getTopCard();

	sf::Vector2i getXBounds();
	sf::Vector2i getYBounds();

	void draw(sf::RenderWindow& window);


};