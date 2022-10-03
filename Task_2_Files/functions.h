#pragma once

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

using namespace std;

bool tryOpenFile(string fileName)
{
	ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		if (!file.good())
		{
			cout << "Ошибка с файлом " << fileName << '\n';
		}
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}


bool isFileExist(string fileName)
{
	ifstream file;
	file.open(fileName);
	return file.good();
}


void createFile(string fileName)
{
	ofstream newFile;
	newFile.open(fileName);
	cout << "Введите некоторое кол-во строк с числами через пробел.\nЧтобы закончить ввод нажмите [Enter]\n";
	string line;
	bool isFirstString = true;
	getline(cin, line);
	while (line != "\0")
	{
		if (!isFirstString)
		{
			newFile << '\n';
		}
		newFile << line;
		isFirstString = false;
		getline(cin, line);
	}
	if (!newFile.good())
	{
		cout << "Ошибка с файлом " << fileName << '\n';
	}
	newFile.close();
}

void printFileСontents(string fileName)
{
	ifstream file;
	string line;
	bool isFirstString = true;
	file.open(fileName);
	if (file.is_open())
	{
		cout << "Содержимое файла:\n";
		while (!file.eof())
		{
			getline(file, line);
			cout << line;
			isFirstString = false;
			if (!isFirstString)
			{
				cout << '\n';
			}
		}
		file.close();
	}
}


void addNewString(string fileName)
{
	cout << "Введите новую строку:\n";
	ofstream file;
	file.open(fileName, ofstream::app);
	if (file.is_open())
	{
		string line;
		getline(cin, line);
		file << '\n' << line;
		if (!file.good())
		{
			cout << "Ошибка с файлом " << fileName << '\n';
		}
		file.close();
	}
}


int getNumberByID(string fileName, int ID)
{
	ifstream file;
	int number = 0;
	file.open(fileName);
	if (file.is_open()) {
		int iter = 0;
		while (iter < ID)
		{
			iter++;
			file >> number;
		}
		if (!file.good())
		{
			cout << "Ошибка с файлом " << fileName << '\n';
		}
		file.close();
		return number;
	}
}


int countAmountOfNumbers(string fileName)
{
	ifstream file;
	int amount = 0;
	int value;
	file.open(fileName);
	if (file.is_open()) {
		while (!file.eof())
		{
			amount++;
			file >> value;
		}
		file.close();
		return amount;
	}
}


int findAveregeOfNegativesInFile(string fileName)
{
	int sumOfNegative = 0;
	int amountOfNegatives = 0;
	int value;
	ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		while (!file.eof())
		{
			file >> value;
			if (value < 0)
			{
				amountOfNegatives++;
				sumOfNegative += value;
			}
		}
	}
	file.close();
	return sumOfNegative / amountOfNegatives;
}


vector<int> parseStringToIntArray(string line)
{
	vector<int> numbers;
	string number;
	bool isFirstNumberInit = false;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			if (isFirstNumberInit)
			{
				numbers.push_back(stoi(number));
				number = "";
				isFirstNumberInit = true;
			}	
		}
		else
		{
			number += line[i];
			if (!isFirstNumberInit)
			{
				isFirstNumberInit = true;
			}
		}
	}
	numbers.push_back(stoi(number));
	return numbers;
}


void specialTask(string fileName, string newFileName)
{
	ifstream file;
	string line;
	file.open(fileName);
	ofstream newFile;
	newFile.open(newFileName);
	bool isFirstLine = true;
	if (file.is_open()) {
		vector<int> numbersOfLine;
		int average = findAveregeOfNegativesInFile(fileName);
		while (!file.eof())
		{
			if (!isFirstLine)
			{
				newFile << '\n';
			}
			getline(file, line);
			numbersOfLine = parseStringToIntArray(line);
			for (int i = 0; i < numbersOfLine.size(); i++)
			{
				newFile << numbersOfLine.at(i) + average;
				if (i != numbersOfLine.size() - 1)
				{
					newFile << " ";
				}
			}
			isFirstLine = false;
		}
		file.close();
		newFile.close();
	}
}


