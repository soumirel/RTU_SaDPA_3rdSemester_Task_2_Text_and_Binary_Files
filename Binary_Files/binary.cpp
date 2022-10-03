
#include <locale.h>
#include "functions.h"

using namespace std;

//TODO: удалить запись в двоичном файле по её ключу."
//TODO: сформировать в текстовом файле список друзей, родившихся в указанном месяце."
//TODO: указать имя, родившегося в заданную дату."

void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//Переменные для пользовательского выбора.
	int userMenuChoice = -1;

	//Переменные для работы программы
	string textFileName;
	string binFileName;
	bool isTextFileNameEntered = false;
	bool isBinFileNameEntered = false;
	bool isTextFileEmpty = true;

	// Главный меню-цикл.
	while (userMenuChoice != 10)
	{
		std::system("cls");
		cout << "Практическая работа #2 ИКБО-03-21 Мазанов А.Е. Вариант 15\n\n"
			"Задание - Файлы. Двоичная запись.\n"
			"~~~~~~~~~~~~~~~~~Меню~~~~~~~~~~~~~~~\n";
		cout << "Текущее имя пользовательского текстового файла: ";
		if (isTextFileNameEntered)
		{
			cout << textFileName << '\n';
		}
		else
		{
			cout << "Не введено\n";
		}
		cout << "Текущее имя пользовательского двоичного файла: ";
		if (isBinFileNameEntered)
		{
			cout << binFileName << '\n';
		}
		else
		{
			cout << "Не введено\n";
		}

		cout << "\nВведите [0], чтобы ввести имя текстового файла."
			<< "\nВведите [1], чтобы ввести имя двоичного файла."
			<< "\nВведите [2], чтобы переместить данные из текстового файла в двоичный."
			<< "\nВведите [3], чтобы переместить данные из двоичного файла в текстовый."
			<< "\nВведите [4], чтобы вывести все записи из двоичного файла."
			<< "\nВведите [5], чтобы вывести все записи из текстового файла."
			<< "\nВведите [6], чтобы получить запись из двоичного файла по её номеру."
			<< "\nВведите [7], чтобы удалить запись в двоичном файле по заданному ключу, путём замены на последнюю."
			<< "\nВведите [8], чтобы сформировать в текстовом файле список друзей, родившихся в указанном месяце."
			<< "\nВведите [9], чтобы указать имя, родившегося в заданную дату."
			<< "\nВведите [10], чтобы закончить работу программы."
			<< "\nВаш выбор: ";

		cin >> userMenuChoice;
		cin.ignore();
		if (userMenuChoice == 0 || userMenuChoice == 1)
		{
			switch (userMenuChoice)
			{
			case 0:
			{
				cout << "Введите имя файла:\n";
				cin >> textFileName;
				textFileName += ".txt";
				createTextFile(textFileName);
				isTextFileNameEntered = true;
				break;
			}	

			case 1:
				cout << "Введите имя бинарного файла:\n";
				cin >> binFileName;
				binFileName += ".dat";
				createBinFile(binFileName);
				isBinFileNameEntered = true;
				break;
			}
		}
		else if (isTextFileNameEntered && isBinFileNameEntered)
		{
			if (tryOpenFile(textFileName, 't') && tryOpenFile(binFileName, 'b'))
			{
				switch (userMenuChoice)
				{
				case 2:
					translateTextToBin(textFileName, binFileName);
					cout << "Данные из текстового файла перенесены в двоичный файл";
					break;

				case 3:
					translateBinToText(textFileName, binFileName);
					break;

				case 4:
					printBinFile(binFileName);
					break;

				case 5:
					printFileСontents(textFileName);
					break;

				case 6:
				{
					int recordID;
					cout << "Введите номер записи:\n";
					cin >> recordID;
					if (recordID <= countRecordsInBin(binFileName))
					{
						cout << "Запись под номером " << recordID <<
							": " << getRecordByID(binFileName, recordID) <<
							'\n';
					}
					else
					{
						cout << "В файле меньше записей, чем указанный номер\n";
					}
					break;
				}
				case 7:
				{
					char recordKey[6];
					cout << "Введите ключ записи (дата в формате dd.mm)\n";
					cin.getline(recordKey, 6, '\n');

					if (deleteRecordByKey(binFileName, recordKey))
					{
						cout << "Запись по ключу: " << recordKey <<
							" заменена на последнюю запись\n";
					}
					else
					{
						cout << "В файле нет записи с ключом: " <<
							recordKey;
					}

					break;
				}

				case 8:
					char month[3];
					cout << "Введите месяц в формате mm:\n";
					cin.get(month, 3);
					copyRecordsByMonth(binFileName, textFileName, month);
					cout << "Информация записана в текстовый файл\n";
					break;

				case 9:
					cout << "Введите дату в формате dd.mm:\n";
					char userDate[6];
					cin.getline(userDate, 6, '\n');
					try
					{
						printFriendBirthday(getRecordByKey(binFileName, userDate));
					}
					catch (const std::invalid_argument& invArg) 
					{
						cout << invArg.what() << '\n';
					}
					break;

				case 10:
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
		else
		{
			cout << "Имя файла не введено!\n";
		}

		std::system("pause");
	}
}