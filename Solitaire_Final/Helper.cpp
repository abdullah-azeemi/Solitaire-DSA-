#include "Helper.h"

TrainClass::TrainClass() : length(0), head(nullptr) { }

void TrainClass::push(Card card) {
	Dabba* cur = new Dabba(card);
	if (length == 0) head = cur;
	else {
		cur->nextNode = head;
		head = cur;
	}
	length++;
}

Card TrainClass::pop() {
	Dabba* top = head;
	head = top->nextNode;
	Card topData = top->data;
	delete top;
	length -= 1;
	return topData;
}

// Return top card
Card TrainClass::top() {
	if (head)
		return head->data;
	else return Card();
}

// Return size of Stack
int TrainClass::size() {
	return length;
}

// Clear Stack
void TrainClass::empty() {
	while (head->nextNode != nullptr) {
		Dabba* top = head->nextNode;
		delete head;
		head = top;
	}
	head = nullptr;
	length = 0;
}

void TrainClass::forEach(NodeHandler handler, sf::RenderWindow& window, sf::Texture& deckSpriteSheet) {
	Dabba* cur = head;
	int index = 0;
	while (cur != nullptr) {
		handler(cur->data, index, window, deckSpriteSheet);
		cur = cur->nextNode;
		index++;
	}
}

std::ostream& operator <<(std::ostream& out, const TrainClass& ll) {
	out << ll.length;
	return out;
}