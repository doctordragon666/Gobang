#include "Chess.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <conio.h>
#include <tgmath.h>

Chess::Chess(int gradeSize, int marginX, int marginY, double chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = chess_kind_t::CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++)
	{
		vector<int> row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	//initgraph(897, 895, EW_SHOWCONSOLE);//����ͼƬ��С����
	initgraph(897, 895);//����ͼƬ��С����
	loadimage(0, L"res/����2.jpg");
	mciSendString(L"play res/start.wav", 0, 0, 0);

	//���غڰ���
	loadimage(&chessBlackImg, L"res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, L"res/white.png", chessSize, chessSize, true);

	//��������
	for (int i = 0; i < gradeSize; i++)
	{
		vector<int> row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		chessMap.push_back(row);
	}

	playerFlag = chess_kind_t::CHESS_BLACK;
}//����ͼƬ��Դ����ʼ����������

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_x + chessSize * row;

	int offset = chessSize * 0.4;
	bool ret = false;

	int len;
	do
	{
		//���Ͻ�
		len = hypot(x - leftTopPosX, y - leftTopPosY);
		if (len < offset)
		{
			pos->row = row;
			pos->col = col;
			if (!chessMap[pos->row][pos->col])
			{
				ret = true;
				break;
			}
		}

		//���Ͻ�
		len = (int)hypot(x - leftTopPosX - chessSize, y - leftTopPosY);
		if (len < offset)
		{
			pos->row = row;
			pos->col = col + 1;
			if (!chessMap[pos->row][pos->col])
			{
				ret = true;
				break;
			}
		}

		//���½�
		len = (int)hypot(x - leftTopPosX, y - leftTopPosY - chessSize);
		if (len < offset)
		{
			pos->row = row + 1;
			pos->col = col;
			if (!chessMap[pos->row][pos->col])
			{
				ret = true;
				break;
			}
		}

		//���½�
		len = (int)hypot(x - leftTopPosX - chessSize, y - leftTopPosY - chessSize);
		if (len < offset)
		{
			pos->row = row + 1;
			pos->col = col + 1;
			if (!chessMap[pos->row][pos->col])
			{
				ret = true;
				break;
			}
		}
	} while (0);
	return ret;
}//�ж��Ƿ���Ч����������ڲ���pos��

void Chess::chessDown(ChessPos* pos)
{
	mciSendString(L"play res/down7.WAV", 0, 0, 0);
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

	if (playerFlag == chess_kind_t::CHESS_WHITE)
	{
		putimagePNG(x, y, &chessWhiteImg);
	}
	else if (playerFlag == chess_kind_t::CHESS_BLACK)
	{
		putimagePNG(x, y, &chessBlackImg);
	}
	else
	{
	}

	updateGameMap(pos);
}//����

void Chess::putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Chess::reset()
{
	FILE* file;
	fopen_s(&file, "result.txt", "w");

	if (file == nullptr)
	{
		return;
	}

	for (auto line : chessMap)
	{
		for (auto cell : line)
		{
			fwrite(&cell, sizeof(int), 1, file);
		}
	}

	fclose(file);
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = (int)playerFlag;
	playerFlag = (playerFlag == chess_kind_t::CHESS_WHITE) ? chess_kind_t::CHESS_BLACK : chess_kind_t::CHESS_WHITE;
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;

	//���ӵ��ˮƽ����
	for (int i = 0; i < 5; i++)
	{
		if (col - i >= 0 &&
			col - i + 4 < gradeSize)
		{
			vector<int> line(chessMap[row].begin() + col - i, chessMap[row].begin() + col - i + 5);
			auto iter = adjacent_find(line.begin(), line.end(), std::not_equal_to<int>());
			if (iter == line.end())return true;
		}
	}

	//��ֱ����
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
		{
			return true;
		}
	}

	//"/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i - 4 >= 0 && row + i < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
		{
			return true;
		}
	}

	//��\������
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
		{
			return true;
		}
	}

	return false;
}

int Chess::getGradeSize()
{
	return this->gradeSize;
}//��ȡ���̴�С

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin())
	{
		Sleep(1500);
		if (playerFlag == chess_kind_t::CHESS_WHITE)
		{
			mciSendString(L"play res/����.mp3", 0, 0, 0);
			loadimage(0, L"res/ʤ��.jpg");
		}
		else
		{
			mciSendString(L"play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, L"res/ʧ��.jpg");
		}

		//_getch();
		return true;
	}

	return false;
}
bool Chess::checkChess(ChessPos* pos)
{
	return pos->row >= 0 && pos->row < gradeSize
		&& pos->col >= 0 && pos->col < gradeSize;
}

bool Chess::checkChess(int row, int col)
{
	return row >= 0 && row < gradeSize
		&& col >= 0 && col < gradeSize;
}
//������̽���