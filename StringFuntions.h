#pragma once
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "VectorFuntions.h"
using namespace std;

//check if string starts with given string
bool startsWith(string mainStr, string matchStr);
//returns string between 2 chars
string cutBetween(string toCut, string leftStr, string rightStr);
//returns string between 2 chars
string cutBetween(string toCut, string cutStr);
//removes special characters from string
string trimString(string toCut);
//removes first words from string 
string throwAwayFirstWords(string toCut, int amount);