#pragma once
#include "global.h"
class Player
{
public:
	virtual void go(BOARD& board, int& x, int& y) = 0;
	int m_flag;
	void setflag(int flag) {
		m_flag = flag;
	}
};

class Man : public Player
{
public:
	void go(BOARD& board, int& x, int& y)override {
		int posX = -1, posY = -1;
		while (true)
		{
			getPos(posX, posY);
			if (posX == -1 && posY == -1) break;
			parsePos(x, y, posX, posY);
			if (checkPos(x, y) && !board[x][y])
			{
				board[x][y] = m_flag;
				break;
			}
		}
	}
};

class AI :public Player
{
public:
	void go(BOARD& board, int& x, int& y)override {
		std::for_each(scoreMap.begin(), scoreMap.end(), [](auto& line)
			{ std::fill(line.begin(), line.end(), 0); });
		calculateScore(board);
		do {
			think(x, y, board);
		} while (!checkPos(x, y) && board[x][y] != m_flag);
		board[x][y] = m_flag;
	}
	BOARD scoreMap = { {0} };
	void calculateScore(BOARD& board);
	void think(int& x, int& y, BOARD& board);
};

void AI::calculateScore(BOARD& board)
{
	int personNum = 0;
	int aiNum = 0;//AI有多少个连续棋子
	int emptyNum = 0;//该方向上空白位的个数

	for (int row = 0; row < gradeSize; row++)
	{
		for (int col = 0; col < gradeSize; col++)
		{
			if (board[row][col] == m_flag) continue;

			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1)continue;
					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//假设黑棋在该位置落子，会构成什么棋形
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (checkPos(curRow, curCol) && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}

						else if (checkPos(curRow, curCol) && board[curRow][curCol] != m_flag)
						{
							personNum++;
						}
						else
						{
							break;
						}
					}

					//反向继续计算
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (checkPos(curRow, curCol) && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else if (checkPos(curRow, curCol) && board[curRow][curCol] != m_flag)
						{
							personNum++;
						}
						else
						{
							break;
						}
					}

					if (personNum == 1)
					{
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] = 60;
						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] = 5000;
						}
					}
					else if (personNum == 4)
					{
						scoreMap[row][col] += 20000;
					}

					//假设白棋在该位置落子，会构成什么棋形
					emptyNum = 0;
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;
						if (checkPos(curRow, curCol) && board[curRow][curCol] == m_flag)
						{
							aiNum++;
						}
						else if (checkPos(curRow, curCol) && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//反向继续计算
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (checkPos(curRow, curCol) && board[curRow][curCol] == m_flag)
						{
							aiNum++;
						}
						else if (checkPos(curRow, curCol) && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					if (aiNum == 0)
					{
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1)
					{
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum == 4)
					{
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}

void AI::think(int& x, int& y, BOARD& board)
{
	std::vector<std::pair<int, int>> maxPoints;
	int maxScore = -1;
	for (int row = 0; row < gradeSize; row++)
	{
		for (int col = 0; col < gradeSize; col++)
		{
			if (board[row][col] == 0)
			{
				if (scoreMap[row][col] > maxScore)
				{
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.emplace_back(row, col);
				}
				else if (scoreMap[row][col] == maxScore)
				{
					maxPoints.emplace_back(row, col);
				}
			}
		}
	}

	int index = rand() % maxPoints.size();
	x = maxPoints[index].first;
	y = maxPoints[index].second;
}