#include "piece.hpp"

class Pawn : protected Piece
{
public:
	Pawn(bool);
	bool has_double_moved();
	void set_double_move(bool);
	void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short);
private:
	bool double_move;
};
