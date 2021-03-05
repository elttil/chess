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
	return 0;
}
