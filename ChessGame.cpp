#include "ChessGame.h"

void ChessGame::play()
{
	m_chess.init();

	while (true)
	{
		//����������
		m_player1->go();
		if (m_chess.checkOver())
		{
			m_chess.reset();
			m_player1->init(m_chess);
			continue;
		}

		//AI��
		m_player2->go();
		if (m_chess.checkOver())
		{
			m_chess.reset();
			m_player2->init(m_chess);

			continue;
		}
	}
}
