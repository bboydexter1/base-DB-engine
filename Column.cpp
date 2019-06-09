#include "Column.h"

	Column::Column()
	{
	}
	Column::Column(string inName, string inType)
	{
		name = inName;

		if (inType.find(",") != string::npos)
		{
			inType.erase(inType.find(","));
		}

		if (inType.find("(") != string::npos)
		{
			int left = inType.find("(");
			int right = inType.find(")");

			string number = inType.substr(left + 1, right - left);

			inType.erase(left, right);

			lenght = stoi(number);
		}

		if (inType == "Boolean" || inType == "Integer" || inType == "Float" || inType == "Varchar")
			type = inType;
		else
			cout << "wrong column type in column " << name << endl;
	}

	string Column::GetName()
	{
		return name;
	}
	string Column::GetType()
	{
		return type;
	}
	string Column::GetLenghtStr()
	{
		if (lenght > 0)
			return to_string(lenght);
		else
			return "";
	}
