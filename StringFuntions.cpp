#include "StringFuntions.h"

bool startsWith(string mainStr, string matchStr)
{
	transform(mainStr.begin(), mainStr.end(), mainStr.begin(), ::tolower);
	transform(matchStr.begin(), matchStr.end(), matchStr.begin(), ::tolower);

	if (mainStr.find(matchStr) == 0)
		return true;
	else
		return false;
}

string cutBetween(string toCut, string leftStr, string rightStr)
{
	int left = toCut.find(leftStr) + leftStr.length();
	int right = toCut.find(rightStr) - left;
	string ret = toCut.substr(left, right);

	return ret;
}

string cutBetween(string toCut, string cutStr)
{
	int left = toCut.find(cutStr) + cutStr.length();
	int right = toCut.find_last_of(cutStr) - left;
	string ret = toCut.substr(left, right);

	return ret;
}

string trimString(string toCut)
{
	stringstream ret;

	for (int i = 0; i < toCut.length() ; i++)
	{
		if (toCut.at(i) != '(' && toCut.at(i) != ')' && toCut.at(i) != ':'  && toCut.at(i) != '<' && toCut.at(i) != '>' && toCut.at(i) != '/' && toCut.at(i) != '\'' && toCut.at(i) != '[' && toCut.at(i) != ']' && toCut.at(i) != ',')
		{
			ret << toCut.at(i);
		}
	}

	return ret.str();
}

string throwAwayFirstWords(string toCut, int amount)
{
	stringstream ret;
	vector<string> parts = partStringStreamToVector(toCut, ' ');
	parts = trimVector(parts);

	for (int i = amount; i < parts.size(); i++)
		ret << parts[i] << " ";

	return ret.str();
}
