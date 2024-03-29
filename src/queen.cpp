#include "queen.hpp"
#include <SFML/Graphics.hpp>

#define ADD_MOVE(y,x) (\
(this->can_move(y, x, board, &stop))&&\
((*moves)[y][x] = true)\
)

Queen::Queen(bool isWhite)
{
	type = 'q';
	texture.loadFromFile("pieces.png", sf::IntRect(320, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

void Queen::get_legal_moves(std::vector<std::vector<bool>>* moves, std::vector<std::vector<Piece*>> board, unsigned short x, unsigned short y)
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
