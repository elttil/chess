#include "piece.hpp"

class Queen : protected Piece
{
public:
	Queen(bool);
	bool can_move(int, int, Piece*[8][8], bool*);
	void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short);
};