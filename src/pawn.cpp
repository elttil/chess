#include "pawn.hpp"
#include <iostream>

Pawn::Pawn(bool isWhite)
{
	type = 'p';
	texture.loadFromFile("pieces.png", sf::IntRect(320*5, 0+((int)!isWhite)*320, 320, 320));
	texture.setSmooth(true);
	mainObj.setTexture(texture);
	mainObj.setScale(sf::Vector2f(0.19375,0.19375));
	this->isWhite = isWhite;
}

void Pawn::get_legal_moves(std::vector<std::vector<bool>>* moves, std::vector<std::vector<Piece*>> board, unsigned short x, unsigned short y)
{
	if(this->is_white())
	{
		if(y == 0) return;

		if(y == 6 && board[y-2][x] == nullptr)
			(*moves)[y-2][x] = true;
		
		if(board[y-1][x] == nullptr)
			(*moves)[y-1][x] = true;

		if(x > 0)
		{
			if(board[y-1][x-1] != nullptr)
				if(((Piece*)board[y-1][x-1])->is_white() != this->is_white())
					(*moves)[y-1][x-1] = true;

			//en passant
			if(y == 3)
				if(board[y][x-1] != nullptr)
					if(board[y+1][x-1] == nullptr)
						if(((Piece*)board[y][x-1])->get_type() == 'p')
							if(((Pawn*)board[y][x-1])->has_double_moved())
								(*moves)[y-1][x-1] = true;
		}

		if(x < 7)
		{
			if(board[y-1][x+1] != nullptr)
				if(((Piece*)board[y-1][x+1])->is_white() != this->is_white())
					(*moves)[y-1][x+1] = true;
			
			//en passant
			if(y == 3)
				if(board[y][x+1] != nullptr)
					if(board[y+1][x+1] == nullptr)
						if(((Piece*)board[y][x+1])->get_type() == 'p')
							if(((Pawn*)board[y][x+1])->has_double_moved())
								(*moves)[y-1][x+1] = true;
		}
	}
	else
	{
		if(y == 7) return;

		if(y == 1 && board[y+2][x] == nullptr)
			(*moves)[y+2][x] = true;
		
		if(board[y+1][x] == nullptr)
			(*moves)[y+1][x] = true;

		if(x > 0)
		{
			if(board[y+1][x-1] != nullptr)
				if(((Piece*)board[y+1][x-1])->is_white() != this->is_white())
					(*moves)[y+1][x-1] = true;

			//en passant
			if(y == 4)
				if(board[y][x-1] != nullptr)
					if(board[y-1][x-1] == nullptr)
						if(((Piece*)board[y][x-1])->get_type() == 'p')
							if(((Pawn*)board[y][x-1])->has_double_moved())
								(*moves)[y+1][x-1] = true;
		}

		if(x < 7)
		{
			if(board[y+1][x+1] != nullptr)
				if(((Piece*)board[y+1][x+1])->is_white() != this->is_white())
					(*moves)[y+1][x+1] = true;

			//en passant
			if(y == 4)
				if(board[y][x+1] != nullptr)
					if(board[y-1][x+1] == nullptr)
						if(((Piece*)board[y][x+1])->get_type() == 'p')
							if(((Pawn*)board[y][x+1])->has_double_moved())
								(*moves)[y+1][x+1] = true;
		}
	}
}

bool Pawn::has_double_moved() { return double_move; }

void Pawn::set_double_move(bool arg) { double_move = arg; }
