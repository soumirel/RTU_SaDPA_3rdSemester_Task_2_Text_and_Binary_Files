#pragma once

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <string>

using namespace std;

vector<string> names
{
	"Вася", "Петя", "Гоша", "Дима", "Саша",
	"Лиза", "Анна", "Лена", "Крис", "Маня"
};
vector<string> surnames
{
	"П.", "Ж.", "А.", "Г.", "Д.", "П.", "Н."
};

struct FriendsBirthday{
	char name[8];
	char date[6];
};


bool isFileExist(string fileName)
{
	ifstream file;
	file.open(fileName);
	char a[3];
	return file.good();
}


bool tryOpenFile(string fileName, char type)
{
	ifstream file;
	if (type == 't')
		file.open(fileName);
	if (type == 'b')
		file.open(fileName, ios::binary);
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


void printBinFile(string binFileName)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	FriendsBirthday birthday;
	binFile.read((char*)&birthday, sizeof(birthday));
	cout << "Содержимое бинарного файла:\n";
	while (!binFile.eof()) 
	{
		cout << birthday.name << " " << birthday.date << '\n';
		binFile.read((char*)&birthday, sizeof(birthday));
	}
}

void printFileСontents(string fileName)
{
	ifstream file;
	string line;
	bool isFirstString = true;
	file.open(fileName);
	if (file.is_open())
	{
		cout << "Содержимое текстового файла:\n";
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


void translateBinToText(string textFileName, string binFileName)
{
	ofstream textFile;
	ifstream binFile;
	textFile.open(textFileName);
	binFile.open(binFileName, ios::in | ios::binary);
	FriendsBirthday birthday;
	binFile.read((char*)&birthday, sizeof(FriendsBirthday));
	while (binFile.good()) 
	{
		textFile << birthday.name << " " << birthday.date;
		binFile.read((char*)&birthday, sizeof(FriendsBirthday));
		if (!binFile.eof())
		{
			textFile << '\n';
		}
	}
}


void translateTextToBin(string textFileName, string binFileName)
{
	ifstream textFile;
	ofstream binFile;
	textFile.open(textFileName);
	binFile.open(binFileName, ios::out | ios::binary);
	while (!textFile.eof()) 
	{
		FriendsBirthday birthday;
		char name[8];
		char date[6];
		name[7] = '\0';
		date[5] = '\0';

		textFile.read((char*)&name, 7);
		strcpy_s(birthday.name, name);

		textFile.get();
		textFile.read((char*)&date, 5);
		strcpy_s(birthday.date, date);

		textFile.get();

		binFile.write((char*)&birthday, sizeof(FriendsBirthday));
	}

	textFile.close();
	binFile.close();
}


string getRecordByID(string binFileName, int ID)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	FriendsBirthday birthday;
	string record = "";
	binFile.seekg(sizeof(FriendsBirthday) * (ID - 1), ios::beg);
	binFile.read((char*)&birthday, sizeof(FriendsBirthday));
	record += birthday.name;
	record += " ";
	record += birthday.date;
	binFile.close();
	return record;
}


bool deleteRecordByKey(string binFileName, char recordKey[6])
{
	FriendsBirthday lastRecord;
	fstream binFile;

	binFile.open(binFileName, ios::in | ios::out | ios::binary);
	binFile.seekg(-(int)sizeof(FriendsBirthday), ios::end);
	binFile.read((char*)&lastRecord, sizeof(FriendsBirthday));

	binFile.seekg(0, ios::beg);
	FriendsBirthday currentRecord;
	while (binFile.good())
	{
		binFile.read((char*)&currentRecord, sizeof(FriendsBirthday));
		if (strcmp(currentRecord.date, recordKey) == 0)
		{
			binFile.seekg(-(int)sizeof(FriendsBirthday), ios::cur);
			binFile.write(reinterpret_cast<const char*>(&lastRecord),
				sizeof(FriendsBirthday));
			binFile.close();
			return true;
		}
	}
	binFile.close();
	return false;
}


FriendsBirthday getRecordByKey(string binFileName, char* recordKey)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	FriendsBirthday currentRecord;
	
	while (binFile.good())
	{
		binFile.read((char*)&currentRecord, sizeof(currentRecord));
		if (strcmp(currentRecord.date, recordKey) == 0)
		{
			binFile.close();
			return currentRecord;
		}
	}
	throw std::invalid_argument("There is no record by key");
}


void printFriendBirthday(FriendsBirthday birthday)
{
	cout << birthday.date << " день рождения у " << birthday.name << '\n';
}


int countRecordsInBin(string binFileName)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	binFile.seekg(0, std::ios::end);
	int size = binFile.tellg();
	binFile.close();
	return size / sizeof(FriendsBirthday);
}


int getRandomInt(int left, int right)
{
	return left + rand() % (right - left + 1);
}


void createBinFile(string binFileName)
{
	ofstream binFile;
	binFile.open(binFileName, ios::out | ios::binary);
	
	FriendsBirthday currentBirthday;
	for (int i = 0; i < 10; i++)
	{
		int day = getRandomInt(1, 30);
		int month = getRandomInt(1, 12);
		string date;
		if (day > 9)
		{
			date += to_string(day);
		}
		else
		{
			date += '0' + to_string(day);
		}
		date += '.';
		if (month > 9)
		{
			date += to_string(month);
		}
		else
		{
			date += '0' + to_string(month);
		}
		strcpy_s(currentBirthday.date, date.c_str());
		string name = names.at(getRandomInt(0, names.size() - 1)) +
			" " + surnames.at(getRandomInt(0, surnames.size() - 1));
		strcpy_s(currentBirthday.name, name.c_str());
		binFile.write((char*)&currentBirthday, sizeof(FriendsBirthday));	
	}
	binFile.close();
}


void createTextFile(string textFileName)
{
	ofstream newTextFile;
	newTextFile.open(textFileName);

	int recordsAmount = 10;

	for (int i = 0; i < recordsAmount; i++)
	{
		int day = getRandomInt(1, 30);
		int month = getRandomInt(1, 12);
		string date = (day <= 9 ? "0" + to_string(day) : to_string(day)) + "." +
			(month <= 9 ? "0" + to_string(month) : to_string(month));

		newTextFile << names.at(getRandomInt(0, names.size() - 1)) +
			" " + surnames.at(getRandomInt(0, surnames.size() - 1)) + " " << date;

		if (i != recordsAmount - 1)
		{
			newTextFile << '\n';
		}
	}
	newTextFile.close();
}


void copyRecordsByMonth(string binFileName, string textFileName, char month[3])
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	ofstream textFile;
	textFile.open(textFileName);
	FriendsBirthday currentBirthday;
	while (binFile.good())
	{
		binFile.read((char*)&currentBirthday, sizeof(FriendsBirthday));
		char currentMonth[3];
		copy(currentBirthday.date + 3, currentBirthday.date + 6, currentMonth);
		if (strcmp(currentMonth, month) == 0)
		{
			textFile << currentBirthday.name << " " << currentBirthday.date << "\n";
		}
	}

}