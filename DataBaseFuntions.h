#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Column.h"
#include "StringFuntions.h"
#include "VectorFuntions.h"

using namespace std;

bool createTable(vector<string> commandParts);
vector<Column> getTableTemplate(string fileName);
bool insertToTable(vector<string> commandParts);
bool displayTable(vector<string> commandParts);
bool dropTable(vector<string> commandParts);
bool dropData(vector<string> commandParts);