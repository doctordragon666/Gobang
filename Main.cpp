#include "global.h"
#include "Go.h"
#include "Player.h"
#include <array>

IMAGE whiteChessImg;
IMAGE blackChessImg;
IMAGE boardImg;
IMAGE victoryImg;

static void initResource()
{
	loadimage(&whiteChessImg, L"res/white.png");
	loadimage(&blackChessImg, L"res/black.png");
	loadimage(&boardImg, L"res/board.jpg");
	loadimage(&victoryImg, L"res/v.jpg", boardImg.getwidth(), boardImg.getheight(), true);
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
		putimage(0, 0, &victoryImg);
	}
	else if (playerorder == 2)
	{
		putimage(0, 0, &victoryImg);
	}
	else
	{
		//没有胜利者,棋盘已经满了
		putimage(0, 0, &victoryImg);
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
	//Man man;
	Man man1, man2;
	//AI ai;
	//go.setplay1(&man);
	//go.setplay2(&ai);

	// 设置为双人对战，注释下面两行解开上面的注释，开启人机对战。
	go.setplay1(&man1);
	go.setplay2(&man2);

	while (!exist)
	{
		putimage(0, 0, &boardImg);
		printBoard(go.get_board());
		FlushBatchDraw();
		go.move();

		if (go.isover()) {
			if (debug)
			{
				FILE* file;
				int r = fopen_s(&file, "result.txt", "w");
				for (auto i : go.get_board())
				{
					for (auto j : i)
					{
						fprintf(file, "%d ", j);
					}
					fprintf(file, "\n");
				}
				fclose(file);
			}
			printBoard(go.get_board());
			FlushBatchDraw();
			Sleep(1000);
			printVictory(go.getvictory());
			FlushBatchDraw();
			Sleep(3000);

			cleardevice();
			go.clear();
		}
	}

	go.clear();
	EndBatchDraw();
	closegraph();

	return 0;
}