#pragma once
#include "Man.h"
#include "Chess.h"
#include "AI.h"

class ChessGame
{
public:
	ChessGame(Man* man, AI* ai, Chess* chess) :m_man(man), m_ai(ai), m_chess(chess) 
	{
		man->init(chess);
		ai->init(chess);
	}
	void play();//��ʼ��Ϸ
private:
	Man* m_man;
	AI* m_ai;
	Chess* m_chess;
};

