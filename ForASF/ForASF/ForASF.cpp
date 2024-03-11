#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;

void createJson(nlohmann::json &json, const string login)
{
	string name = login + ".json";
	string folderPath = "output";
	string filePath = folderPath + "\\" + name;
	

	ofstream file(filePath);
	if (file.is_open())
	{
		file << json;
	}
	file.close();
}

int main()
{
	std::string folderName = "output";
	std::filesystem::create_directory(folderName);
	string line;

	fstream in("logpass.txt"); // open .txt

	if (in.is_open())
	{
		while (getline(in, line))						//выполняется пока есть линии в потоковом выводе in который считывает .txt
		{
			int length = size(line);					//для того чтоб можно было отследить : и разделить строку на 2 строковые переменыне

			int find_duble_dot;

			for (int i = 0; i < length; i++)			// для нахождения инедкса :
			{
				if (line[i] == ':')
				{
					find_duble_dot = i;
					break;
				}
			}

			//вычисление длинны строки для логина и пароля
			int lengthOfLogin = find_duble_dot;
			int lengthOFPassword = length - 1 - find_duble_dot;


			string login (lengthOfLogin, ' ');
			string password (lengthOFPassword, ' ');

			bool flag = true;
			int count = 0;
			for (int i = 0; i < length; i++)			// цикл для записи в строки символов
			{
				if (line[i] == ':')
				{
					flag = false;
					continue;
				}
					
				if (flag)
					login[i] = line[i];

				if (!flag)
				{
					password[count] = line[i];
					count++;
				}
			}
			ifstream setting("setting.txt");
			nlohmann::json json;
			setting >> json;
			json["SteamLogin"] = login;
			json["SteamPassword"] = password;

			createJson(json, login);
		}
	}
	in.close();

	std::cout << "Successful" << std::endl;
	std::cout << "Tap any key for close...";
	std::cin.get();

	return 0;
}