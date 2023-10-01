#include "Deck.h"
#include <cstdlib>
#include <iostream>
#include<algorithm>
#include<random>
#include<vector>
#include<chrono>
#include<iostream>
using namespace std;

Deck::Deck(sf::Texture& deckSpriteSheet, int x, int y) : deckSpriteSheet(deckSpriteSheet), x(x), y(y) {}
void Deck::fill() {
	cards.clear();
	for (int i = 0; i < 52; i++) {
		cards.push_back(Card((i % 13) + 1, (Suit)(i % 4), x, y, 0));
	}
}
void Deck::shuffle() {
	std::random_device rand;
	std::mt19937 rng(rand());
	int n = cards.size();
	int divideIndex = n - 16; 
	for (int i = divideIndex - 1; i > 0; i--) {
		std::uniform_int_distribution<int> distribution(0, i);
		int j = distribution(rng);
		std::swap(cards[i], cards[j]);
	}

	for (int i = n - 1; i > divideIndex; i--) {
		std::uniform_int_distribution<int> distribution(divideIndex, i);
		int j = distribution(rng);
		std::swap(cards[i], cards[j]);
	}
}

void Deck::printCards() {
	for (unsigned int i = 0; i < cards.size(); i++) {
		if (i % 13 == 0) std::cout << "\n";
		std::cout << cards[i] << " ";
	}
	std::cout << "\n";
}

Card Deck::getTopCard() {
	return cards[cards.size() - 1];
}

sf::Vector2i Deck::getXBounds() {
	sf::Vector2i xBounds(x, x + 80);
	return xBounds;
}

sf::Vector2i Deck::getYBounds() {
	sf::Vector2i yBounds(y, y + 100);
	return yBounds;
}

void Deck::draw(sf::RenderWindow& window) {
	if (cards.size() > 0) {
		cards.back().draw(window, deckSpriteSheet);
	}
	else {
		cards.push_back(Card(-1, (Suit)2, x, y, true));
		cards.back().draw(window, deckSpriteSheet);
	}
}
Deck& Deck::operator=(const Deck& other) {
	if (this == &other) {
		return *this;
	}
	this->cards = other.cards;
	this->deckSpriteSheet = other.deckSpriteSheet;
	this->x = other.x;
	this->y = other.y;

	return *this;
}



