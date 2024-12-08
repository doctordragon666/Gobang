#include "Man.h"

void Man::init(Chess& chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (true)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess.clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}
	}

	chess.chessDown(&pos);
}
