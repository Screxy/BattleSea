// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CBattleGame.h"

using namespace std;

int main()
{
	CBattleGame game;
	
	
	if (game.StartTCP(10000))
		game.DoPlay();
}

