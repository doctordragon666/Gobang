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

	void init();//����ͼƬ��Դ����ʼ����������
	bool clickBoard(int x, int y, ChessPos* pos);//�ж��Ƿ���Ч����������ڲ���pos��
	void chessDown(ChessPos* pos, chess_kind_t kind);//����
	int getGradeSize();//��ȡ���̴�С

	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//������̽���

	void putimagePNG(int x, int y, IMAGE* picture);//�Զ�����ͼ�ӿ�
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;
	int margin_x;
	int margin_y;

	float chessSize;//���Ӵ�С

	//�洢�������ӷֲ�����
	vector<vector<int>> chessMap;

	//��ʾ˭����
	bool playerFlag;//true������

	void updateGameMap(ChessPos* pos);

	bool checkWin();//���ʤ������

	ChessPos lastPos;//������ӵ��λ��
};

