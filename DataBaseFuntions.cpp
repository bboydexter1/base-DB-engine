#include "DataBaseFuntions.h"

bool createTable(vector<string> commandParts)
{
	if (fileExists(commandParts[1] + ".xml"))
	{
		cout << "there is already table named " << commandParts[1] << endl;
		return false;
	}
	else
	{
		stringstream newFileContent;
		vector<Column> columns;
		vector<string> cleanVector;

		for (int i = 0; i < commandParts.size(); i++)
		{
			string tmp = commandParts[i];

			if (tmp != "(" && tmp != ")" && tmp != ":" && tmp != "")
				cleanVector.push_back(tmp);
		}
		commandParts = cleanVector;

		for (int i = 2; i < commandParts.size(); i = i + 2)
		{
			try
			{
				columns.push_back(Column(commandParts[i], commandParts[i + 1]));
			}
			catch (exception e)
			{
				cout << "missing arguments" << endl;
				return false;
			}
		}

		newFileContent << "<" << commandParts[1] << ">" << endl;
		newFileContent << "		" << "<" << "template" << ">" << endl;

		for (Column column : columns)
		{
			newFileContent << "			" << "<" << column.GetName() << " type = \"" << column.GetType() << "\" >";
			newFileContent << column.GetLenghtStr();
			newFileContent << "</" << column.GetName() << ">" << endl;
		}

		newFileContent << "		</" << "template" << ">" << endl;
		newFileContent << "		<" << "data" << ">" << endl;
		newFileContent << "		</" << "data" << ">" << endl;
		newFileContent << "</" << commandParts[1] << ">" << endl;

		ofstream myfile;
		myfile.open(commandParts[1] + ".xml");
		myfile << newFileContent.str();
		myfile.close();
		return true;
	}
}

vector<Column> getTableTemplate(string fileName)
{
	vector<Column> columns;

	if (fileExists(fileName + ".xml"))
	{
		ifstream myfile;
		myfile.open(fileName + ".xml");

		string line;
		bool templateFound = false;
		while (getline(myfile, line))
		{
			if (line.find("</template>") != string::npos)
				break;

			if (templateFound == true)
			{
				string name = cutBetween(line, "<", " type = ");
				string type = cutBetween(line, "type = \"", "\" >");
				string lenghtStr = cutBetween(line, "\" >", "</");
				int lenght;

				if (lenghtStr != "")
					columns.push_back(Column(name, type + "(" + lenghtStr + ")"));
				else
					columns.push_back(Column(name, type));
			}

			if (line.find("<template>") != string::npos)
				templateFound = true;
		}

		myfile.close();
		return columns;
	}
	else
	{
		cout << "there is no table like  " << fileName << endl;
		vector<Column> ret;
		return ret;
	}
}

bool addToFile(string fileName , vector<Column> tableTemplate , vector<string> toAdd)
{
	vector<string>fileContent = loadFileToVector(fileName);

	ofstream myfile;
	myfile.open(fileName+".xml");

	for (int i = 0; i < fileContent.size(); i++)
	{
		if(fileContent[i].find("</data>") == string::npos)
			myfile << fileContent[i] << "\n";
		else
		{	
			myfile << "		<item>" << "\n";
			for (int j = 0; j < tableTemplate.size(); j++)
			{
				myfile <<			"<"<< tableTemplate[j].GetName() << " type = \"" << tableTemplate[j].GetType() << "\" >" << toAdd[j];
				myfile << "</" << tableTemplate[j].GetName() << "> \n";
			}
			myfile << "		</item>" << "\n";
			myfile << fileContent[i] << "\n";
		}
	}
	
	myfile.close();
	return true;
}

bool insertToTable(vector<string> commandParts)
{
	commandParts = trimVector(commandParts);
	vector<string> commandStart = partStringStreamToVector(commandParts[0], ' ');
	commandStart = trimVector(commandStart);
	string tableName = commandStart[2];
	vector<Column> columns = getTableTemplate(tableName);
	commandParts[0] = throwAwayFirstWords(commandParts[0], 3);
	commandParts = cutStaringSpaces(commandParts);
	bool veryfication = true;

	if (commandParts.size() != columns.size())
	{
		veryfication = false;
		return false;
	}
	for (int i = 0; i < commandParts.size(); i++)
	{
		commandParts[i] = trimString(commandParts[i]);
		string str = commandParts[i];		

		if (columns[i].GetType() == "Varchar")
		{
			try
			{
				if (!(stoi(columns[i].GetLenghtStr()) >= str.length() || stoi(columns[i - 3].GetLenghtStr()) == 0))
				{
					veryfication = false;
				}else if (str.at(0) != '\"' )
				{
					veryfication = false;
				}
				else
				{
					commandParts[i] = cutBetween(commandParts[i], "\"");
				}
			}
			catch (exception e)
			{
				veryfication = false;
			}
		}
		else if (columns[i].GetType() == "Integer")
		{
			try
			{
				stoi(str);
			}
			catch (exception e)
			{
				veryfication = false;
			}
		}
		else if (columns[i].GetType() == "Float")
		{
			try
			{
				stof(str);
			}
			catch (exception e)
			{
				veryfication = false;
			}
		}
		else if (columns[i].GetType() == "Boolen")
		{
			if (str.find("TRUE") == string::npos && str.find("FALSE") == string::npos)
			{
				veryfication = false;
			}
		}

		if (veryfication == false)
		{
			cout << "insertion problem" << endl;
			return false;
		}
	}

	return addToFile(tableName , columns , commandParts);
}

bool displayTable(vector<string> commandParts)
{
	commandParts = trimVector(commandParts);
	string tableName = commandParts[commandParts.size()-1];
	
	if (fileExists(tableName + ".xml"))
	{
		vector<Column> columns = getTableTemplate(tableName);
		//commandParts[0] = throwAwayFirstWords(commandParts[0], 3);
		commandParts = trimVector(commandParts);
		commandParts = cutStaringSpaces(commandParts);
		vector<string> fileContent = loadFileToVector(tableName);

		bool columnExists = false;
		for (int i = 0; i < columns.size(); i++)
		{
			for (int j = 1; j < commandParts.size() - 2; j++)
			{
				if (commandParts[1] == "*" || trimString(commandParts[j]) == columns[i].GetName())
				{
					columnExists = true;
					break;
				}
			}
		}
		if (columnExists == false)
		{
			cout << "there is no column named " << commandParts[1] << endl;
			return false;
		}

		for (int i = 0; i < columns.size(); i++)
		{
			for (int j = 1; j < commandParts.size() - 2; j++)
			{
				if (commandParts[1] == "*" || trimString(commandParts[j]) == columns[i].GetName())
				{
					cout << columns[i].GetName() << ", ";
				}
			}
		}
		cout << endl;

		for (int i = 0 ; i < fileContent.size();i++)
		{
			if (fileContent[i].find("<item>") != string::npos)
			{
				i++;
				for (int j = 0; j < columns.size(); j++)
				{					
					for (int z = 1; z < commandParts.size() - 2; z++)
					{
						if (commandParts[1] == "*" || trimString(commandParts[z]) == columns[j].GetName())
						{
							cout << cutBetween(fileContent[i], ">", "</") << ", ";
						}
					}
					i++;
				}
				cout << endl;
			}
		}
		return true;
	}
	else
	{
		cout << "there is no table named " << tableName << endl;
		return false;
	}
}

bool dropData(vector<string> commandParts)
{
	commandParts = trimVector(commandParts);
	string tableName = commandParts[commandParts.size() - 1];
	tableName = tableName ;
	vector<string>fileContent = loadFileToVector(tableName);

	ofstream myfile;
	myfile.open(tableName + ".xml");
	bool cut = false;

	for (int i = 0; i < fileContent.size(); i++)
	{
		if (fileContent[i].find("</data>") != string::npos)
		{
			cut = false;
			myfile << fileContent[i] << "\n";
		}
		else if (fileContent[i].find("<data>") != string::npos)
		{
			cut = true;
			myfile << fileContent[i] << "\n";
		}
		else if (cut == false)
			myfile << fileContent[i] << "\n";
	}

	myfile.close();
	return true;
}

bool dropTable(vector<string> commandParts)
{
	commandParts = trimVector(commandParts);
	string tableName = commandParts[commandParts.size() - 1] ;
	tableName = tableName + ".xml";
	const char * fileName = tableName.c_str() ;

	if (!fileExists(tableName))
		return false;

	if (remove(fileName) != 0)
		return false;
	else
		return true;
}
