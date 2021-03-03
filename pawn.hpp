#include "piece.hpp"

class Pawn : protected Piece
{
public:
	Pawn(bool);
	bool can_move(int, int, Piece*[8][8], bool*);
	void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short);
};
