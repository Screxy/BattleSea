#include "CBattlePlayer.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define TEST
CBattlePlayer::CBattlePlayer()
{
	m_sock = 0;
	m_pAnotherPlayer = NULL;

}
CBattlePlayer::~CBattlePlayer()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		delete m_Ships[i];
	}

	m_Ships.clear();

}
void CBattlePlayer::Message(string str)
{
	str = "\n" + str + "\n";
	send(m_sock, str.c_str(), str.size() + 1, 0);
}

bool CBattlePlayer::PrepareShips()
{
	Message("������������ �������!");
	Message("����������: 4(a1,a2,a3,a4)");
	
	while (!ShipsAreReady())
	{
		if (Try2PlaceShip(recieve()))
		{
			Message("OK");
		}
		else
		{
			Message("������ � ������������ �������!");
		}
		Message(m_Aqua.PrintForeign());
	}
	Message("���� ������� ������!");
	
	return true;

}
bool CBattlePlayer::DoMove()
{
	Message("��� ���!");
	string move = recieve();

	Message(m_Aqua.PrintForeign());
	//Message(m_Aqua.PrintOwn());
	CShip *ship=NULL;
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // ��� �������� ������� � ��������� A-j
	string cifrs = "123456789"; // ��� �������� ������� � ��������� A-j
	cout << move;

	move.erase(remove(move.begin(), move.end(), ' '), move.end()); // �������� ��������
	cout << move;

	cout << move << endl;
	cout << move.length() << "< �����\n";
	if (alf.find(move[0]) == std::string::npos or move.length() == 1 or move.length() >= 4)
	{
		cout << "������ � ����� ��� ����� 1\n";
		Message("������������ ���");
		DoMove();
	}
	if (move.length() == 2)
	{
		if (cifrs.find(move[1]) == std::string::npos)
		{
			cout << "������ � ����� ��� ����� 2\n";

			Message("������������ ���");
			DoMove();
		}
	}
	else if (move.length() == 3)
	{
		if (move[1] == '1' and move[2] == '0')
		{
		}
		else
		{
			cout << "������ � (10) ��� ����� 3\n";

			Message("������������ ���");
			DoMove();
		}
	}
	if (m_pAnotherPlayer->m_Aqua.TestShip(move, &ship))
	{
		Message("���������!");
		
		if (!ship->Alive())
		{
			Message("������� ��������!");

			if (!m_pAnotherPlayer->IsAlive())
			{
				Message("�� ��������(");
				m_pAnotherPlayer->Message("�� ���������(");
				return true;
			}
		}
		
		DoMove();

	}
	else
		Message("����(");
	
	return true;
}

bool CBattlePlayer::ShipsAreReady()
{
#ifndef TEST
	if (m_Ships.size() != 10)
		return false;

#endif
	int n4Deck, n3Deck, n2Deck, n1Deck;

	n4Deck = n3Deck = n2Deck = n1Deck = 0;
	
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if (!m_Ships[i]->IsPlaced())
			return false;
		else {
			switch (m_Ships[i]->m_Deck)
			{
			case 1:
				n1Deck++;
				break;
			case 2:
				n2Deck++;
				break;
			case 3:
				n3Deck++;
				break;
			case 4:
				n4Deck++;
				break;

			}
		}
	}

#ifdef TEST
	if (n4Deck == 1)// ��������
#else
	if (n1Deck == 4 and n2Deck == 3 and n3Deck == 2 and n4Deck == 1)
#endif	
		return true;

	return false;
}
bool CBattlePlayer::Try2PlaceShip(string ship)
{
	int iDeck = 0;
	char buf[50];
	cout << ship << "< ship before delete\n";
	ship.erase(remove(ship.begin(), ship.end(), ' '), ship.end()); // �������� ��������
	cout << ship << "< ship after delete\n";;
	sscanf_s(ship.c_str(), "%i(%[^)]", &iDeck,buf,50);
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // ��� �������� ������� � ��������� A-j
	char cell[4][10];
	if (iDeck < 1 or iDeck > 4)
	{
		cout << "������ � ����������";
		return false;
	}
	switch (iDeck)
	{
	case 1:
		if (alf.find(ship[2]) != std::string::npos and ship[1] == '(' and ship[4] == ')' and ship.length() == 5) // �������� �� ��������, �������, ����������� ���������� � ��������� // ����������
		{
		}
		else
		{
			cout << "1 ������ � ������ ����� (";
			return false;
		}
	case 2:
		if (alf.find(ship[2]) != std::string::npos and alf.find(ship[5]) != std::string::npos and ship[1] == '(' and ship[7] == ')' and ship.length() == 8)
		{
		}
		else
		{
			cout << "2 ������ � ������ ����� (";

			return false;
		}
	case 3:
		if (alf.find(ship[2]) != std::string::npos and alf.find(ship[5]) != std::string::npos and alf.find(ship[8]) != std::string::npos and ship[1] == '(' and ship[10] == ')' and ship.length() == 11)
		{
		}
		else
		{
			cout << "3 ������ � ������ ����� (";
			return false;
		}
	case 4:
		if (alf.find(ship[2]) != std::string::npos and alf.find(ship[5]) != std::string::npos and alf.find(ship[8]) != std::string::npos and alf.find(ship[11]) != std::string::npos and ship[1] == '(' and ship[13] == ')' and ship.length() == 14)
		{
		}
		else
		{
			cout << "4 ������ � ������ ����� (";
			return false;
		}
	}
	if (iDeck == 4)
	{
		sscanf_s(buf, "%[^,],%[^,],%[^,],%[^\n],", cell[0],10,cell[1],10, cell[2], 10, cell[3], 10);
	}
	if (iDeck == 3)
	{
		sscanf_s(buf, "%[^,],%[^,],%[^\n],", cell[0], 10, cell[1], 10, cell[2], 10);
	}
	if (iDeck == 2)
	{
		sscanf_s(buf, "%[^,],%[^\n],", cell[0], 10, cell[1], 10);
	}
	if (iDeck == 1)
	{
		sscanf_s(buf, "%[^\n],", cell[0], 10);
	}
	
	CShip *s = new CShip(iDeck);

	for (int i = 0; i < iDeck; i++)
	{
		CCell *pCell= NULL;
		if (m_Aqua.Try2PlaceDeck(cell[i],&pCell,s))
		{
			cout << "��� ������";

			s->m_pCells.push_back(pCell);
			pCell->m_pShip = s;
		}
		else
		{
			s->ClearCells();
			delete s;
			cout << "������ ����� ������";

			return false;
		}
	}
	cout << "��� ������";

	m_Ships.push_back(s);

	return true;
}
bool CBattlePlayer::Try2openfile(string flink)
{
	ifstream fin;
	fin.open(flink); // ��������� ����
	if (!fin.is_open()) // ��������� �� ��������
	{
		return false;
	}
	else
	{
		return true;
	}
}
string CBattlePlayer::recieve()
{
	char buff[1024];
	char buff1[1024];
	recv(m_sock, &buff[0], sizeof(buff), 0);
	sscanf_s(buff, "%[^\n]", buff1,1024);
	cout << buff1 << "< ��� buf1 \n";
	return buff1;
}

string CBattlePlayer::placerecieve()
{
	char buff[1024];

	recv(m_sock, &buff[0], sizeof(buff), 0);

	string strbuf(buff);
	strbuf += "0";
	strbuf.erase(strbuf.find_first_of(")")+1, strbuf.find_first_of("0"));
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // ��� �������� ������� � ��������� A-j
	strbuf.erase(remove(strbuf.begin(), strbuf.end(), ' '), strbuf.end()); // �������� ��������
	cout << strbuf;
	char buf[50];
	int nDeck;
	sscanf_s(strbuf.c_str(), "%i(%[^)]", &nDeck, buf, 50);

	if (nDeck < 0 or nDeck > 4)
		return "False";
	switch (nDeck)
	{
	case 1:
		if (alf.find(strbuf[2]) != std::string::npos and strbuf[1] == '(' and strbuf[4] == ')' and strbuf.length() == 5) // �������� �� ��������, �������, ����������� ���������� � ��������� // ����������
		{
			return strbuf;
		}
		break;
	case 2:
		if (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and strbuf[1] == '(' and strbuf[7] == ')' and strbuf.length() == 8)
		{
			return strbuf;
		}
		break;
	case 3:
		if (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and alf.find(strbuf[8]) != std::string::npos and strbuf[1] == '(' and strbuf[10] == ')' and strbuf.length() == 11)
		{
			return strbuf;
		}
		break;
	case 4:
		if (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and alf.find(strbuf[8]) != std::string::npos and alf.find(strbuf[11]) != std::string::npos and strbuf[1] == '(' and strbuf[13] == ')' and strbuf.length() == 14)
		{
			return strbuf;
		}
		break;
	}
	return "False";
}
//string CBattlePlayer::fileplace(string flink) //����������
//{
//	setlocale(LC_ALL, "ru");
//	// ����� �++
//	string alf = "AaBbCcDdEeFfGgHhIiJj"; // ��� �������� ������� � ��������� A-j
//	ifstream fin;
//	fin.open(flink); // ��������� ����
//
//	if (!Try2openfile(flink)) // ��������� �� ��������
//	{
//		return "0";
//	}
//	else
//	{
//		string str;
//		while (!fin.eof()) // ������ ����
//		{
//			string strbuf = " ";
//			getline(fin, strbuf); // ����������� ��������� �� �����
//			char buf[50];
//
//			int nDeck;
//			sscanf_s(strbuf.c_str(), "%i(%[^)]", &nDeck, buf, 50);
//
//			if (nDeck < 0 or nDeck > 4)
//				return "False";
//			switch (nDeck)
//			{
//			case 1:
//				if (alf.find(strbuf[2]) != std::string::npos and strbuf[1] == '(' and strbuf[4] == ')' and strbuf.length() == 5) // �������� �� ��������, �������, ����������� ���������� � ���������
//				{
//					return strbuf;
//				}
//				break;
//			case 2:
//				if (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and strbuf[1] == '(' and strbuf[7] == ')' and strbuf.length() == 8)
//				{
//					return strbuf;
//				}
//				break;
//			case 3:
//				if (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and alf.find(strbuf[8]) != std::string::npos and strbuf[1] == '(' and strbuf[10] == ')' and strbuf.length() == 11)
//				{
//					return strbuf;
//				}
//				break;
//			case 4:
//				if (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and alf.find(strbuf[8]) != std::string::npos and alf.find(strbuf[11]) != std::string::npos and strbuf[1] == '(' and strbuf[13] == ')' and strbuf.length() == 14)
//				{
//					return strbuf;
//				}
//				break;
//			}
//			return "False";
//		}
//		fin.close();
//	}
//}
bool CBattlePlayer::IsAlive()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if (m_Ships[i]->Alive())
			return true;
	}

	return false;
}