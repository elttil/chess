#pragma once
#include <SFML/Graphics.hpp>
#include "piece.hpp"

class Game
{
public:
	Game();
	~Game();
	void update_game();
	void update_window();
	void update_pieces();
	bool is_open();
	bool is_in_check(bool, Piece*[8][8]);
	bool is_in_check_mate(bool, Piece*[8][8]);
	void apply_fen_notation(const char*, void*[8][8]);
private:
	void *board[8][8];
	bool moves[8][8];
	sf::RectangleShape box;
	sf::Sprite background;
	sf::Event evnt;
	sf::RenderWindow window;
	sf::Texture backTexture;
	Piece *selectedPiece = nullptr;
	bool whites_turn;
	int winner = 0;
	
	//Two kings 0 = player, 1 = foo
	sf::Vector2i king_position[2];
};
