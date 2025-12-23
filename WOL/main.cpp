#include <iostream>
#include <Windows.h>
#include <fstream> //0 открываем fstream
using std::cin;
using std::cout;
using std::endl;

//#define File.txt
#define dhcpd
void main()
{
	setlocale(LC_ALL, "");
#ifdef File.txt
	const int SIZE = 1024 * 64;
	char ip[SIZE] = {};
	char mac[SIZE] = {};
	std::ifstream fin("201_RAW.txt");
	std::ofstream fout("File.txt");
	if (fin.is_open())
	{
		//3. Read file
		while (!fin.eof()) //eof - End Of File
		{
			fin >> ip;
			fin >> mac;
			fout << mac << "\t" << ip << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}
	fin.close();
	fout.close();
#endif // File.txt

#ifdef dhcpd
	const int SIZE = 1024 * 64;
	char ip[SIZE] = {};
	char mac[SIZE] = {};
	std::ifstream fin("201_RAW.txt");
	std::ofstream fout("201.dhcpd");
	if (fin.is_open())
	{
		//3. Read file
		for (int i = 1; !fin.eof(); i++) //eof - End Of File
		{
			fin >> ip;
			fin >> mac;
			if (fin.eof()) break;
			fout << "host-" << i << endl << "{" << endl;
			fout << "hardware ethernet" << "\t" << mac << ";"<<endl;
			fout << "fixed-address" << "\t\t" << ip << ";" << endl << "}"<<endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}
	fin.close();
	fout.close();
#endif // dhcpd


}