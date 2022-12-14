#pragma once

#include <vector>

class CCell;

using namespace std;
class CShip
{
public:
	CShip();
	CShip(int iDeck);
	~CShip();

	int m_Deck;
	
	vector <CCell*> m_pCells;

	bool IsPlaced();
	void ClearCells();

	bool Alive();

};

