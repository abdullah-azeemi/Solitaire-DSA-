#include "Pile.h"

Pile::Pile(sf::Texture& deckSpriteSheet, int x, int y) : deckSpriteSheet(deckSpriteSheet), x(x), y(y),
foundationSize(4), width(900), height(1060) {
};

std::vector<Card> Pile::getTopCards() {
	std::vector<Card> topCards;

	for (int i = 0; i < foundationSize; i++) {
		if (foundation[i].getStack().size() > 0) {
			
			topCards.push_back(foundation[i].getStack().top());
		}
	}
	return topCards;
}

bool Pile::stackIsEmpty(sf::Vector2i pos) {
	for (int i = 0; i < foundationSize; i++) {
		
		if (foundation[i].containsPos(pos) && foundation[i].getStack().size() == 0) {
			return true;
		}
	}
	return false;
}

bool Pile::containsPos(sf::Vector2i pos) {
	if (pos.x > x && pos.x < x + width && pos.y > y && pos.y < y + height) {
		for (int ri = 0; ri < foundationSize; ri++) {
			
			if (foundation[ri].containsPos(pos)) {
				return true;
			}
		}
	}
	return false;
}

bool Pile::containsTopCard(Card card) {
	std::vector<Card> topCards = getTopCards();
	for (int ri = 0; ri < topCards.size(); ri++) {
		if (topCards[ri] == card) return true;
	}
	return false;
}

bool Pile::validNextCard(Card card, sf::Vector2i pos) {
	for (int ri = 0; ri < foundationSize; ri++) {
		if (foundation[ri].containsPos(pos)) {

			return foundation[ri].validNextCard(card, pos);
		}
	}
	return false;
}

Card Pile::getCardAt(sf::Vector2i pos) {
	for (int ri = 0; ri < foundationSize; ri++) {
		if (foundation[ri].containsPos(pos) && foundation[ri].getStack().size() > 0) {
			
			return foundation[ri].getCardAt(pos);
		}
	}

	return Card();
}

void Pile::addCardAt(sf::Vector2i pos, std::vector<Card>& cards) {
	
	for (int ri = 0; ri < foundationSize; ri++) {
		if (foundation[ri].containsPos(pos)) {
			
			foundation[ri].addCard(cards);
		}
	}
}

void Pile::printStacks() {
	for (int ri = 0; ri < foundationSize; ri++) {
		cout << "\n " << foundation[ri].getStack().size();
	}
}

void Pile::draw(sf::RenderWindow& window) {
	for (int i = 0; i < foundationSize; i++) {
		foundation[i].draw(window);
	}
}
Pile& Pile::operator=(const Pile& other) {
	if (this == &other) {
		return *this; 
	}
	this->deckSpriteSheet = other.deckSpriteSheet;
	this->width = other.width;
	this->height = other.height;
	for (int i = 0; i < foundationSize; i++) {
		this->foundation[i] = other.foundation[i];
	}
	return *this;
}
