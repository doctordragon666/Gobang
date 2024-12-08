#pragma once
#include "Chess.h"
class Player
{
public:
	virtual void init(Chess& chess) {};
	virtual void go() {};
};
