#include "piece.hpp"

class Knight : public Piece
{
public:
	Knight(bool);
	void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short);
};
