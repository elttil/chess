#include <iostream>
#include "piece.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "king.hpp"
#include "queen.hpp"

void apply_fen_notation(const char* fen_string, void *board[64])
{
	bool isWhite;
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
		isWhite = true;
		switch(fen_string[i])
		{
			case 'P': isWhite = false;
			case 'p':
				board[row+col*8] = new Pawn(isWhite);
				break;
			case 'R': isWhite = false;
			case 'r':
				board[row+col*8] = new Rook(isWhite);
				break;
			case 'B': isWhite = false;
			case 'b':
				board[row+col*8] = new Bishop(isWhite);
				break;
			case 'N': isWhite = false;
			case 'n':
				board[row+col*8] = new Knight(isWhite);
				break;
			case 'Q': isWhite = false;
			case 'q':
				board[row+col*8] = new Queen(isWhite);
				break;
			case 'K': isWhite = false;
			case 'k':
				board[row+col*8] = new King(isWhite);
				break;
			default:
				board[row+col*8] = new Piece();
				break;
		}
		row++;
	}
}

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(495, 495), "My window");

	void *board[64] = { nullptr };

	sf::Texture texture;
	texture.loadFromFile("back.png");

	sf::Sprite background;
	background.setTexture(texture);

	apply_fen_notation("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR", board);
	unsigned int x,y;

	for(size_t i = 0;i < 64;i++)
	{
		if(board[i] == nullptr)
			continue;
		
		x = (i%8)*62;
		y = (i/8)*62;
		((Piece*)board[i])->setPosition(x,y);
	}

	while(window.isOpen())
	{
		sf::Event evnt;
		while(window.pollEvent(evnt))
		{
			if(evnt.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);
		for(size_t i = 0;i < 64;i++)
		{
			if(board[i] == nullptr)
				continue;

			((Piece*)board[i])->draw(window);
		}
		window.display();
	}
}
