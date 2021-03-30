#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "piece.hpp"

class Bishop : protected Piece
{
public:
	Bishop(bool);
	void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short);
};
#endif
