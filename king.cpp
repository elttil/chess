#include "king.hpp"

King::King(bool isWhite)
{
	type = 'k';
	hasMoved = false;
	texture.loadFromFile("pieces.png", sf::IntRect(0, 0+((int)isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
}
