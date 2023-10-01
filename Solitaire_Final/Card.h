#pragma once
#include <SFML\Graphics.hpp>
#include "Utility.h"
#include <iostream>

class Card {

private:
	int rank;
	Suit suit;
	int x, y;
	const static float width, height;
	const static float scale;
	bool orientation;

public:
	Card();
	Card(int rank, Suit suit, int x, int y, bool orientation);

	int getRank();
	int getSuit();

	int getX();
	int getY();

	float getWidth();
	float getHeight();

	void setX(int x);
	void setY(int y);

	bool containsPos(sf::Vector2i pos);

	void setOrientation(bool orientation);
	bool getOrientation();

	void draw(sf::RenderWindow& window, sf::Texture& deckSpriteSheet);
	void drawBlank(sf::RenderWindow& window, sf::Texture& deckSpriteSheet);

	friend std::ostream& operator <<(std::ostream& out, const Card& card);
	friend bool operator ==(const Card& card1, const Card& card2);

};