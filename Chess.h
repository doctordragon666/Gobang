//#pragma once
//#include <graphics.h>
//#include <vector>
//#include <algorithm>
//#include <numeric>
//#include <functional>
//using namespace std;

//class Chess
//{
//public:
//	Chess(int gradeSize, int marginX, int marginY, double chessSize);
//
//	void init();//加载图片资源，初始化棋盘数据
//	bool clickBoard(int x, int y, ChessPos* pos);//判定是否有效点击，保存在参数pos中
//	//跟换状态
//	void chessDown(ChessPos* pos);//落子
//	int getGradeSize();//获取棋盘大小
//
//
//	bool checkOver();//检查棋盘结束
//
//	//检查这个位置是否在棋盘上
//	bool checkChess(ChessPos* pos);
//	bool checkChess(int row, int col);
//
//
//	//重置棋盘，并将棋盘的结果保存
//	void reset();
//private:
//	IMAGE chessBlackImg;
//	IMAGE chessWhiteImg;
//
//	int gradeSize;//棋盘大小
//	int margin_x;
//	int margin_y;
//
//	double chessSize;//棋子大小
//
//	//存储棋盘棋子分布数据
//	vector<vector<int>> chessMap;
//
//	//表示谁下棋
//	chess_kind_t playerFlag;//true黑子走
//
//	void updateGameMap(ChessPos* pos);
//
//	bool checkWin();//检查胜利条件
//
//	ChessPos lastPos;//最近落子点的位置
//};
