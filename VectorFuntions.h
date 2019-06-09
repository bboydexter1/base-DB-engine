#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//separetes string between given char and puts it in vector word by word
vector<string> partStringStreamToVector(string text, char separator);
//removes parts of vector that contatins usless strings
vector<string> trimVector(vector<string> inVector);
//puts file to vector line by line
vector<string> loadFileToVector(string fileName);
//return true if file exists
bool fileExists(string filename);
//removes spaces at begining of string
vector<string> cutStaringSpaces(vector<string> toCut);

