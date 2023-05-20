#pragma once
#include "Player.h"

class AI :public Player
{
public:
	void init(Chess* chess);
	void go();
private:
	Chess* chess;
	vector<vector<int>> scoreMap;

private:
	void calculateScore();
	ChessPos think();
};
