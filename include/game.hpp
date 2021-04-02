#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "piece.hpp"

class Game
{
public:
	Game(bool);
	~Game();
	void update_game();
	void update_window();
	void update_pieces();
	bool is_open();
	bool is_in_check(bool, std::vector<std::vector<Piece*>>);
	bool is_in_check_mate(bool, std::vector<std::vector<Piece*>>);
	void apply_fen_notation(const char*, std::vector<std::vector<Piece*>>&);
	void move_selectedpiece(sf::Vector2i);
private:
	std::vector<std::vector<Piece*>> board;
	std::vector<std::vector<bool>> moves;
	sf::RectangleShape box;
	sf::Sprite background;
	sf::Event evnt;
	sf::RenderWindow window;
	sf::Texture backTexture;
	Piece *selectedPiece;
	bool whites_turn;
	int winner = 0;
	int sock;
	
	//Two kings 0 = player, 1 = foo
	sf::Vector2i king_position[2];
};
