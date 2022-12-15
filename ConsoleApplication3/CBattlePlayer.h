#pragma once
#include "CAquatory.h"
#include "CShip.h"
#include <vector>

#include "winsock2.h" 

class CBattlePlayer
{
public:
	CBattlePlayer();
	~CBattlePlayer();

	CAquatory m_Aqua;
	vector <CShip*> m_Ships;

	SOCKET m_sock;
	bool PrepareShips();
	bool ShipsAreReady();
	bool DoMove();

	bool Try2PlaceShip(string ship);
	bool Try2openfile(string flink);
	void Message(string str);


	string recieve();
	string placerecieve();
	string fileplace(string flink);//доработать
	

	CBattlePlayer *m_pAnotherPlayer;

	bool IsAlive();
};

