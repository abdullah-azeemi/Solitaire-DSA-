#pragma once
#include "Stack.h"
#include "Card.h"
#include <vector>

class Pile {

private:
	sf::Texture& deckSpriteSheet;
	const int x, y, foundationSize;
	int width, height;
	Stack foundation[4] = { Stack(deckSpriteSheet, x, y), Stack(deckSpriteSheet, x * 2, y),
	Stack(deckSpriteSheet, x * 3, y), Stack(deckSpriteSheet, x * 4, y) };

public:
	Pile(sf::Texture& deckSpriteSheet, int x, int y);
	Pile& operator=(const Pile& other);
	std::vector<Card> getTopCards();
	bool stackIsEmpty(sf::Vector2i pos);
	bool containsPos(sf::Vector2i pos);
	bool containsTopCard(Card card);
	bool validNextCard(Card card, sf::Vector2i pos);
	Card getCardAt(sf::Vector2i pos);
	void addCardAt(sf::Vector2i pos, std::vector<Card>& cards);
	void printStacks();
	void draw(sf::RenderWindow& window);
};
