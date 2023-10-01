#include "Card.h"

const float Card::width = 345, Card::height = 528, Card::scale = 0.26;

Card::Card() {};

Card::Card(int rank, Suit suit, int x, int y, bool orientation) : rank(rank), suit(suit), x(x), y(y), orientation(orientation) {}
int Card::getRank() {
	return rank;
}
int Card::getSuit() {
	return (int)suit;
}
int Card::getX() {
	return x;
}
int Card::getY() {
	return y;
}
float Card::getWidth() {
	return width * scale;
}
float Card::getHeight() {
	return height * scale;
}
void Card::setX(int x) {
	this->x = x;
}
void Card::setY(int y) {
	this->y = y;
}
bool Card::containsPos(sf::Vector2i pos) {
	if (pos.x < x + getWidth() && pos.x > x &&
		pos.y < y + getHeight() && pos.y > y) {
		
		return true;
	}
	return false;
}

void Card::setOrientation(bool orientation) {
	
	this->orientation = orientation;
}

bool Card::getOrientation() {
	return orientation;
}

void Card::draw(sf::RenderWindow& window, sf::Texture& deckSpriteSheet) {
	sf::IntRect loc = sf::IntRect((int)((rank - 1) * 345),((int)suit) * 528,width,height);
	if (rank == -1) {
		loc.top = height * 4;
		loc.left = width * 1;
	}
	if (!orientation) {
		loc.left = width * 2;
		loc.top = height * 4;
	}
	sf::Sprite sprite;
	sprite.setTexture(deckSpriteSheet);
	sprite.scale(sf::Vector2f(scale, scale));
	sprite.setTextureRect(loc);
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	window.draw(sprite);
}

void Card::drawBlank(sf::RenderWindow& window, sf::Texture& deckSpriteSheet) {
	sf::IntRect loc = sf::IntRect((int)((rank - 1) * 345),((int)suit) * 528,width,height);
	loc.top = height * 4;
	loc.left = width * 1;
	sf::Sprite sprite;
	sprite.setTexture(deckSpriteSheet);
	sprite.scale(sf::Vector2f(scale, scale));
	sprite.setTextureRect(loc);
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	window.draw(sprite);

}
std::ostream& operator <<(std::ostream& out, const Card& card) {
	out << "(" << card.rank << " " << (int)card.suit << ")";
	
	return out;
}

bool operator ==(const Card& card1, const Card& card2) {
	return (card1.rank == card2.rank && card1.suit == card2.suit);
}