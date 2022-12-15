#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CBattleGame.h"

#pragma comment (lib, "ws2_32.lib")
#include <iostream>

#include "winsock2.h" 

using namespace std;

CBattleGame::CBattleGame()
{
	m_iCurrentMove = MOVE1;
	m_Player1.m_pAnotherPlayer = &m_Player2;
	m_Player2.m_pAnotherPlayer = &m_Player1;
}
CBattleGame::~CBattleGame()
{

}

bool CBattleGame::StartTCP(int port)
{
	setlocale(LC_ALL, "Rus");
	
	WSADATA wsaData;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Error WSAStartup %i\n", WSAGetLastError());
		return false;
	}
	
	SOCKET mysocket;
	
	if ((mysocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		printf("Error socket %i\n", WSAGetLastError());
		WSACleanup(); // Деиницилизация библиотеки Winsock
		return false;
	}
	
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port); 
	local_addr.sin_addr.s_addr = 0; 
									
	if (bind(mysocket, (sockaddr *)&local_addr, sizeof(local_addr)))
	{
		
		printf("Error bind %d\n", WSAGetLastError());
		closesocket(mysocket); 
		WSACleanup();
		return false;
	}
	
	if (listen(mysocket, 0x100))
	{
		printf("Error listen %d\n", WSAGetLastError());
		closesocket(mysocket);
		WSACleanup();
		return false;
	}
	printf("Начинаем игру\n");
	
	SOCKET client_socket; 
	sockaddr_in client_addr;
 
	int client_addr_size = sizeof(client_addr);
	
	
		client_socket = accept(mysocket, (sockaddr *)&client_addr, &client_addr_size);
		
		
		m_Player1.m_sock = client_socket;

		HOSTENT *hst;
		hst = gethostbyaddr((char *)&client_addr.sin_addr.s_addr, 4, AF_INET);

		// вывод сведений о клиенте
		printf("Игрок1 с IP [%s] на связи!\n", inet_ntoa(client_addr.sin_addr));

		client_socket = accept(mysocket, (sockaddr *)&client_addr, &client_addr_size);

		m_Player2.m_sock = client_socket;
				
		hst = gethostbyaddr((char *)&client_addr.sin_addr.s_addr, 4, AF_INET);

		// вывод сведений о клиенте
		printf("Игрок2 с IP [%s] на связи!\n", inet_ntoa(client_addr.sin_addr));
		
	return true;
}

void CBattleGame::DoPlay()
{
	m_Player2.Message("Соперник расставляет корабли. Подождите некоторое время.");

	if (m_Player1.PrepareShips())
	{
		m_Player1.Message("Соперник расставляет корабли. Подождите некоторое время.");

	}
	if (!m_Player2.PrepareShips())
	{
		return;
	}

	while (m_Player1.IsAlive() and m_Player2.IsAlive())
	{
		if (m_iCurrentMove == MOVE1)
		{
			cout << "Ход игрока 1\n";
			m_Player1.DoMove();
		}
		if (m_iCurrentMove == MOVE2)
		{
			cout << "Ход игрока 2\n";
			m_Player2.DoMove();
		}
		m_iCurrentMove *= -1;
	}

}