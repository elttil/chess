#include "queen.hpp"

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
(moves[y][x] = true)\
)

Queen::Queen(bool isWhite)
{
	type = 'q';
	texture.loadFromFile("pieces.png", sf::IntRect(320, 0+((int)isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

bool Queen::can_move(int y, int x, Piece* board[8][8], bool *stop = nullptr)
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

void Queen::get_legal_moves(bool moves[8][8], Piece* board[8][8], unsigned short x, unsigned short y)
{
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
			moves[i][j] = { false };

	bool stop = false;

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
