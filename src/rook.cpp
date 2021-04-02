#include "rook.hpp"

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
((*moves)[y][x] = true)\
)

Rook::Rook(bool isWhite) 
{
	type = 'r';
	texture.loadFromFile("pieces.png", sf::IntRect(320*4, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

void Rook::get_legal_moves(std::vector<std::vector<bool>>* moves, std::vector<std::vector<Piece*>> board, unsigned short x, unsigned short y)
{
	bool stop = false;

	for(int i = x+1;i < 8 && !stop;i++)
		ADD_MOVE(y,i);
	
	stop = false;

	for(int i = x-1;i >= 0 && !stop;i--)
		ADD_MOVE(y,i);
	
	stop = false;

	for(int i = y+1;i < 8 && !stop;i++)
		ADD_MOVE(i,x);

	stop = false;

	for(int i = y-1;i >= 0 && !stop;i--)
		ADD_MOVE(i,x);
}
