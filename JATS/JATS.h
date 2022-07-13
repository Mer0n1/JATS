#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

class interpretation
{
private:
	string key;
public:
	interpretation();
	interpretation(string key_);
	~interpretation();
	operator string();

	void toIntMassv(int* massv, int length); //massv - первый элемент массива
	void toFloatMassv(float* massv, int length);

	string toString(); //вернем тип string
	int toInt(); //вернем тип int
	float toFloat(); //вернем тип float
};

class JsonDocument
{
private:
	string msg;
public:
	JsonDocument();
	JsonDocument(string d);

	interpretation value(string key);
};