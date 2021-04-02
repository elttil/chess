#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
public:
	Piece();
	virtual ~Piece() { };
	char get_type();
	void set_position(int,int);
	void draw(sf::RenderWindow&);
	bool contains(sf::Vector2f);
	bool is_white();
	bool has_moved();
	void set_has_moved(bool);
	bool can_move(int, int, std::vector<std::vector<Piece*>>, bool* = nullptr);
	virtual void get_legal_moves(std::vector<std::vector<bool>>*, std::vector<std::vector<Piece*>>, unsigned short, unsigned short) = 0;
protected:
	char type;
	bool isWhite;
	bool hasMoved;
	sf::Sprite mainObj;
	sf::Texture texture;
};
