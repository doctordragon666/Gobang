#pragma once
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <array>
#include <stdlib.h>
#include <vector>
#include <algorithm>

const int gradeSize = 13;
const int marginX = 33;
const int marginY = 30;
const int margin = 2;
int chessSize = 0;
const int debug = 0;
bool exist = false;
ExMessage ex;//游戏循环消息

typedef std::array < std::array<int, gradeSize>, gradeSize> BOARD;

// 修正后的putimagePNG函数，用于实现透明贴图功能，增强了边界处理、可读性等方面
void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 获取绘图设备的显存指针、图片宽度、高度以及绘图区宽度、高度，使用更具描述性的变量名
	DWORD* destinationBuffer = GetImageBuffer();    // 目标绘图区的显存指针
	int pictureWidth = picture->getwidth();        // 获取picture的宽度，EASYX自带
	int pictureHeight = picture->getheight();      // 获取picture的高度，EASYX自带
	int graphWidth = getwidth();                   // 获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();                 // 获取绘图区的高度，EASYX自带

	// 对传入坐标和图片尺寸进行有效性验证，避免无效的绘制操作
	if (x < 0 || y < 0 || x + pictureWidth > graphWidth || y + pictureHeight > graphHeight)
	{
		outtextxy(0, 0, L"error");
		return;
	}

	DWORD* sourceBuffer = GetImageBuffer(picture); // 获取picture的显存指针

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < pictureHeight; iy++)
	{
		for (int ix = 0; ix < pictureWidth; ix++)
		{
			int sourceIndex = ix + iy * pictureWidth; // 在源图片显存里像素的角标
			int alpha = ((sourceBuffer[sourceIndex] & 0xff000000) >> 24); // 0xAArrggbb;AA是透明度
			int sourceRed = ((sourceBuffer[sourceIndex] & 0xff0000) >> 16); // 获取RGB里的R
			int sourceGreen = ((sourceBuffer[sourceIndex] & 0xff00) >> 8);   // G
			int sourceBlue = sourceBuffer[sourceIndex] & 0xff;              // B

			int destinationX = ix + x;
			int destinationY = iy + y;
			int destinationIndex = destinationX + destinationY * graphWidth; // 在目标绘图区显存里像素的角标

			// 验证目标绘图区的坐标是否在有效范围内，避免越界访问显存
			if (destinationX >= 0 && destinationX < graphWidth && destinationY >= 0 && destinationY < graphHeight)
			{
				int destinationRed = ((destinationBuffer[destinationIndex] & 0xff0000) >> 16);
				int destinationGreen = ((destinationBuffer[destinationIndex] & 0xff00) >> 8);
				int destinationBlue = destinationBuffer[destinationIndex] & 0xff;

				// Cp = \alpha_p * FP + (1-\alpha_p)*BP
				// \alpha_p = alpha/255, FP = sourceRed, BP = destinationRed
				// \alpha_p = alpha/255, FP = sourceGreen, BP = destinationGreen
				// \alpha_p = alpha/255, FP = sourceBlue, BP = destinationBlue
				int finalRed = (sourceRed * alpha / 255 + destinationRed * (255 - alpha) / 255);
				int finalGreen = (sourceGreen * alpha / 255 + destinationGreen * (255 - alpha) / 255);
				int finalBlue = (sourceBlue * alpha / 255 + destinationBlue * (255 - alpha) / 255);

				// 合成最终颜色并写入目标显存
				destinationBuffer[destinationIndex] = (finalRed << 16) | (finalGreen << 8) | finalBlue;
			}
		}
	}
}

void getPos(int& x, int& y)
{
	if (exist) {
		flushmessage();
		return;
	}
	while (true)
	{
		if (peekmessage(&ex, EX_MOUSE))
		{
			if (ex.lbutton)
			{
				x = ex.x;
				y = ex.y;
				break;
			}
			else if (ex.rbutton)
			{
				exist = true;
				x = -1;
				y = -1;
				break;
			}
		}
	}
}

void parsePos(int& x, int& y, int posX, int posY)
{
	if (posX == -1 && posY == -1) {
		x = -1;
		y = -1;
		return;
	}
	if (posY <= marginY || posX <= marginX)
	{
		x = 0, y = 0;
		return;
	}
	x = int(floor((posY - marginY + chessSize * 0.5) / (chessSize + margin)));
	y = int(floor((posX - marginX + chessSize * 0.5) / (chessSize + margin)));
}

inline bool checkPos(int x, int y)
{
	return x < gradeSize && y < gradeSize && x >= 0 && y >= 0;
}

int cal(BOARD board, int depth, int x, int y, int type)
{
	/*
	* 启发式搜索算法，还没有做好，后面再改。
	*/
	if (depth == 5 || !checkPos(x, y))
	{
		return 0;
	}
	else
	{
		if (board[x][y] == type)
		{
			return cal(board, depth + 1, x + 1, y, type) + 1000;
		}
		else if (board[x][y] == 0)
		{
			return -100 + cal(board, depth + 1, x + 1, y, type);
		}
		else
		{
			return -10000;//如果不是自己的棋子，直接返回负数
		}
	}
}