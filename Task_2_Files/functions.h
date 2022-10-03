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
			cout << "Îøèáêà ñ ôàéëîì " << fileName << '\n';
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


int getRandomInt(int left, int right)
{
	return left + rand() % (right - left + 1);
}


void createFile(string fileName)
{
	ofstream newFile;
	newFile.open(fileName);
	int numberOfRows = getRandomInt(3, 10);
	int amountOfNumbers;
	for (int i = 0; i < numberOfRows; i++)
	{
		amountOfNumbers = getRandomInt(3, 10);
		for (int j = 0; j < amountOfNumbers; j++)
		{
			newFile << getRandomInt(-30, 30);
			if (j < amountOfNumbers - 1)
			{
				newFile << " ";
			}
		}
		if (i < numberOfRows - 1)
		{
			newFile << "\n";
		}
	}
	if (!newFile.good())
	{
		cout << "Îøèáêà ñ ôàéëîì " << fileName << '\n';
	}
	newFile.close();
}


void printFileÑontents(string fileName)
{
	ifstream file;
	string line;
	bool isFirstString = true;
	file.open(fileName);
	if (file.is_open())
	{
		cout << "Ñîäåðæèìîå ôàéëà:\n";
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
	cout << "Ââåäèòå íîâóþ ñòðîêó:\n";
	ofstream file;
	file.open(fileName, ofstream::app);
	if (file.is_open())
	{
		string line;
		getline(cin, line);
		file << '\n' << line;
		if (!file.good())
		{
			cout << "Îøèáêà ñ ôàéëîì " << fileName << '\n';
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
			cout << "Îøèáêà ñ ôàéëîì " << fileName << '\n';
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


