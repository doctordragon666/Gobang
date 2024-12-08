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
