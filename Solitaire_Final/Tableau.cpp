#include "Tableau.h"

Tableau::Tableau(sf::Texture& deckSpriteSheet, int x, int y) : deckSpriteSheet(deckSpriteSheet), x(x), y(y),
width(1240), height(700) {
};


void Tableau::fillCascades(Deck& stock) {
	for (int i = 1; i <= 7; i++) {
		cascades.push_back(Cascade(deckSpriteSheet, (int)(80 + (i - 1) * x), y));
		cascades[(i - 1)].startCards(stock, i);
	}
}

std::vector<Card> Tableau::getTopCards() {
	vector<Card> topCards;
	for (int i = 0; i < cascades.size(); i++) {
		if (cascades[i].size() > 0) {
			topCards.push_back(cascades[i].getCascade().back());
		}
	}
	return topCards;
}

bool Tableau::cascadeIsEmpty(sf::Vector2i pos) {
	for (int ri = 0; ri < cascades.size(); ri++) {
		if (cascades[ri].containsPos(pos) && cascades[ri].size() == 0) return true;
	}

	return false;
}

bool Tableau::containsPos(sf::Vector2i pos) {
	if (pos.x > 80 && pos.x < width && pos.y > y && pos.y < height) {
		for (int ri = 0; ri < cascades.size(); ri++) {
			if (cascades[ri].containsPos(pos)) return true;
		}
	}

	return false;
}

bool Tableau::containsTopCard(Card card) {
	std::vector<Card> topCards = getTopCards();
	for (int i = 0; i < topCards.size(); i++) {
		if (topCards[i] == card) return true;
	}

	return false;
}

Card Tableau::getCardAt(sf::Vector2i pos) {
	for (int i = 0; i < cascades.size(); i++) {
		if (cascades[i].containsPos(pos) && cascades[i].size() > 0) {
			return cascades[i].getCardAt(pos);
		}
	}

	return Card();
}

void Tableau::addCardAt(sf::Vector2i pos, std::vector<Card>& cards) {
	for (int i = 0; i < cascades.size(); i++) {
		if (cascades[i].containsPos(pos)) {
			cascades[i].addCard(cards);
		}
	}
}

void Tableau::removeCardAt(sf::Vector2i pos) {
	for (int i = 0; i < cascades.size(); i++) {
		if (cascades[i].containsPos(pos)) {
			cascades[i].removeCardAt(pos);
		}
	}
}

void Tableau::saveCards(sf::Vector2i pos, Card card, std::vector<Card>& savedCards) {
	for (int i = 0; i < cascades.size(); i++) {
		if (cascades[i].containsPos(pos)) {
			cascades[i].saveCards(card, savedCards);
		}
	}
	for (int i = 0; i < savedCards.size(); i++) {
		cout << "\n Saved " << savedCards[i];
	}
}

void Tableau::printCascades() {
	for (int i = 0; i < cascades.size(); i++) {
	    cout << "\n "<< cascades[i].getCascade().size();
	}
}

void Tableau::draw(sf::RenderWindow& window) {
	for (int ri = 0; ri < cascades.size(); ri++) {
		cascades[ri].draw(window);
	}
}
Tableau& Tableau::operator=(const Tableau& other) {
	if (this == &other) {
		return *this;
	}
	this->deckSpriteSheet = other.deckSpriteSheet;
	this->cascades = other.cascades;
	this->x = other.x;
	this->y = other.y;
	this->width = other.width;
	this->height = other.height;

	return *this;
}
