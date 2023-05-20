#pragma once
#include "Chess.h"
#include "Player.h"

class ChessGame
{
public:
	ChessGame(Player* man, Player* ai, Chess* chess) :m_player1(man), m_player2(ai), m_chess(chess)
	{
		man->init(chess);
		ai->init(chess);
	}
	void play();//¿ªÊ¼ÓÎÏ·
private:
	Player* m_player1;
	Player* m_player2;
	Chess* m_chess;
};
