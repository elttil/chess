#include "game.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"
#include <iostream>

Game::Game() :
	board { nullptr },
	moves { false },
	window(sf::VideoMode(495, 495), "My window")
{
	backTexture.loadFromFile("back.png");
	background.setTexture(backTexture);

	sf::Color red(255, 0, 0, 100);
	box.setFillColor(red);
	box.setSize(sf::Vector2f(62,62));

	this->apply_fen_notation("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board);
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
		}

	printf("RUNNING\n");
}

void Game::apply_fen_notation(const char* fen_string, void *board[8][8])
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

		if(i > 0)
			if(fen_string[i-1] == ' ')
			{
				whites_turn = (fen_string[i] == 'w');
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
				break;
		}
		row++;
	}
}

void Game::update_game()
{
	while(window.pollEvent(evnt))
	{
		if(evnt.type == sf::Event::Closed)
			window.close();
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
				for(size_t i = 0;i < 8;i++)
					for(size_t j = 0;j < 8;j++)
						if(board[i][j] == selectedPiece)
						{
							board[i][j] = nullptr;
							break;
						}

				if(board[boardPosition.y][boardPosition.x] != nullptr)
				{
					// This indicates that the new movment captures
					// a piece and therefore we have to free that
					// pieces memory.
					delete (Piece*)board[boardPosition.y][boardPosition.x];
				}

				board[boardPosition.y][boardPosition.x] = selectedPiece;
				whites_turn = !whites_turn;
			}

			update_pieces();
		}

		bool wasPressed = false;
		for(size_t i = 0;i < 8;i++)
		{
			for(size_t j = 0;j < 8;j++)
			{
				if(board[i][j] == nullptr)
					continue;

				if(((Piece*)board[i][j])->contains((sf::Vector2f)sf::Mouse::getPosition(window)))
				{
					selectedPiece = (Piece*)board[i][j];
					if(selectedPiece->is_white() == whites_turn)
					{
						selectedPiece = nullptr;
						break;
					}

					for(size_t i = 0;i < 8;i++)
						for(size_t j = 0;j < 8;j++)
							moves[i][j] = { false };
					selectedPiece->get_legal_moves(moves, (Piece*(*)[8])board, j, i);
					wasPressed = true;
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

			((Piece*)board[i][j])->draw(window);
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
