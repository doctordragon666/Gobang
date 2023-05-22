#include <stdio.h>
#include "ChessGame.h"
#include "AI.h"
#include "Man.h"
#include <memory>

const int gradeSize = 13;
const int marginX = 44;
const int marginY = 43;
const double chessSize = 67.3;

int main()
{
	Chess chess(gradeSize, marginX, marginY, chessSize);
	Man man;
	AI ai;

	shared_ptr<ChessGame> game(new ChessGame(&man, &ai, &chess));
	game->play();

	return 0;
}