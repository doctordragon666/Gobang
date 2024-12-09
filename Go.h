#pragma once
#include "global.h"
#include "Player.h"
class Go
{
public:
	void setplay1(Player* player) {
		player1 = player;
		player1->setflag(1);
	}
	void setplay2(Player* player) {
		player2 = player;
		player2->setflag(2);
	}

	void move() {
		if (play_times % 2) player1->go(board);
		else player2->go(board);
		play_times++;
	}

	bool isover() {
		bool full = true;
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j] == 0)
				{
					full = false;
					continue;
				}
				else
				{
				}
			}
		}
		return full;
	}
	int getvictory() const
	{
		return play_times % 2 ? 2 : 1;
	}
	void clear() {
		std::for_each(board.begin(), board.end(), [](auto& line) { std::fill(line.begin(), line.end(), 0); });
	}
	BOARD get_board() const {
		return board;
	}

private:
	Player* player1;
	Player* player2;
	BOARD board = { {0} };
	int play_times = 1;//下了多少手
};
