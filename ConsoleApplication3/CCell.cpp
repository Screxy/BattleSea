#include "CCell.h"
#include <iostream>

using namespace std;
CCell::CCell()
{
	m_pShip = 0;
	m_bBeated = false;
}
string CCell::PrintOwn()
{
	
	if (m_pShip)
		return "S ";
	else
		return  ". ";

}
string CCell::PrintForeign()
{
	if (m_bBeated)
	{
		if (m_pShip)
			return "! ";
		else
			return "# ";
	}
	else
		if (m_pShip)
			return "* ";
		else
			return  ". ";

}

CCell::~CCell()
{

}