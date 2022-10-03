
#include <locale.h>
#include "functions.h"

using namespace std;


void main()
{
	setlocale(LC_ALL, "ru");

	//Переменные для пользовательского выбора.
	int userMenuChoice = -1;

	//Переменные для работы программы
	string fileName;
	bool isNameEntered = false;

	// Главный меню-цикл.
	while (userMenuChoice != 7)
	{
		std::system("cls");
		cout << "Практическая работа #2 ИКБО-03-21 Мазанов А.Е. Вариант 15\n\n"
			"Задание - Файлы.\n"
			"~~~~~~~~~~~~~~~~~Меню~~~~~~~~~~~~~~~\n";
		cout << "Текущее имя файла: ";
		if (isNameEntered)
		{
			cout << fileName << '\n';
		}
		else
		{
			cout << "Не введено\n";
		}

		cout	<< "\nВведите [0], чтобы ввести имя файла."
			<< "\nВведите [1], чтобы создать файл с числами."
			<< "\nВведите [2], чтобы вывести содержимое файла."
			<< "\nВведите [3], чтобы добавить новую строку в конец файла."
			<< "\nВведите [4], чтобы считать число из файла по его номеру."
			<< "\nВведите [5], чтобы узнать количество чисел в файле."
			<< "\nВведите [6], чтобы cоздать новый файл из значений исходного,"
			<< "\n             увеличив его на среднее арифметическое "
			<< "\n             всех отрицательных чиселисходного файла."
			<< "\nВведите [7], чтобы закончить работу программы."
			<< "\nВаш выбор: ";
		cin >> userMenuChoice;
		cin.ignore();
		if (userMenuChoice == 0)
		{
			cout << "Введите имя файла:\n";
			cin >> fileName;
			isNameEntered = true;
		}
		if (isNameEntered)
		{
			if (userMenuChoice == 1)
			{
				if (isFileExist(fileName) == true)
				{
					cout << "Файл с таким именем уже сущестует!\n";
				}
				else
				{
					createFile(fileName);
				}
			}
			else if (userMenuChoice >= 2 && userMenuChoice <= 7)
			{
				if (tryOpenFile(fileName))
				{
					switch (userMenuChoice)
					{
					case 2:
						printFileСontents(fileName);
						break;

					case 3:
						addNewString(fileName);
						break;

					case 4:
						int numberID;
						cout << "Введите номер числа:\n";
						cin >> numberID;
						if (numberID <= countAmountOfNumbers(fileName))
						{
							cout << "Число под номером " << numberID <<
								": " << getNumberByID(fileName, numberID) <<
								'\n';
						}
						else
						{
							cout << "В файле меньше чисел, чем указанный номер\n";
						}
						break;

					case 5:
						cout << "Количество чисел в файле: " << countAmountOfNumbers(fileName) << '\n';
						break;

					case 6:
					{
						string newFileName;
						cout << "Введите имя нового файла:\n";
						cin >> newFileName;
						if (isFileExist(newFileName) == true)
						{
							cout << "Файл с таким именем уже сущестует!\n";
						}
						else
						{
							specialTask(fileName, newFileName);
						}
						break;
					}

					case 7:
						cout << "\nДо свидания!\n";
						break;

					default:
						cout << "\nЯ не понимаю вас.\n";
						cin.clear();
						break;
					}
				}
				else
				{
					cout << "Ошибка открытия файла\n";
				}
			}
		}
		else
		{
			cout << "Имя файла не введено!\n";
		}
		
		std::system("pause");
	}
}