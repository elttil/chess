#include <iostream>
#include "game.hpp"

int main(int argc, char **argv)
{
	Game chess(argc >= 2);
	while(chess.is_open())
	{
		chess.update_game();
		chess.update_window();
	}
	return 0;
}
