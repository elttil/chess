#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
public:
	Piece();
	virtual ~Piece() { };
	char get_type();
	void draw(sf::RenderWindow&);
	void setPosition(float,float);
	bool contains(sf::Vector2f);
	bool is_white();
	bool can_move(int, int, Piece*[8][8], bool* = nullptr);
	virtual void get_legal_moves(bool[8][8], Piece*[8][8], unsigned short, unsigned short) = 0;
protected:
	char type;
	bool isWhite;
	sf::Sprite mainObj;
	sf::Texture texture;
};
