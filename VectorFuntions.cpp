#include "VectorFuntions.h"

bool fileExists(string filename)
{
	ifstream ifile(filename);
	return (bool)ifile;
}

vector<string> cutStaringSpaces(vector<string> toCut)
{
	vector<string> ret;
	for (string str : toCut)
	{	
		if (str.length() > 0 && str.at(0) == ' ')
		{
			stringstream ss;
			for (int i = 1; i < str.length(); i++)
			{
				ss << str.at(i);
			}
			ret.push_back(ss.str());
		}else
		{
			ret.push_back(str);
		}
	}
	return ret;
}

vector<string> partStringStreamToVector(string text, char separator)
{
	stringstream ss(text);
	string segment;
	vector<string> retVector;

	while (getline(ss, segment, separator))
	{
		retVector.push_back(segment);
	}

	return retVector;
}

vector<string> trimVector(vector<string> inVector)
{
	vector<string> cleanVector;

	for (int i = 0; i < inVector.size(); i++)
	{
		string tmp = inVector[i];

		if (tmp != "(" && tmp != ")" && tmp != ":" && tmp != "" && tmp != "<" && tmp != ">" && tmp != "/" && tmp != "\"")
			cleanVector.push_back(tmp);
	}
	return cleanVector;
}

vector<string> loadFileToVector(string fileName)
{
	vector<string> ret;
	ifstream myfile;
	string line;

	if (fileExists(fileName + ".xml"))
	{
		myfile.open(fileName + ".xml");
		while (getline(myfile, line))
		{
			ret.push_back(line);
		}
	}

	return ret;
}
