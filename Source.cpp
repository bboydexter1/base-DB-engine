#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Column.h"
#include "StringFuntions.h"
#include "VectorFuntions.h"
#include "DataBaseFuntions.h"

using namespace std;


int main(int argc, char* argv[])
{
	stringstream fileContent;

	while (cin.good())
	{
		string wordHolder;
		cin >> wordHolder;
		fileContent << " " <<  wordHolder ;
	}

	vector<string> commands = partStringStreamToVector(fileContent.str(), ';');
	commands = cutStaringSpaces(commands);

	for (string command : commands)
	{
		if (startsWith(command,"CREATE"))
		{	
			vector<string> commandParts = partStringStreamToVector(command, ' ');
			bool created = createTable(commandParts);

			if (created == true)
				cout << "table was created successfully" << endl;
			else
				cout << "table wasn`t created" << endl;
		}
		else if (startsWith(command, "INSERT INTO"))
		{
			vector<string> commandParts = partStringStreamToVector(command, ',');
			bool inserted = insertToTable(commandParts);
			if (inserted == true)
				cout << "data inserted" << endl;
			else
				cout << "data could not be inserted" << endl;
		}
		else if (startsWith(command, "SELECT"))
		{
			vector<string> commandParts = partStringStreamToVector(command, ' ');
			displayTable(commandParts);
		}
		else if (startsWith(command, "DELETE FROM"))
		{
			vector<string> commandParts = partStringStreamToVector(command, ' ');
			bool droped = dropData(commandParts);
			if (droped == true)
				cout << "data droped" << endl;
			else
				cout << "data could not be droped" << endl;
		}
		else if (startsWith(command, "DROP"))
		{
			vector<string> commandParts = partStringStreamToVector(command, ' ');
			bool droped = dropTable(commandParts);
			if (droped == true)
				cout << "table removed" << endl;
			else
				cout << "table could not be removed" << endl;
		}
	} 
}