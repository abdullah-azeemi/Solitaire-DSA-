#pragma once
#include "Card.h"

class Dabba {
private:
	Card data;
	Dabba* nextNode;
	friend class TrainClass;

public:
	Dabba(Card data, Dabba* nextNode = nullptr) : data(data), nextNode(nextNode) {}

};

class TrainClass {

private:
	int length;
	Dabba* head;

public:
	typedef void (*NodeHandler) (Card& card, int index, sf::RenderWindow& window, sf::Texture& deckSpriteSheet);

	TrainClass();

	void push(Card card);
	Card pop();
	Card top();

	int size();
	void empty();

	void forEach(NodeHandler handler, sf::RenderWindow& window, sf::Texture& deckSpriteSheet);

	Card operator[] (int position);
	friend std::ostream& operator <<(std::ostream& out, const TrainClass& ll);

};


