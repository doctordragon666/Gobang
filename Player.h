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
			if (x < board.size() && y < board.size() && x>0 && y > 0 && !board[x][y])
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
	//void init(Chess* chess);
	void go(BOARD& board, int& x, int& y)override {
		int posX = -1, posY = -1;
		while (true)
		{
			getPos(posX, posY);
			if (posX == -1 && posY == -1) break;
			parsePos(x, y, posX, posY);
			if (x < board.size() && y < board.size() && x>0 && y > 0 && !board[x][y])
			{
				board[x][y] = m_flag;
				break;
			}
		}
	}
private:
	//Chess* chess;
	//vector<vector<int>> scoreMap;

private:
	//void calculateScore();
	//ChessPos think();
};
//#include "AI.h"
//#include <time.h>
//
//void AI::go()
//{
//	ChessPos pos = think();
//	Sleep(1000);
//	chess->chessDown(&pos);
//}
//
//void AI::calculateScore()
//{
//	int personNum = 0;
//	int aiNum = 0;//AI有多少个连续棋子
//	int emptyNum = 0;//该方向上空白位的个数
//
//	for (auto i : scoreMap)
//	{
//		for (auto j : i)
//		{
//			j = 0;
//		}
//	}
//	int size = chess->getGradeSize();
//	for (int row = 0; row < size; row++)
//	{
//		for (int col = 0; col < size; col++)
//		{
//			if (chess->getChessData(row, col)) continue;
//
//			for (int y = -1; y <= 0; y++)
//			{
//				for (int x = -1; x <= 1; x++)
//				{
//					if (y == 0 && x == 0) continue;
//					if (y == 0 && x != 1)continue;
//					personNum = 0;
//					aiNum = 0;
//					emptyNum = 0;
//					//假设黑棋在该位置落子，会构成什么棋形
//					for (int i = 1; i <= 4; i++)
//					{
//						int curRow = row + i * y;
//						int curCol = col + i * x;
//
//						if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 1)
//						{
//							personNum++;
//						}
//						else if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 0)
//						{
//							emptyNum++;
//							break;
//						}
//						else
//						{
//							break;
//						}
//					}
//
//					//反向继续计算
//					for (int i = 1; i <= 4; i++)
//					{
//						int curRow = row - i * y;
//						int curCol = col - i * x;
//
//						if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 1)
//						{
//							personNum++;
//						}
//						else if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 0)
//						{
//							emptyNum++;
//							break;
//						}
//						else
//						{
//							break;
//						}
//					}
//
//					switch (personNum) {
//					case 1:
//						scoreMap[row][col] += 10;
//						break;
//					case 2:
//						scoreMap[row][col] += emptyNum == 1 ? 30 : (emptyNum == 2 ? 40 : 0);
//						break;
//					case 3:
//						scoreMap[row][col] = emptyNum == 1 ? 60 : (emptyNum == 2 ? 5000 : 0);
//						break;
//					case 4:
//						scoreMap[row][col] += 20000;
//						break;
//					default:
//						break;
//					}
//
//					//假设白棋在该位置落子，会构成什么棋形
//					emptyNum = 0;
//					for (int i = 1; i <= 4; i++)
//					{
//						int curRow = row + i * y;
//						int curCol = col + i * x;
//
//						if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 1)
//						{
//							aiNum++;
//						}
//						else if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 0)
//						{
//							emptyNum++;
//							break;
//						}
//						else
//						{
//							break;
//						}
//					}
//					//反向继续计算
//					for (int i = 1; i <= 4; i++)
//					{
//						int curRow = row - i * y;
//						int curCol = col - i * x;
//
//						if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 1)
//						{
//							aiNum++;
//						}
//						else if (chess->checkChess(curRow, curCol)
//							&& chess->getChessData(curRow, curCol) == 0)
//						{
//							emptyNum++;
//							break;
//						}
//						else
//						{
//							break;
//						}
//					}
//
//					switch (aiNum) {
//					case 0:
//						scoreMap[row][col] += 5;
//						break;
//					case 1:
//						scoreMap[row][col] += 10;
//						break;
//					case 2:
//						scoreMap[row][col] += emptyNum == 1 ? 25 : (emptyNum == 2 ? 50 : 0);
//						break;
//					case 3:
//						scoreMap[row][col] += emptyNum == 1 ? 55 : (emptyNum == 2 ? 10000 : 0);
//						break;
//					case 4:
//						scoreMap[row][col] += 30000;
//						break;
//					default:
//						break;
//					}
//				}
//			}
//		}
//	}
//}
//
//ChessPos AI::think()
//{
//	calculateScore();
//
//	vector<ChessPos> maxPoints;
//	maxPoints.clear();
//	int maxScore = 0;
//	int size = scoreMap.size();
//
//	for (int row = 0; row < size; row++)
//	{
//		for (int col = 0; col < size; col++)
//		{
//			if (chess->getChessData(row, col) == 0)
//			{
//				if (scoreMap[row][col] > maxScore)
//				{
//					maxScore = scoreMap[row][col];
//					maxPoints.clear();
//					maxPoints.emplace_back(row, col);
//				}
//				else if (scoreMap[row][col] == maxScore)
//				{
//					maxPoints.emplace_back(row, col);
//				}
//			}//在能下的地方,既不能是黑棋也不能是白棋
//		}
//	}
//
//	srand((unsigned int)time(NULL));
//	int index = rand() % maxPoints.size();
//	return maxPoints[index];
//}