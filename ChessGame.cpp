#include "ChessGame.h"

void ChessGame::play()
{
	m_chess->init();

	while (true)
	{
		//����������
		m_man->go();
		if (m_chess->checkOver())
		{
			m_chess->init();
			continue;
		}
		//AI��
		m_ai->go();
		if (m_chess->checkOver())
		{
			m_chess->init();
			continue;
		}
	}
}
