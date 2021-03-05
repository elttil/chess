#include "pawn.hpp"

Pawn::Pawn(bool isWhite)
{
	type = 'p';
	texture.loadFromFile("pieces.png", sf::IntRect(320*5, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

bool Pawn::can_move(int y, int x, Piece* board[8][8], bool *stop = nullptr)
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

void Pawn::get_legal_moves(bool moves[8][8], Piece* board[8][8], unsigned short x, unsigned short y)
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
