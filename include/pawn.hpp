#include "piece.hpp"

class Pawn : public Piece
{
public:
	Pawn(bool);
	bool has_double_moved();
	void set_double_move(bool);
	void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short);
private:
	bool double_move;
};
