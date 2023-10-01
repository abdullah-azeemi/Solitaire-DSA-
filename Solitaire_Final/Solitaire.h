#pragma once
#include "Deck.h"
#include "DrawnCards.h"
#include "Tableau.h"
#include "Card.h"
#include "Pile.h"
#include"Utility.h"
using namespace std;

class Solitaire {
private:
	Deck stock;
	DrawnCards waste;
	Tableau tableau;
	Pile foundation;
	sf::Texture& deckSpriteSheet;
	vector<Card> savedCards;
	sf::Vector2i savedPos;
	Player* P;

	// ---------------------- For undo & redo ----------------------------------------------
	stack<Deck> stStock,stStock1;
	stack<DrawnCards> stWaste,stWaste1;
	stack<Tableau> stTableau,stTableau1;
	stack<Pile> stFoundation, stFoundation1;

	int saveCardClass;
	bool cardSelected;
	bool undoButtonClicked;
	bool redoButtonClicked;
	int sc = 0;

public:
	void run();
	Solitaire(sf::Texture& deckSpriteSheet);

	void startGame();

	void draw(sf::RenderWindow& window);
	void saveCard(Card card, sf::Vector2i pos);
	void unsaveCard();
	bool validCardPlacement(Card card);
	bool isValidMove(sf::Vector2i pos);
	bool isValidSource(sf::Vector2i pos);
};