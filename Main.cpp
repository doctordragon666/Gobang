#include "global.h"
#include "Go.h"
#include "Player.h"

IMAGE whiteChessImg;
IMAGE blackChessImg;
IMAGE boardImg;

ExMessage ex;
//IMAGE* backgroundImg;
//IMAGE* winImg;
//IMAGE* loseImg;

static void initResource()
{
	loadimage(&whiteChessImg, L"scr/white.jpg");
	loadimage(&blackChessImg, L"scr/black.jpg");
	//loadimage(&winImg, L"scr/win.jpg");
	//loadimage(&loseImg, L"scr/lose.jpg");
	loadimage(&boardImg, L"scr/board.jpg");
}

static void printBoard(array<array<int, gradeSize >, gradeSize> board)
{
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			if (board[i][j] == 1)
			{
				putimage(50 + i * 50, 50 + j * 50, &whiteChessImg);
			}
			else if (board[i][j] == 2)
			{
				putimage(50 + i * 50, 50 + j * 50, &blackChessImg);
			}
		}
	}
}

int main()
{
	// 加载资源文件
	initResource();

	// 游戏开始
	initgraph(boardImg.getwidth(), boardImg.getheight(), EX_NOCLOSE);
	BeginBatchDraw();

	while (true)
	{
		putimage(0, 0, &boardImg);

		FlushBatchDraw();

		if (peekmessage(&ex, EX_MOUSE | EX_KEY))
		{
			if (ex.vkcode == 'Q')
			{
				break;//结束游戏
			}
		}
	}

	return 0;
}