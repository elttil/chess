#include "knight.hpp"

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board))&&\
((*moves)[y][x] = true)\
)

Knight::Knight(bool isWhite)
{
	type = 'n';
	texture.loadFromFile("pieces.png", sf::IntRect(320*3, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

void Knight::get_legal_moves(std::vector<std::vector<bool>>* moves, std::vector<std::vector<Piece*>> board, unsigned short x, unsigned short y)
{
	ADD_MOVE(y+2, x+1);
	ADD_MOVE(y+2, x-1);
	ADD_MOVE(y-2, x+1);
	ADD_MOVE(y-2, x-1);

	ADD_MOVE(y-1, x+2);
	ADD_MOVE(y-1, x-2);
	ADD_MOVE(y+1, x+2);
	ADD_MOVE(y+1, x-2);
}
