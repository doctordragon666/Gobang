#include "global.h"
#include "Go.h"
#include "Player.h"
#include <array>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

IMAGE whiteChessImg;
IMAGE blackChessImg;
IMAGE boardImg;
IMAGE victoryImg;
IMAGE failureImg;

static void initResource()
{
	loadimage(&whiteChessImg, L"res/white.png");
	loadimage(&blackChessImg, L"res/black.png");
	loadimage(&boardImg, L"res/board.jpg");
	loadimage(&victoryImg, L"res/v.jpg", boardImg.getwidth(), boardImg.getheight(), true);
	loadimage(&failureImg, L"res/f.jpg", boardImg.getwidth(), boardImg.getheight(), true);
	chessSize = whiteChessImg.getwidth();
}
void printBoard(BOARD board)
{
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			if (board[i][j] == 0)
			{
				continue;
			}
			int x = static_cast<int>(marginX + chessSize * j - 0.5 * chessSize + margin * j);
			int y = static_cast<int>(marginY + chessSize * i - 0.5 * chessSize + margin * i);
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
		mciSendString(L"play res/胜利.mp3", 0, 0, 0);
		putimage(0, 0, &victoryImg);
	}
	else if (playerorder == 2)
	{
		mciSendString(L"play res/失败.mp3", 0, 0, 0);
		putimage(0, 0, &failureImg);
	}
	else
	{
		//没有胜利者,棋盘已经满了
		putimage(0, 0, &failureImg);
	}
}

int main()
{
	// 加载资源文件
	initResource();
	// 游戏开始
	int flag = debug ? EX_SHOWCONSOLE : EX_NOCLOSE;
	initgraph(boardImg.getwidth(), boardImg.getheight(), flag);

	BeginBatchDraw();
	Go go;
	//Man man;
	Man man1, man2;
	//AI ai, man2;

	AI ai;
	//go.setplay1(&man);
	//go.setplay2(&ai);

	// 设置为双人对战，注释下面两行解开上面的注释，开启人机对战。
	//go.setplay1(&ai);
	go.setplay1(&man1);
	go.setplay2(&man2);

	// 人机调试

	while (!exist)
	{
		putimage(0, 0, &boardImg);
		printBoard(go.get_board());
		FlushBatchDraw();
		go.move();

		if (!exist && go.isover()) {
			exist = true;//暂时停止记录按键消息
			printBoard(go.get_board());
			FlushBatchDraw();
			Sleep(1000);

			printVictory(go.getvictory());
			FlushBatchDraw();
			go.clear();

			Sleep(3000);
			exist = false;
		}
		cleardevice();
	}

	go.clear();
	EndBatchDraw();
	closegraph();

	return 0;
}