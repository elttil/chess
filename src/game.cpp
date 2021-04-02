#include "game.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"
#include <iostream>

Game::Game(bool arg) :
	selectedPiece(nullptr),
	board(8,std::vector<Piece*>(8, nullptr)),
	moves(8,std::vector<bool>(8, false)),
	window(sf::VideoMode(495, 495), "My window"),
	whites_turn ( true ),
	sock(0)
{
	backTexture.loadFromFile("back.png");
	background.setTexture(backTexture);

	sf::Color red(255, 0, 0, 100);
	box.setFillColor(red);
	box.setSize(sf::Vector2f(62,62));

	this->apply_fen_notation("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", board);
	this->update_pieces();
}

Game::~Game()
{
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
		{
			if(board[i][j] == nullptr)
				continue;

			delete (Piece*)(board[i][j]);
			board[i][j] = nullptr;
		}
}

void Game::apply_fen_notation(const char* fen_string, std::vector<std::vector<Piece*>>&board)
{
	int row,col;
	row = col = 0;
	for(size_t i = 0;fen_string[i] != 0;i++)
	{
		if(fen_string[i] == '/')
		{
			col++;
			row = 0;
			continue;
		}
		if((int)fen_string[i] < 58 && (int)fen_string[i] > 47)
		{
			row += (int)(fen_string[i]-'0');
			continue;
		}

		bool isWhite = false;
		switch(fen_string[i])
		{
			case 'P': isWhite = true;
			case 'p':
				board[col][row] = new Pawn(isWhite);
				break;
			case 'R': isWhite = true;
			case 'r':
				board[col][row] = new Rook(isWhite);
				break;
			case 'B': isWhite = true;
			case 'b':
				board[col][row] = new Bishop(isWhite);
				break;
			case 'N': isWhite = true;
			case 'n':
				board[col][row] = new Knight(isWhite);
				break;
			case 'Q': isWhite = true;
			case 'q':
				board[col][row] = new Queen(isWhite);
				break;
			case 'K': isWhite = true;
			case 'k':
				board[col][row] = new King(isWhite);
				king_position[!isWhite].y = col;
				king_position[!isWhite].x = row;
				break;
		}
		row++;
	}
}

bool Game::is_in_check(bool white, std::vector<std::vector<Piece*>>board)
{
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
		{
			if(board[i][j] == nullptr)
				continue;

			if(((Piece*)board[i][j])->is_white() == white)
				continue;
			
			std::vector<std::vector<bool>> possible_moves(8, std::vector<bool>(8, false));
			board[i][j]->get_legal_moves(&possible_moves, board, j, i);
			if(possible_moves[king_position[!white].y][king_position[!white].x] == true)
				return true;
		}

	return false;
}

bool Game::is_in_check_mate(bool white, std::vector<std::vector<Piece*>>board)
{
	std::vector<std::vector<Piece*>> potential_board(board);
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
		{
			if(potential_board[i][j] == nullptr)
				continue;

			if(potential_board[i][j]->is_white() != white)
				continue;
			
			std::vector<std::vector<bool>> possible_moves(8, std::vector<bool>(8, false));
			potential_board[i][j]->get_legal_moves(&possible_moves, potential_board, j, i);
			for(size_t a = 0;a < 8;a++)
				for(size_t b = 0;b < 8;b++)
				{
					if(!possible_moves[a][b]) continue;
					if(board[i][j] == nullptr)
						continue;

					potential_board[a][b] = board[i][j];
					potential_board[i][j] = nullptr;

					sf::Vector2i tmp_king_position = king_position[!white];

					if(potential_board[a][b]->get_type() == 'k')
					{
						king_position[!white].x = b;
						king_position[!white].y = a;
					}

					if(!this->is_in_check(white, potential_board))
					{
						king_position[!white] = tmp_king_position;
						return false;
					}

					king_position[!white] = tmp_king_position;

					potential_board[i][j] = board[i][j];
					potential_board[a][b] = board[a][b];
				}
		}

	return true;
}

void Game::move_selectedpiece(sf::Vector2i dst)
{
	if(board[dst.y][dst.x] != nullptr)
	{
		// This indicates that the new movment captures
		// a piece and therefore we have to free that
		// pieces memory.
		delete (Piece*)board[dst.y][dst.x];
		board[dst.y][dst.x] = nullptr;
	}

	if(selectedPiece->get_type() == 'k')
	{
		//If we castelled we also need to move the rook.
	
		//First we check whether we castled
		if(abs((int)king_position[!selectedPiece->is_white()].x - dst.x) != 2)
			goto out3;
		
		//If we got to this part it means that we have castelled
		//so we will now move the rook.
		if(dst.x == 7)
		{
			//We castled king side
			board[dst.y][5] = board[dst.y][7];
			board[dst.y][7] = nullptr;
		}
		else
		{
			//We castled queen side
			board[dst.y][3] = board[dst.y][0];
			board[dst.y][0] = nullptr;
		}

out3:
		king_position[!selectedPiece->is_white()].x = dst.x;
		king_position[!selectedPiece->is_white()].y = dst.y;
	}

	if(selectedPiece->get_type() == 'p')
	{
		if(!selectedPiece->has_moved())
			if(dst.y == 3 || dst.y == 4)
				((Pawn*)selectedPiece)->set_double_move(true);

/*					if(board[dst.y][dst.x] == nullptr)
		{
			if(selectedPiece->is_white())
			{
				delete (Piece*)board[dst.y+1][dst.x];
				board[dst.y+1][dst.x] = nullptr;
			}
			else
			{
				delete (Piece*)board[dst.y-1][dst.x];
				board[dst.y-1][dst.x] = nullptr;
			}
		}*/
	}

	///////
	/*
	char move[4];

	for(unsigned short i = 0;i < 8;i++)
		for(unsigned short j = 0;j < 8;j++)
			if(board[i][j] == selectedPiece)
			{
				//src
				move[0] = j + '0';
				move[1] = i + '0';
				goto out4;
			}
out4:

	//dst
	move[2] = dst.x + '0';
	move[3] = dst.y + '0';

	send(sock, move, sizeof(move), 0);
	std::cout << "Data sent" << std::endl;
	*/
	////////


	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
			if(board[i][j] == selectedPiece)
			{
				board[i][j] = nullptr;
				break;
			}

	board[dst.y][dst.x] = selectedPiece;
	selectedPiece->set_has_moved(true);

	whites_turn = !whites_turn;
	if(this->is_in_check_mate(true, board))
		this->winner = 2;

	if(this->is_in_check_mate(false, board))
		this->winner = 1;

}

void Game::update_game()
{
	while(window.pollEvent(evnt))
	{
		if(evnt.type == sf::Event::Closed)
			window.close();
	}

	if(winner != 0)
	{
		if(winner == 1)
			puts("WHITE WON");
		else
			puts("BLACK WON");
		
		window.close();
		return;
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if(selectedPiece)
		{
			sf::Vector2i boardPosition = sf::Mouse::getPosition(window);
			if(boardPosition.x > 495) return;
			if(boardPosition.y > 495) return;
			boardPosition.x /= 62.5;
			boardPosition.y /= 62.5;
			if(moves[boardPosition.y][boardPosition.x] == true)
			{
				move_selectedpiece(boardPosition);
				update_pieces();
			}
		}

		bool wasPressed = false;
		for(size_t i = 0;i < 8;i++)
		{
			for(size_t j = 0;j < 8;j++)
			{
				if(board[i][j] == nullptr)
					continue;

				if(!((Piece*)board[i][j])->contains((sf::Vector2f)sf::Mouse::getPosition(window)))
					continue;

				wasPressed = true;
				selectedPiece = (Piece*)board[i][j];
				if(selectedPiece->is_white() != whites_turn)
				{
					selectedPiece = nullptr;
					break;
				}

				for(size_t a = 0;a < 8;a++)
					for(size_t b = 0;b < 8;b++)
						moves[a][b] = false;

				selectedPiece->get_legal_moves(&moves, board, j, i);

				//We can not castle out of a check therefore
				//if we are in check and have gotten the moves to 
				//castle we must disable those moves
				if(selectedPiece->get_type() == 'k')
				{
					sf::Vector2i position;
					position = king_position[!selectedPiece->is_white()];

					if(position.x == 4)	
						if(moves[position.y][position.x+2] == true ||
						   moves[position.y][position.x-2] == true)
						{
							if(is_in_check(selectedPiece->is_white(), board))
							{
								moves[position.y][position.x+2] = false;
								moves[position.y][position.x-2] = false;
							}
						}
				}

				//Determine whether the move may result in a check
				//for the player
				std::vector<std::vector<Piece*>> potential_board(board);
				for(size_t a = 0;a < 8;a++)
					for(size_t b = 0;b < 8;b++)
					{
						if(moves[a][b] == false) continue;
						potential_board[a][b] = selectedPiece;
						potential_board[i][j] = nullptr;

						const sf::Vector2i tmp_king_position = king_position[!selectedPiece->is_white()];
						if(selectedPiece->get_type() == 'k')
						{
							//If we castelled we also need to move the rook.
						
							//First we check whether we castled
							if(abs((int)king_position[!selectedPiece->is_white()].x - (int)b) != 2)
								goto out2;

							//If we got to this part it means that we have castelled
							//so we will now move the rook.
							if(b == 7)
								//We castled king side
								potential_board[a][5] = (Piece*)board[a][b];
							else
								//We castled queen side
								potential_board[a][3] = (Piece*)board[a][b];

							potential_board[a][b] = nullptr;
out2:
							king_position[!selectedPiece->is_white()].x = b;
							king_position[!selectedPiece->is_white()].y = a;
						}

						if(this->is_in_check(selectedPiece->is_white(), potential_board))
							moves[a][b] = false;

						king_position[!selectedPiece->is_white()] = tmp_king_position;
						if(selectedPiece->get_type() == 'p')
						{
							if(board[i][j] == nullptr)
							{
								if(selectedPiece->is_white())
								{
									delete (Piece*)board[i+1][j];
									board[i+1][j] = nullptr;
								}
								else
								{
									delete (Piece*)board[i-1][j];
									board[i-1][j] = nullptr;
								}
							}
						}

						potential_board[i][j] = selectedPiece;
						potential_board[a][b] = (Piece*)board[a][b];
					}
			}
		}
		if(!wasPressed)
			selectedPiece = nullptr;
	}
}

void Game::update_pieces()
{
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
		{
			if(board[i][j] == nullptr)
				continue;
			
			((Piece*)board[i][j])->setPosition(j*62,i*62);
		}
}

void Game::update_window()
{
	window.clear();
	window.draw(background);
	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
		{
			if(board[i][j] == nullptr)
				continue;

			board[i][j]->draw(window);
		}

	if(selectedPiece)
		for(size_t i = 0;i < 8;i++)
			for(size_t j = 0;j < 8;j++)
			{
				if(moves[i][j] == false)
					continue;
				
				box.setPosition(sf::Vector2f(j*62,i*62));
				window.draw(box);
			}

	window.display();
}

bool Game::is_open() { return window.isOpen(); }
