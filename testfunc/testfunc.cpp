// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

string recieve(string strbuf)
{
	string buff = strbuf;

	string alf = "AaBbCcDdEeFfGgHhIiJj"; // для проверки символа в диапозоне A-j
	string cifrs = "123456789"; // для проверки символа в диапозоне A-j


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


string placerecieve(string strbuf)
{
	string alf = "AaBbCcDdEeFfGgHhIiJj";
	char buf[50];
	char buf1[50];

	int nDeck;
	sscanf_s(strbuf.c_str(), "%i(%[^)]", &nDeck, buf, 50);

	if (nDeck < 0 or nDeck > 4 or strbuf.length() < 5)
		return "False";
	switch (nDeck)
	{
	case 1:
		if (alf.find(strbuf[2]) != std::string::npos and strbuf[1] == '(' and strbuf[4] == ')' and strbuf.length() == 5)
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
		if  (alf.find(strbuf[2]) != std::string::npos and alf.find(strbuf[5]) != std::string::npos and alf.find(strbuf[8]) != std::string::npos and strbuf[1] == '(' and strbuf[10] == ')' and strbuf.length() == 11)
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


int main()
{
	while (true)
	{
		string str = " ";
		cin >> str;
		cout << recieve(str) << endl << endl;

	}
		

	system("pause");
}

