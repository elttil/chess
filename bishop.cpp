#include "bishop.hpp"

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
(moves[y][x] = true)\
)

Bishop::Bishop(bool isWhite)
{
	type = 'b';
	texture.loadFromFile("pieces.png", sf::IntRect(320*2, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

void Bishop::get_legal_moves(bool moves[8][8], Piece* board[8][8], unsigned short x, unsigned short y)
{
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

}
