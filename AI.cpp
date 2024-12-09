#include "AI.h"
#include <time.h>

void AI::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int> row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);
	chess->chessDown(&pos);
}

void AI::calculateScore()
{
	int personNum = 0;
	int aiNum = 0;//AI�ж��ٸ���������
	int emptyNum = 0;//�÷����Ͽհ�λ�ĸ���

	for (auto i : scoreMap)
	{
		for (auto j : i)
		{
			j = 0;
		}
	}
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col)) continue;

			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1)continue;
					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//��������ڸ�λ�����ӣ��ṹ��ʲô����
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					//�����������
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					switch (personNum) {
					case 1:
						scoreMap[row][col] += 10;
						break;
					case 2:
						scoreMap[row][col] += emptyNum == 1 ? 30 : (emptyNum == 2 ? 40 : 0);
						break;
					case 3:
						scoreMap[row][col] = emptyNum == 1 ? 60 : (emptyNum == 2 ? 5000 : 0);
						break;
					case 4:
						scoreMap[row][col] += 20000;
						break;
					default:
						break;
					}

					//��������ڸ�λ�����ӣ��ṹ��ʲô����
					emptyNum = 0;
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 1)
						{
							aiNum++;
						}
						else if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//�����������
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 1)
						{
							aiNum++;
						}
						else if (chess->checkChess(curRow, curCol)
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					switch (aiNum) {
					case 0:
						scoreMap[row][col] += 5;
						break;
					case 1:
						scoreMap[row][col] += 10;
						break;
					case 2:
						scoreMap[row][col] += emptyNum == 1 ? 25 : (emptyNum == 2 ? 50 : 0);
						break;
					case 3:
						scoreMap[row][col] += emptyNum == 1 ? 55 : (emptyNum == 2 ? 10000 : 0);
						break;
					case 4:
						scoreMap[row][col] += 30000;
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	calculateScore();

	vector<ChessPos> maxPoints;
	maxPoints.clear();
	int maxScore = 0;
	int size = scoreMap.size();

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col) == 0)
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
			}//�����µĵط�,�Ȳ����Ǻ���Ҳ�����ǰ���
		}
	}

	srand((unsigned int)time(NULL));
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}