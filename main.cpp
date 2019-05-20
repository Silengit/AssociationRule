#include "Apriori.h"
#include "FpGrowth.h"
#include <fstream>
using namespace std;
int main()
{
	
	/*string item;
	const char *s = new char[1000];
	ifstream in_file("E:\\Study\\DataMining\\hw\\assign_2\\dataset\\test.txt", ios::in);
	vector<vector<string>> dataset;

	if (!in_file.is_open())
	{
		cout << "未成功打开文件" << endl;
	}
	while (!in_file.eof())
	{
		vector<string> item_list;
		getline(in_file, item);
		s = item.data();
		char *index = new char[10];
		int i;
		for (i = 0; s[i] != '\t'; i++)
			index[i] = s[i];
		index[i] = '\0';
		delete(index);

		char *x = new char[100];
		int j;
		
		for (j = 0, i = i + 2; s[i] != ','&&s[i] != '}'; i++, j++)
			x[j] = s[i];
		x[j] = '\0';
		string y = x;
		item_list.push_back(y);

		while (s[i] != '}')
		{
			for (j = 0, i = i+1; s[i] != ','&&s[i] != '}'; i++, j++)
				x[j] = s[i];
			x[j] = '\0';
			string y = x;
			item_list.push_back(y);
		}

		dataset.push_back(item_list);
		delete(x);
	}
	in_file.close();
	
	for (auto it1 = dataset.begin(); it1 != dataset.end(); it1++)
	{
		for (auto it2 = it1->begin(); it2 != it1->end(); it2++)
			cout << *it2 << " ";
		cout << endl;
	}
	*/
	vector<string> item1{ "l1","l2","l5" };
	vector<string> item2 = { "l2","l4" };
	vector<string> item3 = { "l2","l3" };
	vector<string> item4 = { "l1","l2","l4" };
	vector<string> item5 = { "l1","l3" };
	vector<string> item6 = { "l2","l3" };
	vector<string> item7 = { "l1","l3" };
	vector<string> item8 = { "l1","l2","l3","l5" };
	vector<string> item9 = { "l1","l2","l3" };
	vector<vector<string>> dataset = { item1,item2,item3,item4,item5,item6,item7,item8,item9 };

	//Apriori a(dataset, 200);
	//a.process();
	FpGrowth f(dataset, 2);
	f.gen();

	system("pause");
}

