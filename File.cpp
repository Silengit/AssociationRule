#include "File.h"

vector<vector<string>> read_Groceries()
{
	ifstream in_file("Data//Groceries.txt", ios::in);
	vector<vector<string>> dataset;

	if (!in_file.is_open())
	{
		cout << "未成功打开文件" << endl;
		exit(-1);
	}
	while (!in_file.eof())
	{
		string line;
		vector<string> item_list;
		string item;
		getline(in_file, line);
		int begin = line.find("{") + 1;
		int end = line.find("}") - 1;
		string items(line, begin, end-begin+1);
		istringstream iss(items);
		while (getline(iss, item, ','))
			item_list.push_back(item);
		dataset.push_back(item_list);
	}
	in_file.close();
	return dataset;
}

vector<vector<string>> read_Linux(int n)
{
	if (n < 0 || n > 8)
	{
		cout << "文件不存在" << endl;
		exit(-1);
	}
	char s1[17] = "Data//Unix//USER";
	char s2[2] = { 0 };
	char s3[29] = "//sanitized_all.981115184025";
	char file_name[50];
	sprintf_s(s2, "%d", n);
	sprintf_s(file_name, "%s%s%s", s1, s2, s3);
	ifstream in_file(file_name, ios::in);
	vector<vector<string>> dataset;

	if (!in_file.is_open())
	{
		cout << "未成功打开文件" << endl;
		exit(-1);
	}
	while (!in_file.eof())
	{
		string line;
		vector<string> item_list;
		getline(in_file, line);
		if (line == "**SOF**")
		{
			getline(in_file, line);
			while (line != "**EOF**")
			{
				//cout << line << endl;
				item_list.push_back(line);
				getline(in_file, line);
			}
		}
		if(item_list.size() != 0)
			dataset.push_back(item_list);
	}
	//cout << dataset.size() << endl;
	in_file.close();
	return dataset;
}