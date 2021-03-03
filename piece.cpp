#include "piece.hpp"
#include <iostream>

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
(moves[y][x] = true)\
)

Piece::Piece(char type)
	: isWhite(true), 
	mainObj()
{
	this->type = type;

	int xposition;

	switch(type)
	{
		case 'P': isWhite = false;
		case 'p':
			xposition = 5;
			break;
		case 'R': isWhite = false;
		case 'r':
			xposition = 4;
			break;
		case 'N': isWhite = false;
		case 'n':
			xposition = 3;
			break;
		case 'B': isWhite = false;
		case 'b':
			xposition = 2;
			break;
		case 'Q': isWhite = false;
		case 'q':
			xposition = 1;
			break;
		case 'K': isWhite = false;
		case 'k':
			xposition = 0;
			break;
	}

	texture.loadFromFile("pieces.png", sf::IntRect(320*xposition, ((int)isWhite)*320, 320, 320));

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

bool Piece::contains(sf::Vector2f pos)
{
	return mainObj.getGlobalBounds().contains(pos);
}

bool Piece::is_white() { return isWhite; }

char Piece::get_type() { return type; }

/*bool Piece::can_move(int y, int x, Piece* board[8][8], bool *stop = nullptr)
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

void Piece::get_legal_moves(bool moves[8][8], Piece* board[8][8], unsigned short x, unsigned short y)
{
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
			moves[i][j] = { false };

	bool stop = false;

	if(this->get_type() == 'r' || this->get_type() == 'R')
	{
		for(int i = x+1;i < 8 && stop == false;i++)
			ADD_MOVE(y,i);
		
		stop = false;

		for(int i = x-1;i >= 0 && stop == false;i--)
			ADD_MOVE(y,i);
		
		stop = false;

		for(int i = y+1;i < 8 && stop == false;i++)
			ADD_MOVE(i,x);

		stop = false;

		for(int i = y-1;i >= 0 && stop == false;i--)
			ADD_MOVE(i,x);
	}
	else if(this->get_type() == 'p' || this->get_type() == 'P')
	{
		if(y == 0) return;

		if(y == 6 && board[y-1][x] == nullptr)
			moves[y-2][x] = true;
		
		if(board[y-1][x] == nullptr)
			moves[y-1][x] = true;

		if(x > 0)
			if(board[y-1][x-1] != nullptr)
				if(((Piece*)board[y-1][x-1])->is_white() != this->is_white())
					moves[y-1][x-1] = true;

		if(x < 7)
			if(board[y-1][x+1] != nullptr)
				if(((Piece*)board[y-1][x+1])->is_white() != this->is_white())
					moves[y-1][x+1] = true;

	}
	else if(this->get_type() == 'b' || this->get_type() == 'B')
	{
		for(int i = y+1, j = x+1;i < 8 && j < 8 && !stop;i++,j++)
			ADD_MOVE(i,j);

		stop = false;

		for(int i = y-1, j = x-1;i >= 0 && j >= 0 && !stop;i--,j--)
			ADD_MOVE(i,j);

		stop = false;

		for(int i = y+1, j = x-1;i < 8 && j >= 0 && !stop;i++,j--)
			ADD_MOVE(i,j);
		
		stop = false;

		for(int i = y-1, j = x+1;i >= 0 && j < 8 && !stop;i--,j++)
			ADD_MOVE(i,j);
	}
	else if(this->get_type() == 'n' || this->get_type() == 'N')
	{
		ADD_MOVE(y+2, x+1);
		ADD_MOVE(y+2, x-1);
		ADD_MOVE(y-2, x+1);
		ADD_MOVE(y-2, x-1);
	}
	else if (this->get_type() == 'q' || this->get_type() == 'Q')
	{
		for(int i = y+1, j = x+1;i < 8 && j < 8 && !stop;i++,j++)
			ADD_MOVE(i,j);

		stop = false;

		for(int i = y-1, j = x-1;i >= 0 && j >= 0 && !stop;i--,j--)
			ADD_MOVE(i,j);

		stop = false;

		for(int i = y+1, j = x-1;i < 8 && j >= 0 && !stop;i++,j--)
			ADD_MOVE(i,j);
		
		stop = false;

		for(int i = y-1, j = x+1;i >= 0 && j < 8 && !stop;i--,j++)
			ADD_MOVE(i,j);

		stop = false;

		for(int i = x+1;i < 8 && stop == false;i++)
			ADD_MOVE(y,i);

		stop = false;

		for(int i = x-1;i >= 0 && stop == false;i--)
			ADD_MOVE(y,i);

		stop = false;

		for(int i = y+1;i < 8 && stop == false;i++)
			ADD_MOVE(i,x);

		stop = false;

		for(int i = y-1;i >= 0 && stop == false;i--)
			ADD_MOVE(i,x);
	}
}*/
