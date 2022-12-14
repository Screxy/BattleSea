#include "CAquatory.h"
#include <iostream>

using namespace std;
CAquatory::CAquatory()
{

}
CAquatory::~CAquatory()
{

}
string CAquatory::PrintOwn()
{
	string alf = "ABCDEFGHIJ";
	string str = "  1 2 3 4 5 6 7 8 9 10\n";
	string buf;
	for (int i = 0; i < 10; i++)
	{
		str += alf[i];
		str += " ";
		for (int j = 0; j < 10; j++)
		{
			str += m_Cells[i][j].PrintOwn();
		}
		str += "\n";
	}
	return str;
}
string CAquatory::PrintForeign()
{
	string alf = "ABCDEFGHIJ";
	string str = "  1 2 3 4 5 6 7 8 9 10\n\n";
	string buf;
	for (int i = 0; i < 10; i++)
	{
		str += alf[i];
		str += " ";
		for (int j = 0; j < 10; j++)
		{
			str += m_Cells[i][j].PrintForeign();
		}
		str += "\n";
	}

	return str;
}
bool CAquatory::ParseCell(string cell, int &i, int&j)
{
	char letter;
	int number;
	sscanf_s(cell.c_str(), "%c%i", &letter, 1, &number);

	int num = Letter2Number(letter);
	number--;

	i = num;
	j = number;

	return true;
}
bool CAquatory::Try2PlaceDeck(string cell,CCell **pCell, CShip *sh)
{
	int num, number;
	ParseCell(cell, num, number);
	
	if (num > -1)
	{
		if (TestCell4ShipDeck(num, number, sh))
		{
			*pCell = &m_Cells[num][number];
			return true;
		}
	}

	return false;
}

int CAquatory::Letter2Number(char l)
{
	switch (l)
	{
	case 'a':
	case 'A':
		return 0;
		break;
	case 'b':
	case 'B':
		return 1;
		break;
	case 'c':
	case 'C':
		return 2;
		break;
	case 'd':
	case 'D':
		return 3;
		break;
	case 'e':
	case 'E':
		return 4;
		break;
	case 'f':
	case 'F':
		return 5;
		break;
	case 'g':
	case 'G':
		return 6;
		break;
	case 'h':
	case 'H':
		return 7;
		break;
	case 'i':
	case 'I':
		return 8;
		break;
	case 'j':
	case 'J':
		return 9;
		break;

	}

	return -1;

}
bool CAquatory::TestCell4ShipDeck(int i, int j, CShip *s)
{
	if (m_Cells[i][j].m_pShip)
		return false;
//1 +=
	int r=i+1, c=j;
	if (r > -1 && r < 10 && c>-1 &&c<10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
			
	}
  //2 -= 
	r = i - 1, c = j;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
	}
	//3 --
	r = i - 1, c = j-1;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
	}
	//4 -+
	r = i - 1, c = j+1;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
	}
	//5 ++
	r = i + 1, c = j+1;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
	} 
	//6=+
	r = i , c = j+1;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
	}
	//7=-
	r = i, c = j-1;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			
			if (m_Cells[r][c].m_pShip != s)
				return false;
		}
	}
	//8+-
	r = i + 1, c = j-1;
	if (r > -1 && r < 10 && c>-1 && c < 10)
	{
		if (m_Cells[r][c].m_pShip)
		{
			
			if (m_Cells[r][c].m_pShip != s)
			return false;
		}
	}


	return true;
}

bool CAquatory::TestShip(string cell, CShip **ship)
{
	int i, j;
	ParseCell(cell, i, j);
	
	m_Cells[i][j].m_bBeated = true;

	*ship = m_Cells[i][j].m_pShip;
	

	return  *ship;
}