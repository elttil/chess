#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
public:
	Piece();
	virtual ~Piece() { };
	char getType();
//	virtual void move();
	void draw(sf::RenderWindow&);
	void setPosition(float,float);
protected:
	char type;
	bool hasMoved;
	sf::Sprite mainObj;
	sf::Texture texture;
};
