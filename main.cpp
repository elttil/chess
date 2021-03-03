#include <iostream>
#include "game.hpp"

int main(void)
{
	Game chess;
	while(chess.is_open())
	{
		chess.update_game();
		chess.update_window();
	}
/*	sf::RenderWindow window(sf::VideoMode(495, 495), "My window");

	void *board[8][8] = { nullptr };

	sf::Texture texture;
	texture.loadFromFile("back.png");

	sf::Sprite background;
	background.setTexture(texture);

	for(size_t i = 0;i < 8;i++)
		for(size_t j = 0;j < 8;j++)
		{
			if(board[i][j] == nullptr)
				continue;
			
			((Piece*)board[i][j])->setPosition(j*62,i*62);
		}

	bool moves[8][8] = { false };
	bool drawMoves = true;
	sf::Color red(255, 0, 0, 100);
	sf::RectangleShape box;
	box.setFillColor(red);
	box.setSize(sf::Vector2f(62,62));

	while(window.isOpen())
	{
		sf::Event evnt;
		while(window.pollEvent(evnt))
		{
			if(evnt.type == sf::Event::Closed)
				window.close();
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			bool wasPressed = false;
			for(size_t i = 0;i < 8;i++)
				for(size_t j = 0;j < 8;j++)
				{
					if(board[i][j] == nullptr)
						continue;

					if(((Piece*)board[i][j])->contains((sf::Vector2f)sf::Mouse::getPosition(window)))
					{
						((Piece*)board[i][j])->getLegalMoves(moves, board, j, i);
						wasPressed = true;
						drawMoves = true;
					}
				}

			if(!wasPressed)
			{
				drawMoves = false;
			}
		}

		window.clear();
		window.draw(background);
		for(size_t i = 0;i < 8;i++)
			for(size_t j = 0;j < 8;j++)
			{
				if(board[i][j] == nullptr)
					continue;
	
				((Piece*)board[i][j])->draw(window);
			}
		if(drawMoves)
			for(size_t i = 0;i < 8;i++)
			for(size_t j = 0;j < 8;j++)
			{
				if(moves[i][j] == false)
					continue;
				
				box.setPosition(sf::Vector2f(i*62,j*62));
				window.draw(box);
			}

		window.display();
	}*/
}
