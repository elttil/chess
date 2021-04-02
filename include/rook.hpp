#include "piece.hpp"

class Rook : public Piece
{
public:
	Rook(bool);
	void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short);
};
