#include <iostream>
#include "JATS.h"

//Java and translate string

int main(int argc, char* argv[])
{
	//Класс сделан на подобие json Qt
	setlocale(LC_ALL, "Russian");

	JsonDocument doc; //класс для перевода json запросов в string
	interpretation inter; //класс для перевода из string в массивы разных типов

	//Пример запроса Json
	string result = "{\"Type\":\"White\",\"Value\":\"32\",\"Code16x\":\"23 545 123.45 34 11 34.4 157663\"}";
	cout << "Пример запроса: \n" << result << "\n\n";

	doc = result; //обязательная инициализация
	//Вывод результатов
	cout << "Type: "    << doc.value("Type").toString() << endl; 
	cout << "Code16x: " << doc.value("Code16x").toString() << endl;
	cout << "Value: "   << doc.value("Value").toInt() << endl;


	//Перевод в массив
	int IntMassv[30];
	float FlMassv[30];

	memset(IntMassv, 0, 30 * 4);
	memset(FlMassv, 0, 30 * 4);
	
	doc.value("Code16x").toIntMassv(&IntMassv[0], sizeof(IntMassv));
	doc.value("Code16x").toFloatMassv(&FlMassv[0], sizeof(IntMassv));

	cout << "\nВыводим int массив:\n";
	for (int j = 0; j < 30; j++)
		cout << IntMassv[j] << " "; cout << "\n\n";

	cout << "Выводим float массив:\n";
	for (int j = 0; j < 30; j++)
		cout << FlMassv[j] << " "; cout << "\n\n"; 

	//c inter можно взаимодействовать без JsonDocument
	inter = { "23 545 123.45 34 11 34.4 1576653" };
	inter.toFloatMassv(&FlMassv[0], 30); //...

	system("pause");
}