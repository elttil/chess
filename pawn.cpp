#include "pawn.hpp"

Pawn::Pawn(bool isWhite)
{
	type = 'p';
	hasMoved = false;
	texture.loadFromFile("pieces.png", sf::IntRect(320*5, 0+((int)isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
}
