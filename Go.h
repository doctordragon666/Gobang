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
		if (lastposX == -1 && lastposY == -1 && !checkPos(lastposX, lastposY)) return;
		if (debug)printf("the %d choice: x=%d,y=%d,type=%d\n", play_times, lastposX, lastposY, board[lastposX][lastposY]);
		play_times++;
	}
	bool checkrow()
	{
		int start = -1;
		int type = board[lastposX][lastposY];
		for (int left = lastposX - 4; left <= lastposX + 4; left++)
		{
			if (!checkPos(left, lastposY))continue;
			if (board[left][lastposY] == type)
			{
				if (start == -1) start = left;
				else if (left - start == 4) return true;
			}
			else
			{
				start = -1;
			}
		}
		return false;
	}
	bool checkcol()
	{
		int start = -1;
		int type = board[lastposX][lastposY];
		for (int left = lastposY - 4; left <= lastposY + 4; left++)
		{
			if (!checkPos(lastposX, left))continue;
			if (board[lastposX][left] == type)
			{
				if (start == -1) start = left;
				else if (left - start == 4) return true;
			}
			else
			{
				start = -1;
			}
		}
		return false;
	}
	bool checkslash()
	{
		int start = -1;
		int rightX = lastposX + 4, rightY = lastposY + 4;
		int type = board[lastposX][lastposY];

		for (int leftX = lastposX - 4, leftY = lastposY - 4; leftX <= rightX && leftY <= rightY; leftX++, rightY--)
		{
			if (!checkPos(leftX, rightY))continue;
			if (board[leftX][rightY] == type)
			{
				if (start == -1) start = leftX;
				else if (leftX - start == 4) return true;
			}
			else
			{
				start = -1;
			}
		}
		return false;
	}
	bool checkescape()
	{
		int start = -1;
		int rightX = lastposX + 4, rightY = lastposY + 4;
		int type = board[lastposX][lastposY];

		for (int leftX = lastposX - 4, leftY = lastposY - 4; leftX <= rightX && leftY <= rightY; leftX++, leftY++)
		{
			if (!checkPos(leftX, leftY))continue;
			if (board[leftX][leftY] == type)
			{
				if (start == -1) start = leftX;
				if (leftX - start == 4) return true;
			}
			else
			{
				start = -1;
			}
		}
		return false;
	}
	bool isover()
	{
		return checkrow() || checkcol() || checkescape() || checkslash();
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
		play_times = 1;
	}
	BOARD get_board() const
	{
		return board;
	}

	// 上次下棋的位置,用于特别标注最后一个棋子
	int lastposX = 0;
	int lastposY = 0;
private:
	Player* player1;
	Player* player2;
	BOARD board = { {0} };
	bool full = false;
	int play_times = 1; // 下了多少手
};
