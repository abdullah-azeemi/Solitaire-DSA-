#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<thread>
#include <SFML/Graphics.hpp>

using namespace std;
enum class Suit {
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};
static int difficulty = 1;
static int diffVar = difficulty;

static bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp)
{
	if (sprite.contains(mp)) {
		return true;
	}
	return false;
}
