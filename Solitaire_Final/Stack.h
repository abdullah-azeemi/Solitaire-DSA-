#pragma once
#include <vector>
#include "Helper.h"
#include "Deck.h"
#include "Card.h"

class Stack {

private:
	TrainClass stack;
	sf::Texture& deckSpriteSheet;
	int x, y;
	int width, height;

public:
	Stack(sf::Texture& deckSpriteSheet, int x, int y);

	bool containsPos(sf::Vector2i pos);
	bool validNextCard(Card card, sf::Vector2i pos);

	Card getCardAt(sf::Vector2i pos);
	void addCard(std::vector<Card> cards);
	TrainClass getStack();
	void draw(sf::RenderWindow& window);
	Stack &operator=(const Stack& other);
};

