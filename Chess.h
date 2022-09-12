#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

struct ChessPos
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(c), col(c) {}
};

typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();//加载图片资源，初始化棋盘数据
	bool clickBoard(int x, int y, ChessPos* pos);//判定是否有效点击，保存在参数pos中
	void chessDown(ChessPos* pos, chess_kind_t kind);//落子
	int getGradeSize();//获取棋盘大小

	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//检查棋盘结束

	void putimagePNG(int x, int y, IMAGE* picture);//自定义贴图接口
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;
	int margin_x;
	int margin_y;

	float chessSize;//棋子大小

	//存储棋盘棋子分布数据
	vector<vector<int>> chessMap;

	//表示谁下棋
	bool playerFlag;//true黑子走

	void updateGameMap(ChessPos* pos);

	bool checkWin();//检查胜利条件

	ChessPos lastPos;//最近落子点的位置
};

