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
	int k = 0;
	Message("Расставляйте корабли!");
	Message("Инструкция: 4(a1,a2,a3,a4)");

	
	while (!ShipsAreReady())
	{
		if (k == 0)
		{
			if(placerecieve() != "False")
			{
				if (Try2PlaceShip(lastwords))
				{
					Message("OK");
				}
			}
			else
			{
				Message("Ошибка в расположении корабля!");
			}
		}
		if (lastwords != "False")
		{
			if (Try2PlaceShip(lastwords))
			{
				Message("OK");
			}
		}
		else
		{
			Message("Ошибка в расположении корабля!");
		}
		k++;
		Message(m_Aqua.PrintForeign());
		
	}
	Message("Ваши корабли готовы!");
	
	return true;
}
bool CBattlePlayer::DoMove()
{
	Message("Ваш ход!");
	string move = lastwords;

	Message(m_Aqua.PrintForeign());
	//Message(m_Aqua.PrintOwn());
	CShip *ship=NULL;
	if (m_pAnotherPlayer->m_Aqua.TestShip(move, &ship))
	{
		Message("Попадание!");
		
		if (!ship->Alive())
		{
			Message("Корабль потоплен!");

			if (!m_pAnotherPlayer->IsAlive())
			{
				Message("Вы выиграли(");
				m_pAnotherPlayer->Message("Вы проиграли(");
				return true;
			}
		}
		
		DoMove();

	}
	else
		Message("Мимо(");
	
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
	if (n4Deck == 1)// временно
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
	sscanf_s(ship.c_str(), "%i(%[^)]", &iDeck,buf,50);
	
	char cell[4][10];

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
			s->m_pCells.push_back(pCell);
			pCell->m_pShip = s;
		}
		else
		{
			s->ClearCells();
			delete s;
			return false;
		}
	}

	m_Ships.push_back(s);

	return true;
}
bool CBattlePlayer::Try2openfile(string flink)
{
	ifstream fin;
	fin.open(flink); // открываем файл
	if (!fin.is_open()) // проверяем на открытие
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

	recv(m_sock, &buff[0], sizeof(buff), 0);
	
	string strbuf(buff);
	strbuf += "f";
	if (strbuf[2] == '0')
		strbuf.erase(strbuf.find_first_of("0") + 1, strbuf.find_first_of("f"));
	else	
		strbuf.erase(2, strbuf.find_first_of("f"));
	strbuf.erase(remove(strbuf.begin(), strbuf.end(), ' '), strbuf.end());
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	string cifrs = "123456789"; // для проверки символа в диапозоне A-j
	lastwords = strbuf;

	if (alf.find(strbuf[0]) == std::string::npos or strbuf.length() == 1) return "False";
	if (strbuf.length() == 2)
	{
		if (cifrs.find(strbuf[1]) != std::string::npos)
			return buff;
		else
		{
			return "False";
		}
	}
	else if (strbuf.length() == 3)
	{
		if (strbuf[1] == '1' and strbuf[2] == '0')
			return buff;
		else
		{
			return "False";
		}
	}
	return buff;
}

string CBattlePlayer::placerecieve()
{
	char buff[1024];

	recv(m_sock, &buff[0], sizeof(buff), 0);

	string strbuf(buff);
	strbuf += "0";
	strbuf.erase(strbuf.find_first_of(")")+1, strbuf.find_first_of("0"));
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	strbuf.erase(remove(strbuf.begin(), strbuf.end(), ' '), strbuf.end());
	cout << strbuf;
	char buf[50];
	lastwords = strbuf;
	int nDeck;
	sscanf_s(strbuf.c_str(), "%i(%[^)]", &nDeck, buf, 50);

	if (nDeck < 0 or nDeck > 4)
		return "False";
	switch (nDeck)
	{
	case 1:
		if (alf.find(strbuf[2]) != std::string::npos and strbuf[1] == '(' and strbuf[4] == ')' and strbuf.length() == 5) // проверка по символам, скобкам, соответсвии палубности и координат // доработать
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
//string CBattlePlayer::fileplace(string flink) //доработать
//{
//	setlocale(LC_ALL, "ru");
//	// метод с++
//	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
//	ifstream fin;
//	fin.open(flink); // открываем файл
//
//	if (!Try2openfile(flink)) // проверяем на открытие
//	{
//		return "0";
//	}
//	else
//	{
//		string str;
//		while (!fin.eof()) // читаем файл
//		{
//			string strbuf = " ";
//			getline(fin, strbuf); // пробегаемся построчно по файлу
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
//				if (alf.find(strbuf[2]) != std::string::npos and strbuf[1] == '(' and strbuf[4] == ')' and strbuf.length() == 5) // проверка по символам, скобкам, соответсвии палубности и координат
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