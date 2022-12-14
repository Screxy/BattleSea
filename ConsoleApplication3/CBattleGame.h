#pragma once
#include "CBattlePlayer.h"

#define MOVE1 1
#define MOVE2 -1



class CBattleGame
{
public:
	CBattleGame();
	~CBattleGame();

	int m_iCurrentMove;

	bool StartTCP(int port);

	void DoPlay();

	CBattlePlayer m_Player1, m_Player2;
};

