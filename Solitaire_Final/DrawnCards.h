#pragma once
#include "Helper.h"
#include "Card.h"
#include "Deck.h"
#include "Utility.h"

class DrawnCards {
private:
	vector<Card> cards;
	sf::Texture& deckSpriteSheet;
	int x, y;
	
public:
	DrawnCards(sf::Texture& deckSpriteSheet, int x, int y);
	DrawnCards& operator=(const DrawnCards& other);

	void drawCards(Deck& stock); 

	sf::Vector2i getXBounds();
	sf::Vector2i getYBounds();

	bool containsPos(sf::Vector2i pos);

	Card getCardAt(sf::Vector2i pos);
	void removeCardAt(sf::Vector2i pos);
	void saveCards(Card card, std::vector<Card>& savedCards);

	void draw(sf::RenderWindow& window); // Draws waste to window

};