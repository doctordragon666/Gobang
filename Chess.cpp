//#include "Chess.h"
//#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")
//#include <conio.h>
//#include <tgmath.h>
//
//Chess::Chess(int gradeSize, int marginX, int marginY, double chessSize)
//{
//	this->gradeSize = gradeSize;
//	this->margin_x = marginX;
//	this->margin_y = marginY;
//	this->chessSize = chessSize;
//	playerFlag = chess_kind_t::CHESS_BLACK;
//
//	for (int i = 0; i < gradeSize; i++)
//	{
//		vector<int> row;
//		for (int j = 0; j < gradeSize; j++)
//		{
//			row.push_back(0);
//		}
//		chessMap.push_back(row);
//	}
//}
//
//void Chess::init()
//{
//	initgraph(897, 895);//按照图片大小设置
//	loadimage(0, L"res/棋盘2.jpg");
//	mciSendString(L"play res/start.wav", 0, 0, 0);
//
//
//	//棋盘清零
//	for (int i = 0; i < gradeSize; i++)
//	{
//		vector<int> row;
//		for (int j = 0; j < gradeSize; j++)
//		{
//			row.push_back(0);
//		}
//		chessMap.push_back(row);
//	}
//
//	playerFlag = chess_kind_t::CHESS_BLACK;
//}//加载图片资源，初始化棋盘数据
//
//bool Chess::clickBoard(int x, int y, ChessPos* pos)
//{
//	int col = (x - margin_x) / chessSize;
//	int row = (y - margin_y) / chessSize;
//	int leftTopPosX = margin_x + chessSize * col;
//	int leftTopPosY = margin_x + chessSize * row;
//
//	int offset = chessSize * 0.4;
//	bool ret = false;
//
//	int len;
//	do
//	{
//		//左上角
//		len = hypot(x - leftTopPosX, y - leftTopPosY);
//		if (len < offset)
//		{
//			pos->row = row;
//			pos->col = col;
//			if (!chessMap[pos->row][pos->col])
//			{
//				ret = true;
//				break;
//			}
//		}
//
//		//右上角
//		len = (int)hypot(x - leftTopPosX - chessSize, y - leftTopPosY);
//		if (len < offset)
//		{
//			pos->row = row;
//			pos->col = col + 1;
//			if (!chessMap[pos->row][pos->col])
//			{
//				ret = true;
//				break;
//			}
//		}
//
//		//左下角
//		len = (int)hypot(x - leftTopPosX, y - leftTopPosY - chessSize);
//		if (len < offset)
//		{
//			pos->row = row + 1;
//			pos->col = col;
//			if (!chessMap[pos->row][pos->col])
//			{
//				ret = true;
//				break;
//			}
//		}
//
//		//右下角
//		len = (int)hypot(x - leftTopPosX - chessSize, y - leftTopPosY - chessSize);
//		if (len < offset)
//		{
//			pos->row = row + 1;
//			pos->col = col + 1;
//			if (!chessMap[pos->row][pos->col])
//			{
//				ret = true;
//				break;
//			}
//		}
//	} while (0);
//	return ret;
//}//判定是否有效点击，保存在参数pos中
//
//void Chess::chessDown(ChessPos* pos)
//{
//	mciSendString(L"play res/down7.WAV", 0, 0, 0);
//	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
//	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
//
//	if (playerFlag == chess_kind_t::CHESS_WHITE)
//	{
//		putimagePNG(x, y, &chessWhiteImg);
//	}
//	else if (playerFlag == chess_kind_t::CHESS_BLACK)
//	{
//		putimagePNG(x, y, &chessBlackImg);
//	}
//	else
//	{
//	}
//
//	updateGameMap(pos);
//}//落子
//
//
//
//void Chess::updateGameMap(ChessPos* pos)
//{
//	lastPos = *pos;
//	chessMap[pos->row][pos->col] = (int)playerFlag;
//	playerFlag = (playerFlag == chess_kind_t::CHESS_WHITE) ? chess_kind_t::CHESS_BLACK : chess_kind_t::CHESS_WHITE;
//}
//
//bool Chess::checkWin()
//{
//	int row = lastPos.row;
//	int col = lastPos.col;
//
//	//落子点的水平方向
//	for (int i = 0; i < 5; i++)
//	{
//		if (col - i >= 0 &&
//			col - i + 4 < gradeSize)
//		{
//			vector<int> line(chessMap[row].begin() + col - i, chessMap[row].begin() + col - i + 5);
//			auto iter = adjacent_find(line.begin(), line.end(), std::not_equal_to<int>());
//			if (iter == line.end())return true;
//		}
//	}
//
//	//垂直方向
//	for (int i = 0; i < 5; i++)
//	{
//		if (row - i >= 0 &&
//			row - i + 4 < gradeSize &&
//			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
//			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
//			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
//			chessMap[row - i][col] == chessMap[row - i + 4][col])
//		{
//			return true;
//		}
//	}
//
//	//"/"方向
//	for (int i = 0; i < 5; i++)
//	{
//		if (row + i - 4 >= 0 && row + i < gradeSize &&
//			col - i >= 0 && col - i + 4 < gradeSize &&
//			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
//			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
//			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
//			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
//		{
//			return true;
//		}
//	}
//
//	//”\“方向
//	for (int i = 0; i < 5; i++)
//	{
//		if (row - i >= 0 && row - i + 4 < gradeSize &&
//			col - i >= 0 && col - i + 4 < gradeSize &&
//			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
//			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
//			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
//			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//int Chess::getGradeSize()
//{
//	return this->gradeSize;
//}//获取棋盘大小
//
//int Chess::getChessData(ChessPos* pos)
//{
//	return chessMap[pos->row][pos->col];
//}
//
//int Chess::getChessData(int row, int col)
//{
//	return chessMap[row][col];
//}
//
//bool Chess::checkOver()
//{
//	if (checkWin())
//	{
//		Sleep(1500);
//		if (playerFlag == chess_kind_t::CHESS_WHITE)
//		{
//			mciSendString(L"play res/不错.mp3", 0, 0, 0);
//			loadimage(0, L"res/胜利.jpg");
//		}
//		else
//		{
//			mciSendString(L"play res/失败.mp3", 0, 0, 0);
//			loadimage(0, L"res/失败.jpg");
//		}
//
//		//_getch();
//		return true;
//	}
//
//	return false;
//}
//bool Chess::checkChess(ChessPos* pos)
//{
//	return pos->row >= 0 && pos->row < gradeSize
//		&& pos->col >= 0 && pos->col < gradeSize;
//}
//
//bool Chess::checkChess(int row, int col)
//{
//	return row >= 0 && row < gradeSize
//		&& col >= 0 && col < gradeSize;
//}
////检查棋盘结束