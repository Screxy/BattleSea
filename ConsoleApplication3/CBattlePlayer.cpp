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
	Message("Расставляйте корабли!");
	Message("Инструкция: 4(a1,a2,a3,a4)");
	
	while (!ShipsAreReady())
	{
		if (Try2PlaceShip(recieve()))
		{
			Message("OK");
		}
		else
		{
			Message("Ошибка в расположении корабля!");
		}
		Message(m_Aqua.PrintForeign());
	}
	Message("Ваши корабли готовы!");
	
	return true;

}
bool CBattlePlayer::DoMove()
{
	Message("Ваш ход!");
	string move = recieve();

	Message(m_Aqua.PrintForeign());
	//Message(m_Aqua.PrintOwn());
	CShip *ship=NULL;
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	string cifrs = "123456789"; // для проверки символа в диапозоне A-j
	cout << move;

	move.erase(remove(move.begin(), move.end(), ' '), move.end()); // удаление пробелов
	cout << move;

	cout << move << endl;
	cout << move.length() << "< длина\n";
	if (alf.find(move[0]) == std::string::npos or move.length() == 1 or move.length() >= 4)
	{
		cout << "ошибка в букве или длине 1\n";
		Message("Некорректный ход");
		DoMove();
	}
	if (move.length() == 2)
	{
		if (cifrs.find(move[1]) == std::string::npos)
		{
			cout << "ошибка в цифре при длине 2\n";

			Message("Некорректный ход");
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
			cout << "ошибка в (10) при длине 3\n";

			Message("Некорректный ход");
			DoMove();
		}
	}
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
	cout << ship << "< ship before delete\n";
	ship.erase(remove(ship.begin(), ship.end(), ' '), ship.end()); // удаление пробелов
	cout << ship << "< ship after delete\n";;
	sscanf_s(ship.c_str(), "%i(%[^)]", &iDeck,buf,50);
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	char cell[4][10];
	if (iDeck < 1 or iDeck > 4)
	{
		cout << "ошибка в палубности";
		return false;
	}
	switch (iDeck)
	{
	case 1:
		if (alf.find(ship[2]) != std::string::npos and ship[1] == '(' and ship[4] == ')' and ship.length() == 5) // проверка по символам, скобкам, соответсвии палубности и координат // доработать
		{
		}
		else
		{
			cout << "1 ошибка в штуках после (";
			return false;
		}
	case 2:
		if (alf.find(ship[2]) != std::string::npos and alf.find(ship[5]) != std::string::npos and ship[1] == '(' and ship[7] == ')' and ship.length() == 8)
		{
		}
		else
		{
			cout << "2 ошибка в штуках после (";

			return false;
		}
	case 3:
		if (alf.find(ship[2]) != std::string::npos and alf.find(ship[5]) != std::string::npos and alf.find(ship[8]) != std::string::npos and ship[1] == '(' and ship[10] == ')' and ship.length() == 11)
		{
		}
		else
		{
			cout << "3 ошибка в штуках после (";
			return false;
		}
	case 4:
		if (alf.find(ship[2]) != std::string::npos and alf.find(ship[5]) != std::string::npos and alf.find(ship[8]) != std::string::npos and alf.find(ship[11]) != std::string::npos and ship[1] == '(' and ship[13] == ')' and ship.length() == 14)
		{
		}
		else
		{
			cout << "4 ошибка в штуках после (";
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
			cout << "без ошибок";

			s->m_pCells.push_back(pCell);
			pCell->m_pShip = s;
		}
		else
		{
			s->ClearCells();
			delete s;
			cout << "ошибка когда ставил";

			return false;
		}
	}
	cout << "без ошибок";

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
	char buff1[1024];
	recv(m_sock, &buff[0], sizeof(buff), 0);
	sscanf_s(buff, "%[^\n]", buff1,1024);
	cout << buff1 << "< это buf1 \n";
	return buff1;
}

string CBattlePlayer::placerecieve()
{
	char buff[1024];

	recv(m_sock, &buff[0], sizeof(buff), 0);

	string strbuf(buff);
	strbuf += "0";
	strbuf.erase(strbuf.find_first_of(")")+1, strbuf.find_first_of("0"));
	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	strbuf.erase(remove(strbuf.begin(), strbuf.end(), ' '), strbuf.end()); // Удаление пробелов
	cout << strbuf;
	char buf[50];
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