#include "Player.h"

Player::Player() {
	Score = 0;
	name = " ";
}

Player::Player (string _name) {
	name = _name;

}
int Player::returnScore() {

	return Score;
}
string Player::getName() {

	return name;
}
void Player::changeScore() {

	Score += rand() % 10;

}
void Player::setName(string _n) {
	//name = _n;
}

int Player::getScore() {
	return this->Score;
}

Cascade::Cascade(sf::Texture& deckSpriteSheet, int x, int y) : deckSpriteSheet(deckSpriteSheet), x(x), y(y),
width(75), height(100) {}; // fix later width and height

void Cascade::startCards(Deck& stock, int total) {
	for (int i = 1; i <= total; i++) {
		stock.cards.back().setX(x);
		stock.cards.back().setY(y + (30 * (i - 1)));
		cascade.push_back(stock.cards.back());
		stock.cards.pop_back();
	}
	cascade.back().setOrientation(1);
}

bool Cascade::containsPos(sf::Vector2i pos) {
	if (pos.x > x && pos.x < x + width &&
		pos.y > y && pos.y < y + (height + (28 * cascade.size()))) {
		
		return true;
	}
	return false;
}

Card Cascade::getCardAt(sf::Vector2i pos) {
	for (int i = cascade.size() - 1; i >= 0; i--) {
		
		if (cascade[i].containsPos(pos)) return cascade[i];
	}
	return Card();
}

std::vector<Card> Cascade::getCascade() {
	return cascade;
}

int Cascade::size() {
	return cascade.size();
}

void Cascade::addCard(std::vector<Card>& cards) {
	for (int ri = 0; ri < cards.size(); ri++) {
		if (cascade.size() > 0) {
			cards[ri].setX(x);
			cards[ri].setY(cascade.back().getY() + 30);
			cascade.push_back(cards[ri]);
		}
		else {
			cards[ri].setX(x);
			cards[ri].setY(y);
			cascade.push_back(cards[ri]);
		}
	}
}

void Cascade::removeCardAt(sf::Vector2i pos) {
	for (int ri = cascade.size() - 1; ri >= 0; ri--) {
		if (cascade[ri].containsPos(pos)) {
			cascade.erase(cascade.begin() + ri, cascade.end());
			break;
		}
	}
	if (cascade.size() > 0) cascade.back().setOrientation(1);
}

void Cascade::saveCards(Card card, std::vector<Card>& savedCards) {
	bool save = false;
	for (int ri = 0; ri < cascade.size(); ri++) {
		if (cascade[ri] == card) save = true;
		if (save) savedCards.push_back(cascade[ri]);
	}
}

void Cascade::draw(sf::RenderWindow& window) {
	for (int ri = 0; ri < cascade.size(); ri++) {
		cascade[ri].draw(window, deckSpriteSheet);
	}
	if (cascade.size() == 0) {
		Card(-1, (Suit)2, x, y, true).draw(window, deckSpriteSheet);
	}
}
std::vector<Card>& Cascade::getCards() {
	return cascade;
}
Cascade& Cascade::operator=(const Cascade& other) {
	if (this == &other) {
		return *this; 
	}
	cascade = other.cascade; 
	return *this;
}
