#pragma once
#include "CShip.h"
#include <string>

using namespace std;
class CCell
{
public:
	CCell();
	~CCell();

	CShip *m_pShip;

	bool m_bBeated = false;
	string PrintOwn();
	string PrintForeign();
	
};

