#include "Stack.h"
#include "Player.h"

Stack::Stack(sf::Texture& deckSpriteSheet, int x, int y) : deckSpriteSheet(deckSpriteSheet), x(x), y(y),
width(114), height(155) {
};

bool Stack::containsPos(sf::Vector2i pos) {
	if (pos.x > x && pos.x < x + width && pos.y > y && pos.y < y + height) {
		
		return true;
	}
	return false;
}

bool Stack::validNextCard(Card card, sf::Vector2i pos) {
	if (stack.top().getRank() + 1 == card.getRank() && stack.top().getSuit() == card.getSuit())
		return true;

	return false;
}

Card Stack::getCardAt(sf::Vector2i pos) {
	if (stack.top().containsPos(pos)) return stack.top();
	return Card();
}

void Stack::addCard(std::vector<Card> cards) {
	for (int i = 0; i < cards.size(); i++) {
		if (stack.size() > 0) {
			cards[i].setX(x);
			cards[i].setY(y);
			stack.push(cards[i]);
		}
		else {
			cards[i].setX(x);
			cards[i].setY(y);
			stack.push(cards[i]);
		}
	}
}

TrainClass Stack::getStack() {
	return stack;
}

void Stack::draw(sf::RenderWindow& window) {
	if (stack.size() == 0) {
		Card(-1, (Suit)2, x, y, true).draw(window, deckSpriteSheet);
	}
	else {
		stack.top().draw(window, deckSpriteSheet);
	}
}
Stack& Stack::operator=(const Stack& other) {
	if (this == &other) {
		return *this; 
	}
	this->deckSpriteSheet = other.deckSpriteSheet;
	this->x = other.x;
	this->y = other.y;
	this->width = other.width;
	this->height = other.height;
	this->stack = other.stack;

	return *this;
}
