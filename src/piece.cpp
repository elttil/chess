#include "piece.hpp"
#include <iostream>

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
(moves[y][x] = true)\
)

Piece::Piece() :
	hasMoved(false),
	mainObj()
{
}

bool Piece::has_moved()
{
	return hasMoved;
}

void Piece::set_has_moved(bool arg)
{
	hasMoved = arg;
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

bool Piece::can_move(int y, int x, std::vector<std::vector<Piece*>> board, bool* stop)
{ 
	if(x < 0 || x >= 8)
		return false;

	if(y < 0 || y >= 8)
		return false;

	if(board[y][x] != nullptr)
	{
		if((board[y][x])->is_white() != this->is_white())
		{
			if(stop != nullptr)
				*stop = true;
			return true;
		}
		else if(stop != nullptr)
		{
			*stop = true;
		}
	}

	if(board[y][x] == nullptr)
		return true;

	return false;
}
