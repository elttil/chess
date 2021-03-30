#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include "piece.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef std::chrono::high_resolution_clock Clock;

class Game
{
public:
	Game(bool);
	~Game();
	void update_game();
	void update_window();
	void update_pieces();
	bool is_open();
	bool is_in_check(bool, Piece*[8][8]);
	bool is_in_check_mate(bool, Piece*[8][8]);
	void apply_fen_notation(const char*, void*[8][8]);
	void move_selectedpiece(sf::Vector2i);
private:
	void *board[8][8];
	bool moves[8][8];
	sf::RectangleShape box;
	sf::Sprite background;
	sf::Event evnt;
	sf::RenderWindow window;
	sf::Texture backTexture;
	Piece *selectedPiece;
	bool whites_turn;
	int winner = 0;
	int sock;
	std::chrono::_V2::system_clock::time_point update_clock;
	
	//Two kings 0 = player, 1 = foo
	sf::Vector2i king_position[2];
};
