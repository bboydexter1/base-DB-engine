#pragma once
#include<string>
#include<iostream>

using namespace std;

class Column
{
	string name;
	string type;
	int lenght = 0;
public:
	Column();
	Column(string inName, string inType);

	string GetName();
	string GetType();
	string GetLenghtStr();
};

