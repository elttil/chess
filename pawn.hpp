#include "piece.hpp"

class Pawn : protected Piece
{
public:
	Pawn(bool);
	void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short);
};
