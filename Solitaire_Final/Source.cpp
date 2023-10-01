#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Solitaire.h"

int main() {
    srand(static_cast<unsigned>(time(0)));
    sf::Texture deckSpriteSheet;
    if (!deckSpriteSheet.loadFromFile("Img/Cards.png")) {
        cout << "\n image not found ";
        return 1;
    }
    Solitaire solitaire(deckSpriteSheet);
    solitaire.run();

    return 0;
}
