#include "piece.hpp"

class Knight : protected Piece
{
public:
	Knight(bool);
	void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short);
};
