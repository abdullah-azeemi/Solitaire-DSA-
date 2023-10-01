#include "Solitaire.h"
#include"Utility.h"
#include<SFML/Audio.hpp>
#include<Windows.h>

Solitaire::Solitaire(sf::Texture& deckSpriteSheet) :
	deckSpriteSheet(deckSpriteSheet),stock(deckSpriteSheet, 100, 500), waste(deckSpriteSheet, 1190, 600), tableau(deckSpriteSheet, 180, 240), foundation(deckSpriteSheet, 260, 60), undoButtonClicked(false), redoButtonClicked(false){
	startGame();
}
void Solitaire::startGame() {
	P->setName("Abdullah");
	stock.fill();
	stock.shuffle();
	tableau.fillCascades(stock);
}

void Solitaire::draw(sf::RenderWindow& window) {
	stock.draw(window);
	tableau.draw(window);
	waste.draw(window);
	foundation.draw(window);
}

void Solitaire::saveCard(Card card, sf::Vector2i pos) {
	if (card.getRank() > 0 && cardSelected == false) {
		savedPos = pos;
		savedCards.push_back(card);
		cardSelected = true;
		cout << "\n Saved " << card;
	}
}

void Solitaire::unsaveCard() {
	savedPos = sf::Vector2i(0, 0);
	cardSelected = false;
	savedCards.clear();
	cout << "\n]Unsaved card";
}
bool Solitaire::isValidMove(sf::Vector2i pos) {

	if (isValidSource(pos)) {
		stStock.push(stock);
		stWaste.push(waste);
		stTableau.push(tableau);
		stFoundation.push(foundation);
		this->sc += rand() % 10;
		return true;
	}
	if (!cardSelected) {

		if (waste.containsPos(pos) && waste.getCardAt(pos).getOrientation() == 1) {
			saveCard(waste.getCardAt(pos), pos);
			saveCardClass = 1;
			cardSelected = true;
			stStock.push(stock);
			stWaste.push(waste);
			stTableau.push(tableau);
			stFoundation.push(foundation);
			this->sc += rand() % 10;
			return true;

		}
		else if (tableau.containsPos(pos) && tableau.getCardAt(pos).getOrientation() == 1) {
			tableau.saveCards(pos, tableau.getCardAt(pos), savedCards);
			savedPos = pos;
			saveCardClass = 2;
			cardSelected = true;
			stStock.push(stock);
			stWaste.push(waste);
			stTableau.push(tableau);
			stFoundation.push(foundation);
			this->sc += rand() % 10;
			return true;
		}
	}

	else if (cardSelected && (isValidSource(pos) || waste.containsPos(pos) || tableau.containsPos(pos)) || foundation.containsPos(pos)) {
		if (tableau.cascadeIsEmpty(pos) || (tableau.containsPos(pos) && validCardPlacement(tableau.getCardAt(pos)) &&
			tableau.containsTopCard(tableau.getCardAt(pos)))) {

			if (tableau.cascadeIsEmpty(pos) && savedCards[0].getRank() != 13) {
				unsaveCard();
				return false;
			}

			tableau.addCardAt(pos, savedCards);

			if (saveCardClass == 1) waste.removeCardAt(savedPos);
			else if (saveCardClass == 2) tableau.removeCardAt(savedPos);
		}

		if (savedCards.size() == 1 && ((foundation.containsPos(pos)) && foundation.stackIsEmpty(pos) && savedCards[0].getRank() == 1 || (foundation.containsPos(pos) && foundation.validNextCard(savedCards[0], pos)))) {

			foundation.addCardAt(pos, savedCards);

			if (saveCardClass == 1) waste.removeCardAt(savedPos);
			else if (saveCardClass == 2) tableau.removeCardAt(savedPos);
		}
		unsaveCard();
		stStock.push(stock);
		stWaste.push(waste);
		stTableau.push(tableau);
		stFoundation.push(foundation);
		this->sc += rand() % 10;
		return true;
	}
	else {
		unsaveCard();
	}
	return false;
}

bool Solitaire::validCardPlacement(Card card) {
	if ((card.getSuit() + savedCards[0].getSuit() != 3 &&
		card.getSuit() != savedCards[0].getSuit()) &&
		card.getRank() - 1 == savedCards[0].getRank()) {
		return true;
	}
	return false;
}

bool Solitaire::isValidSource(sf::Vector2i pos) {
	if (pos.x > stock.getXBounds().x && pos.x < stock.getXBounds().y
		&& pos.y > stock.getYBounds().x && pos.y < stock.getYBounds().y) {

		waste.drawCards(stock);

		return true;
	}
	return false;
}
void Solitaire::run() {
	bool playButtonClicked = false;
	bool exitButtonClicked = false;
	int selectedLevel = 0;

	sf::RenderWindow window(sf::VideoMode(1500, 900), "Solitaire", sf::Style::Close | sf::Style::Resize);
	sf::Event event;
	sf::Font font,font1;
	if (!font.loadFromFile("Fonts/LiberationSans.ttf")) {
	}
	if (!font1.loadFromFile("Fonts/Pacifico.ttf")) {
	}

	if (playButtonClicked == false) {
		sf::RectangleShape playButton(sf::Vector2f(120, 40));
		sf::RectangleShape exitButton(sf::Vector2f(120, 40));
		int j = 0; //Playing sound once
		playButton.setPosition(570, 400);
		exitButton.setPosition(770, 400);

		playButton.setFillColor(sf::Color(100, 100, 100));
		exitButton.setFillColor(sf::Color(100, 100, 100));

		sf::Text SolitaIre("Solitaire", font1, 100);
		SolitaIre.Bold; SolitaIre.Italic; SolitaIre.setFillColor(sf::Color::Red);
		SolitaIre.setLineSpacing(2.5);
		SolitaIre.setPosition(540, 200);

		sf::Text playText("Play", font, 20);
		sf::Text exitText("Exit", font, 20);
		sf::RectangleShape easyRadioButton(sf::Vector2f(20, 20));
		sf::RectangleShape mediumRadioButton(sf::Vector2f(20, 20));
		sf::RectangleShape hardRadioButton(sf::Vector2f(20, 20));
		easyRadioButton.setPosition(535, 700); mediumRadioButton.setPosition(685, 700); hardRadioButton.setPosition(835, 700);
		easyRadioButton.setOutlineThickness(2); mediumRadioButton.setOutlineThickness(2); hardRadioButton.setOutlineThickness(2);
		easyRadioButton.setOutlineColor(sf::Color::White); mediumRadioButton.setOutlineColor(sf::Color::White); hardRadioButton.setOutlineColor(sf::Color::White);

		// Radio buttons ................
		sf::Text easyText("Easy", font, 20); sf::Text mediumText("Medium", font, 20); sf::Text hardText("Hard", font, 20);
		easyText.setFillColor(sf::Color::White); mediumText.setFillColor(sf::Color::White); hardText.setFillColor(sf::Color::White);
		easyText.setPosition(easyRadioButton.getPosition().x + 30, easyRadioButton.getPosition().y - 3);
		mediumText.setPosition(mediumRadioButton.getPosition().x + 30, mediumRadioButton.getPosition().y - 3);
		hardText.setPosition(hardRadioButton.getPosition().x + 30, hardRadioButton.getPosition().y - 3);
		sf::Text checkmark1("", font, 20); sf::Text checkmark2("", font, 20); sf::Text checkmark3("", font, 20);
		checkmark1.setFillColor(sf::Color::Green); checkmark2.setFillColor(sf::Color::Green); checkmark3.setFillColor(sf::Color::Green);



		playText.setFillColor(sf::Color::White);
		exitText.setFillColor(sf::Color::White);

		playText.setPosition(
			playButton.getPosition().x + (playButton.getSize().x - playText.getLocalBounds().width) / 2,
			playButton.getPosition().y + (playButton.getSize().y - playText.getLocalBounds().height) / 2
		);


		exitText.setPosition(
			exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2,
			exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2
		);

		// Load background image
		sf::Texture backgroundTexture;
		if (!backgroundTexture.loadFromFile("Img/b.jpg")) {
			// Handle background image loading error
		}

		sf::Sprite backgroundImage(backgroundTexture);
		float scaleFactorX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
		float scaleFactorY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
		backgroundImage.setScale(scaleFactorX, scaleFactorY);

		while (window.isOpen() && playButtonClicked== false) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
					if (isSpriteHover(playButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
						// Play button clicked
						playButtonClicked = true;
					}
					else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
						if (isSpriteHover(easyRadioButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							difficulty = 1;
							checkmark1.setString("O");
							checkmark2.setString("");
							checkmark3.setString("");
						}
						else if (isSpriteHover(mediumRadioButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							difficulty = 2;
							checkmark1.setString("");
							checkmark2.setString("O");
							checkmark3.setString("");
						}
						else if (isSpriteHover(hardRadioButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							difficulty = 3;
							checkmark1.setString("");
							checkmark2.setString("");
							checkmark3.setString("O");
						}
						else if (isSpriteHover(exitButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							exitButtonClicked = true;
							window.close();
						}
						else if (isSpriteHover(playButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							playButtonClicked = true;
							window.clear();
						}
					}
				}
			}

			window.clear();
			window.draw(backgroundImage);
			window.draw(SolitaIre);
			window.draw(easyText); window.draw(mediumText); window.draw(hardText);
			window.draw(easyRadioButton); window.draw(mediumRadioButton); window.draw(hardRadioButton);
			window.draw(easyText); window.draw(mediumText); window.draw(hardText);
			window.draw(checkmark1); window.draw(checkmark2); window.draw(checkmark3);
			window.draw(playButton); window.draw(playText);
			window.draw(exitButton); window.draw(exitText);
			window.display();
			if (j == 0) {
				PlaySound(L"intro", NULL, SND_FILENAME | SND_SYNC);
				j++;
			}
		}
	}
	PlaySound(L"sound", NULL, SND_FILENAME | SND_ASYNC);
	if (playButtonClicked) {
		bool mousePress = false;

		sf::Text scoreText;
		scoreText.setFont(font);scoreText.setCharacterSize(24);  scoreText.setFillColor(sf::Color::Red);  scoreText.setPosition(1300, 50); 
		sf::RectangleShape undoButton(sf::Vector2f(120, 40)), redoButton(sf::Vector2f(120, 40));
		undoButton.setPosition(355, 767); redoButton.setPosition(575, 767);
		undoButton.setFillColor(sf::Color(100, 100, 100)); redoButton.setFillColor(sf::Color(100, 100, 100));

		sf::Text buttonText("Undo", font, 20); sf::Text buttonText1("Redo", font, 20);
		buttonText.setFillColor(sf::Color::White); buttonText.setFillColor(sf::Color::White);
		buttonText.setPosition(
			undoButton.getPosition().x + (undoButton.getSize().x - buttonText.getLocalBounds().width) / 2,
			undoButton.getPosition().y + (undoButton.getSize().y - buttonText.getLocalBounds().height) / 2
		);
		buttonText1.setPosition(
			redoButton.getPosition().x + (redoButton.getSize().x - buttonText1.getLocalBounds().width) / 2,
			redoButton.getPosition().y + (redoButton.getSize().y - buttonText1.getLocalBounds().height) / 2
		);
		while (window.isOpen()) {
			while (window.pollEvent(event)) {

				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					std::cout << "new window width  " << event.size.width << "  new window height  " << event.size.height << std::endl;
					break;
				case sf::Event::TextEntered:
					cout << " " << char(event.text.unicode);
					break;
				}

				if (event.type == sf::Event::Closed) {
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Space) {
						//Retart need s to be implemnted
					}
				}
				if (isSpriteHover(undoButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true) {
					if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
						cout << "\n Undo button has been pressed : ";
						undoButtonClicked = true;
					}
				}
				if (isSpriteHover(redoButton.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true) {
					if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
						cout << "\n Redo button has been pressed : ";
						redoButtonClicked = true;
					}
				}
			}

			window.clear(sf::Color(50, 150, 50, 255));

			std::string scoreStr = "Score: " + std::to_string(sc);
			scoreText.setString(scoreStr);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePress) {
				mousePress = true;
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				if (isValidMove(pos)) {
				}
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mousePress = false;
			}
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (undoButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					undoButtonClicked = true;
				}
			}



			if (undoButtonClicked) {
				if (!stStock.empty()) { stock = stStock.top(); stStock1.push(stStock.top()); stStock.pop(); }
				if (!stWaste.empty()) { waste = stWaste.top(); stWaste1.push(stWaste.top()); stWaste.pop(); }
				if (!stTableau.empty()) { tableau = stTableau.top(); stTableau1.push(stTableau.top()); stTableau.pop(); }
				if (!stFoundation.empty()) { foundation = stFoundation.top(); stFoundation1.push(stFoundation.top()); stFoundation.pop(); }

				undoButtonClicked = false;
				draw(window);
				window.display();
			}
			else if (redoButtonClicked) {
				if (!stStock.empty()) { stock = stStock1.top(); stStock1.pop(); }
				if (!stWaste.empty()) { waste = stWaste1.top(); stWaste1.pop(); }
				if (!stTableau.empty()) { tableau = stTableau1.top();  stTableau1.pop(); }
				if (!stFoundation.empty()) { foundation = stFoundation1.top(); stFoundation1.pop(); }

				redoButtonClicked = false;
				draw(window);
				window.display();
			}
			draw(window);
			window.draw(undoButton); window.draw(buttonText);
			window.draw(redoButton); window.draw(buttonText1);
			window.draw(scoreText);

			window.display();
		}
	}
}




