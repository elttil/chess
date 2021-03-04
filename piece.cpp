#include "piece.hpp"
#include <iostream>

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
(moves[y][x] = true)\
)

Piece::Piece()
	: isWhite(true), 
	mainObj()
{
}

void Piece::draw(sf::RenderWindow& window)
{
	window.draw(mainObj);
}

void Piece::setPosition(float x,float y)
{
	mainObj.setPosition(sf::Vector2f(x,y));
}

bool Piece::contains(sf::Vector2f pos)
{
	return mainObj.getGlobalBounds().contains(pos);
}

bool Piece::is_white() { return isWhite; }

char Piece::get_type() { return type; }
