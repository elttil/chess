#include "king.hpp"

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board))&&\
(moves[y][x] = true)\
)

King::King(bool isWhite)
{
	type = 'k';
	texture.loadFromFile("pieces.png", sf::IntRect(0, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

void King::get_legal_moves(bool moves[8][8], Piece* board[8][8], unsigned short x, unsigned short y)
{
	ADD_MOVE(y+1, x+1);
	ADD_MOVE(y+1, x-1);
	ADD_MOVE(y-1, x+1);
	ADD_MOVE(y-1, x-1);
	ADD_MOVE(y+1, x);
	ADD_MOVE(y-1, x);
	ADD_MOVE(y, x+1);
	ADD_MOVE(y, x-1);

	//Castling
	if(this->has_moved())
		return;

	if(x != 4)
		return;

	//Make sure that there is room to castle king side
	if(board[y][6] != nullptr || board[y][5] != nullptr)
		goto next;

	if(board[y][7] == nullptr)
		goto next;

	if(((Piece*)board[y][7])->get_type() != 'r' )
		goto next;

	if(((Piece*)board[y][7])->has_moved())
		goto next;
	
	moves[y][x+2] = true;

next:

	//Queen side castle
	if(board[y][1] != nullptr || board[y][2] != nullptr || board[y][3] != nullptr)
		return;

	if(board[y][0] == nullptr)
		return;

	if(((Piece*)board[y][0])->get_type() != 'r' )
		return;

	if(((Piece*)board[y][0])->has_moved())
		return;
	
	moves[y][x-2] = true;
}
