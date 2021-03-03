#pragma once
#include <SFML/Graphics.hpp>
#include "piece.hpp"

class Game
{
public:
	Game();
	void update_game();
	void update_window();
	void update_pieces();
	bool is_open();
	void apply_fen_notation(const char*, void*[8][8]);
private:
	void *board[8][8];
	bool moves[8][8];
	sf::RectangleShape box;
	sf::Sprite background;
	sf::Event evnt;
	sf::RenderWindow window;
	sf::Texture backTexture;
	Piece *selectedPiece;
};
