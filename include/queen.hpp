#include "piece.hpp"

class Queen : public Piece
{
public:
	Queen(bool);
	void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short);
};
