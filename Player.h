#pragma once
#include "Chess.h"
class Player
{
public:
	virtual void init(Chess& chess) {};
	virtual void go() {};
};
#pragma once
#include "Player.h"

class Man : public Player
{
public:
	void init(Chess& chess)override;
	void go() override;
private:
	Chess& chess;
};
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