#include "global.h"
#include "Go.h"
#include "Player.h"
#include <array>

IMAGE whiteChessImg;
IMAGE blackChessImg;
IMAGE boardImg;
int chessSize = 0;

static void initResource()
{
	loadimage(&whiteChessImg, L"res/white.png");
	loadimage(&blackChessImg, L"res/black.png");
	loadimage(&boardImg, L"res/board.jpg");
	chessSize = whiteChessImg.getwidth();
}

static void printBoard(BOARD board)
{
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			if (board[i][j] == 0)
			{
				continue;
			}
			int x = marginX + chessSize * j - 0.5 * chessSize + margin * j;
			int y = marginY + chessSize * i - 0.5 * chessSize + margin * i;
			if (board[i][j] == 1)
			{
				putimagePNG(x, y, &whiteChessImg);
			}
			else if (board[i][j] == 2)
			{
				putimagePNG(x, y, &blackChessImg);
			}
		}
	}
}

static void printVictory(int playerorder) {
	if (playerorder == 1)
	{
	}
	else if (playerorder == 2)
	{
	}
	else
	{
		//没有胜利者
	}
}

int main()
{
	// 加载资源文件
	initResource();
	// 游戏开始
	initgraph(boardImg.getwidth(), boardImg.getheight(), EX_NOCLOSE);
	BeginBatchDraw();
	Go go;
	Man man;
	AI ai;
	go.setplay1(&man);
	go.setplay2(&ai);

	while (!exist)
	{
		putimage(0, 0, &boardImg);
		printBoard(go.get_board());
		FlushBatchDraw();

		if (go.isover()) {
			printVictory(go.getvictory());

			cleardevice();
			go.clear();
		}
		go.move();
	}
	EndBatchDraw();
	closegraph();

	return 0;
}