#include "ChessGame.h"

void ChessGame::play()
{
	m_chess->init();

	while (true)
	{
		//先由棋手走
		m_man->go();
		if (m_chess->checkOver())
		{
			m_chess->init();
			continue;
		}
		//AI走
		m_ai->go();
		if (m_chess->checkOver())
		{
			m_chess->init();
			continue;
		}
	}
}
