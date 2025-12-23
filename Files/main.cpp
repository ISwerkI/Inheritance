#include <iostream>
#include <Windows.h>
#include <fstream> //0 открываем fstream
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
//#define INPUT_STRING
#define GGG
void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE //ctrl + k + s
	std::ofstream fout; //1 Создаем поток
	fout.open("File.txt"); //2 Открываем поток
	fout << "Hello World!" << endl; //3 Записываем в поток
	fout.close(); // 4 Закрываем поток
	system("start notepad File.txt");
#endif
#ifdef INPUT_STRING
	const int SIZE = 256;
	char first[SIZE] = {};
	char last[SIZE] = {};
	SetConsoleCP(1251);
	cin >> first >> last;
	SetConsoleCP(866);
	cout << first << "\t" << last << endl;
#endif

#ifdef GGG
	const int SIZE = 1024 * 512;
	char sz_buffer[SIZE] = {}; //sz - Atring Zero
	//1. Создаем и открываем поток
	std::ifstream fin("File.txt"); //Если имя файла оказать при создании потока, он сразу же откроется.

	//2. Проверяем существование файла
	if (fin.is_open())
	{
		//3. Read file
		while (!fin.eof()) //eof - End Of File
		{
			fin.getline(sz_buffer, SIZE);
			cout << sz_buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}

	//?. Закрываем поток
	fin.close();
#endif // DEBUG

}