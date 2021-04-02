#include "piece.hpp"

class King : public Piece
{
public:
	King(bool);
	void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short);
};
