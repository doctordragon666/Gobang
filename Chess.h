#pragma once
#include <graphics.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

struct ChessPos
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

enum class chess_kind_t {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1,
	CHESS_NONE = 0
};

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, double chessSize);

	void init();//����ͼƬ��Դ����ʼ����������
	bool clickBoard(int x, int y, ChessPos* pos);//�ж��Ƿ���Ч����������ڲ���pos��
	//����״̬
	void chessDown(ChessPos* pos);//����
	int getGradeSize();//��ȡ���̴�С

	//��ȡ��������
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	bool checkOver();//������̽���

	//������λ���Ƿ���������
	bool checkChess(ChessPos* pos);
	bool checkChess(int row, int col);

	void putimagePNG(int x, int y, IMAGE* picture);//�Զ�����ͼ�ӿ�

	//�������̣��������̵Ľ������
	void reset();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;//���̴�С
	int margin_x;
	int margin_y;

	double chessSize;//���Ӵ�С

	//�洢�������ӷֲ�����
	vector<vector<int>> chessMap;

	//��ʾ˭����
	chess_kind_t playerFlag;//true������

	void updateGameMap(ChessPos* pos);

	bool checkWin();//���ʤ������

	ChessPos lastPos;//������ӵ��λ��
};
