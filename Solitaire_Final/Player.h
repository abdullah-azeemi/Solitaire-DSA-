#pragma once
#include "Utility.h"
#include "Helper.h"
#include "Deck.h"
#include "Card.h"

class Player {
	string name;
	int Score;

public:
	Player();
	Player(string _name);
	void setName(string _n);
	int returnScore();
	string getName();
	void changeScore();
	int getScore();


};




class Cascade {

private:
	vector<Card> cascade;
	sf::Texture& deckSpriteSheet;
	int x, y;
	int width, height;

public:
	Cascade(sf::Texture& deckSpriteSheet, int x, int y);
	void startCards(Deck& stock, int total);

	bool containsPos(sf::Vector2i pos);
	Card getCardAt(sf::Vector2i pos);
	std::vector<Card> getCascade();
	int size();

	void addCard(std::vector<Card>& cards);
	void removeCardAt(sf::Vector2i pos);
	void saveCards(Card card, std::vector<Card>& savedCards);
	std::vector<Card>& getCards();
	void draw(sf::RenderWindow& window);
	Cascade& operator=(const Cascade& other);
};