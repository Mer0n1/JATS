#include "JATS.h"

JsonDocument::JsonDocument()
{

}

JsonDocument::JsonDocument(string d)
{
	for (int j = 0; j < d.length(); j++) {
		string d_; d_ = d[j];
		msg.append(d_.c_str());
		if (msg[j] == '}') break; //доходим до конца ключ-запроса 
	}
}

interpretation JsonDocument::value(string key)
{
	int len = key.length();
	string itog;

	if (key == "" || key == " ") return interpretation("");

	for (int j = 0; j < msg.length(); j++) {
		if (msg[j] == '{') continue;
		for (int l = 0; l < len; l++)
		{
			if (msg[j + l] != key[l] || msg[j + len] != '"' || msg[j - 1] != '"') break;
			if (l == len - 1) {
				for (int c = j + len + 3; c < msg.length(); c++)
					if (msg[c] == '"') break; else
						itog += msg[c];
			}
		}
	}

	interpretation inc(itog);
	return inc;
}


//----------------------------------------------interpretation
interpretation::interpretation()
{
	key = "";
}
interpretation::interpretation(string key_)
{
	key = key_;
}
interpretation::~interpretation()
{

}
interpretation::operator string()
{
	return key;
}

void interpretation::toIntMassv(int* massv, int length_)
{
	if (key == "") return;
	if (key[key.length() - 1] != ' ')
		key += ' '; //добавляем пробел на всякий

	string data; //временный результат
	vector<int> vec(1); //изначально переводим в вектор (обяз.инициализация)
	int length = key.length() + 1; //узнаем размер

	for (int j = 0, n = 0; j < length; j++)
	{
		if (key[j] != ' ') {
			data += key[j];
			continue;
		}
		vec[n] = atoi(data.c_str()); //переводим число в int
		data.clear();
		n++; //кол во чисел (или номер текущего числа)
		vec.push_back(0); //новое число
	}

	//переведем в массив
	for (int j = 0; j < vec.size() && j < length_ / sizeof(int); j++) { //length учитывает макс.кол во индексов массива
		*massv = vec[j]; 
		massv++;
	}
}

void interpretation::toFloatMassv(float* massv, int length_)
{
	if (key == "") return;
	if (key[key.length() - 1] != ' ')
		key += " "; //добавляем пробел

	string data; //будет хранить число и очищаться
	vector<float> vec(1); //изначально переводим в вектор (обяз.инициализация)
	int length = key.length() + 1;

	for (int j = 0; j < length; j++) //переделаем все точки в запятые ради stof
		if (key[j] == '.') key[j] = ',';

	for (int j = 0, n = 0; j < length; j++)
	{
		if (key[j] != ' ') {
			data += key[j];
			continue;
		}

		vec[n] = stof(data); //переводим число в float
		data.clear(); //очищаем
		n++; //кол во чисел (или номер текущего числа)
		vec.push_back(0); //новое число
	}
	
	//переведем в массив
	for (int j = 0; j < vec.size() && j < length_ / sizeof(float); j++) { //length учитывает макс.кол во индексов массива
		*massv = vec[j];
		massv++;
	}
}


string interpretation::toString()
{
	return key;
}

int interpretation::toInt()
{
	string nool;
	for (int j = 0; j < key.length(); j++)
		if (key[j] == ' ') key.erase(j);

	return  (key != nool) ? atoi(key.c_str()) : 0;
}

float interpretation::toFloat()
{
	string nool;

	for (int j = 0; j < key.length(); j++) //переделаем все точки в запятые ради stof
		if (key[j] == '.') key[j] = ',';

	for (int j = 0; j < key.length(); j++)
		if (key[j] == ' ') key.erase(j);

	return (key != nool) ? stof(key) : 0;
}
