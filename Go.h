#pragma once
#include "global.h"
#include "Player.h"
class Go
{
public:
	void setplay1(Player* player)
	{
		player1 = player;
		player1->setflag(1);
	}
	void setplay2(Player* player)
	{
		player2 = player;
		player2->setflag(2);
	}

	void move()
	{
		if (play_times % 2)
			player1->go(board, lastposX, lastposY);
		else
			player2->go(board, lastposX, lastposY);
		play_times++;
	}
	bool checkrow()
	{
		int right = min(lastposX + 4, board.size() - 1);
		int sametimes = 1;
		for (int left = max(lastposX - 4, 0); left < right; left++)
		{
			if (board[left][lastposY] != 0 && board[left][lastposY] == board[left + 1][lastposY])
			{
				sametimes++;
			}
		}
		return sametimes == 5;
	}
	bool checkcol()
	{
		//for (int i = 0; i < 15; i++)
		//{
		//	int count = 0;
		//	for (int j = 0; j < 15; j++)
		//	{
		//		if (board[j][i] == play_times % 2)
		//			count++;
		//		else
		//			count = 0;
		//		if (count == 5)

		//			return true;
		//	}
		//}
		return false;
	}
	bool checkslash()
	{
		//for (int i = 0; i < 15; i++)
		//{
		//	int count = 0;
		//	for (int j = 0; j < 15; j++)
		//	{
		//		if (board[i + j][j] == play_times % 2)
		//			count++;
		//		else
		//			count = 0;
		//		if (count == 5)
		//			return true;
		//	}
		//}
		return false;
	}
	bool checkescape()
	{
		//根据lastposX和lastposY判断斜线
		//for (int i = 0; i < 10; i++)
		//{
		//	int count = 0;
		//	for (int j = 0; j < 10; j++)
		//	{
		//		//if (board[i + j][14 - j] == play_times % 2)
		//			//count++;
		//		//else
		//			//count = 0;
		//		if (count == 5)
		//			return true;
		//	}
		//}
		return false;
	}
	bool isover()
	{
		return checkrow() || checkcol() || checkslash() || checkescape();
	}
	int getvictory() const
	{
		if (full) return 3;
		return play_times % 2 ? 2 : 1;
	}
	void clear()
	{
		std::for_each(board.begin(), board.end(), [](auto& line)
			{ std::fill(line.begin(), line.end(), 0); });
	}
	BOARD get_board() const
	{
		return board;
	}

private:
	Player* player1;
	Player* player2;
	BOARD board = { {0} };
	bool full = false;
	int play_times = 1; // 下了多少手
	// 上次下棋的位置
	int lastposX = 0;
	int lastposY = 0;
};
