// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;


void Message(string s)
{
	cout << s << endl;
}

bool DoMove(string recieve)
{
	string move = recieve;

	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	string cifrs = "123456789"; // для проверки символа в диапозоне A-j
	if (alf.find(move[0]) == std::string::npos or move.length() == 1)
	{
		return true;
	}
	if (move.length() == 2)
	{
		Message("проверка на длину 2");
		if (cifrs.find(move[1]) == std::string::npos)
		{
			return true;
		}
	}
	else if (move.length() == 3)
	{
		if (move[1] == '1' and move[2] == '0')
		{
		}
		else
		{
			return true;
		}
	}
	Message("Все ок!");
	return true;
}


int main()
{
	setlocale(LC_ALL, "RU");
	while (true)
	{
		string str;
		cin >> str;
		DoMove(str);
		cout << endl;
	}
		

	system("pause");
}

