#include "piece.hpp"

Piece::Piece()
	: mainObj()
{
	type = 'u';
	hasMoved = false;
	texture.loadFromFile("pieces.png", sf::IntRect(0, 0, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
}

void Piece::draw(sf::RenderWindow& window)
{
	window.draw(mainObj);
}

void Piece::setPosition(float x,float y)
{
	mainObj.setPosition(sf::Vector2f(x,y));
}
