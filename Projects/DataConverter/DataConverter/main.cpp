#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector <string> fileNames;

bool readFileNames()
{
	ifstream _in("../../../Data/RECORDS.txt");

	if (!_in.is_open())
	{
		cout << "File is not open\n";

		return false;
	}

	string name;

	while (_in >> name)
	{
		fileNames.push_back(name);
	}

	return true;
}

bool convertToTxt(string pathFrom, string pathTo)
{
	ifstream _in(pathFrom);
	ofstream _out(pathTo);

	if (!_in.is_open())
	{
		cout << "File _in is not open\n";

		return false;
	}

	if (!_out.is_open())
	{
		cout << "File _out is not open\n";

		return false;
	}

	string data, tmp;
	_in >> data;

	vector <string> separatdData;
	for (auto it : data)
	{
		if (it == ',')
		{
			separatdData.push_back(tmp);
			tmp = "";
		}
		else
		{
			tmp += it;
		}
	}
	separatdData.push_back(tmp);

	for (auto value : separatdData)
	{
		_out << value << "\n";
	}

	cout << pathFrom << " is ok " << separatdData.size() << "\n";

	_out.close();
}

int main()
{
	if (!readFileNames())
	{
		return 0;
	}

	for (auto name : fileNames)
	{
		convertToTxt("../../../Data/CSV/" + name + ".csv", "../../../Data/TXT/" + name + ".txt");
	}


	return 0;
}