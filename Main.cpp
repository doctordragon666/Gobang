#include <stdio.h>
#include "ChessGame.h"

int main()
{
	Chess chess(13,44,43,67.3);
	Man man;
	AI ai;
	ChessGame* game = new ChessGame(&man, &ai, &chess);
	game->play();
	return 0;
}