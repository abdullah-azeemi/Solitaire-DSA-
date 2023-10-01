#include "DrawnCards.h"

DrawnCards::DrawnCards(sf::Texture& deckSpriteSheet, int x, int y) : deckSpriteSheet(deckSpriteSheet), x(x), y(y) { }

void DrawnCards::drawCards(Deck& stock) {
	int maxCardsToDraw = diffVar;
	int xOffset = 20;
	if (cards.size() == 24) {
		cout << "Reached the maximum size ...";
		cout << stock.cards.size();
	}
	if (difficulty && cards.size() <24) {
		if (maxCardsToDraw - cards.size() == 0) {
			maxCardsToDraw += difficulty;
			diffVar += difficulty;
		}
		if (maxCardsToDraw == stock.cards.size() + cards.size()+1) {
			maxCardsToDraw = difficulty;
			diffVar = difficulty;
		}
	}

	while (cards.size() < maxCardsToDraw || cards.size() ==24) {
		if (stock.cards.empty()) {
			int i = 0;
			while (!cards.empty()) {
				stock.cards.push_back(cards.back());
				cards.pop_back();
				stock.cards[i].setOrientation(false);
				stock.cards[i].setX(100); 
				stock.cards[i].setY(500);
				i++;
			}
			maxCardsToDraw = difficulty;
			diffVar = difficulty; 
			
			if (stock.cards.size() == 1) {
				cout << "Only one card left in the stock. Pushing it back into the deck..." ;
				stock.cards.clear(); 
			}
			return;
		}
		Card drawnCard = stock.cards.back();
		drawnCard.setX(x + cards.size() * xOffset);
		drawnCard.setY(y);
		drawnCard.setOrientation(1);
		cards.push_back(drawnCard);
		stock.cards.pop_back();
	}
}

sf::Vector2i DrawnCards::getXBounds() {
	sf::Vector2i xBounds(x + 116, x - 100);
	return xBounds;
}

sf::Vector2i DrawnCards::getYBounds() {
	sf::Vector2i yBounds(y, y + 154);
	return yBounds;
}

bool DrawnCards::containsPos(sf::Vector2i pos) {
	for (int i = cards.size() - 1; i >= 0; i--) {
		if (cards[i].containsPos(pos)) {
			
			return true;
		}
	}
	return false;
}

Card DrawnCards::getCardAt(sf::Vector2i pos) {
	for (int i = cards.size() - 1; i >= 0; i--) {
		if (cards[i].containsPos(pos)) return cards[i];
	}

	return Card();
}

void DrawnCards::removeCardAt(sf::Vector2i pos) {
	for (int i = cards.size() - 1; i >= 0; i--) {
		if (cards[i].containsPos(pos)) {
			cards.erase(cards.begin() + i);
			
			return;
		}
	}
}

void DrawnCards::saveCards(Card card, std::vector<Card>& savedCards) {
	bool save = false;
	for (int i = 0; i < cards.size(); i++) {
		if (cards[i] == card) save = true;
		if (save) savedCards.push_back(cards[i]);
	}
	for (int i = 0; i < savedCards.size(); i++) {
		cout << "\n Save : " << savedCards[i];
	}
}
void DrawnCards::draw(sf::RenderWindow& window) {
	int numCardsToDraw = std::min(static_cast<int>(cards.size()), difficulty);
	int xOffset = 20; 
	int startX = x - (numCardsToDraw - 1) * xOffset / 2;
	int cardX = startX;

	if (cards.size() >= 22) {
		//cout << "hahahahah";
	}
	int ri = 0;
	for (int i = 0; i < cards.size(); i++, ri++) {
		if (i == cards.size() - 1 && difficulty==3) {
			ri = 2;
		}
		else if (i == cards.size() - 2 && difficulty == 3) {
			ri = 1;
		}
		if (difficulty == 3) {
			cardX += ((ri)%difficulty) * xOffset;
		}
		if (ri == 2) {
			ri = 0; cardX = startX;
		}
		int cardY = y;
		cards[i].setX(cardX);
		cards[i].setY(cardY);
		cards[i].draw(window, deckSpriteSheet);
	}
}
DrawnCards& DrawnCards::operator=(const DrawnCards& other) {
	if (this == &other) {
		return *this;
	}
	this->cards = other.cards;
	this->deckSpriteSheet = other.deckSpriteSheet;
	this->x = other.x;
	this->y = other.y;

	return *this;
}
