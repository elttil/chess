#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "piece.hpp"

class Bishop : public Piece
{
public:
	Bishop(bool);
	void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short);
};
#endif
