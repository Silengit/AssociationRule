#include "Apriori.h"
#include "FpGrowth.h"
#include "File.h"
#include <fstream>
#include<ctime>
using namespace std;
#define CLOCKS_PER_SEC ((clock_t)1000)

int main()
{	
	vector<vector<string>> dataset = read_Linux(6);
	/*
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
	*/

	clock_t startTime, endTime1, endTime2, endTime3;
	startTime = clock();//计时开始
	cout << "dummy Apriori: " << endl;
	Apriori a(dataset, 200, 0.95, 1);
	endTime1 = clock();//计时结束1
	cout << "dummy Apriori's run time is: " << (double)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
	cout << endl;
	cout << "Apriori: " << endl;
	Apriori b(dataset, 200, 0.95, 0);
	endTime2 = clock();//计时结束1
	cout << "Apriori's run time is: " << (double)(endTime2 - endTime1) / CLOCKS_PER_SEC << "s" << endl;
	cout << endl;
	cout << "FpGrowth: " << endl;
	FpGrowth f(dataset, 200, 0.95);
	fpgrowth(f);
	endTime3 = clock();//计时结束2
	cout << "FpGrowth's run time is: " << (double)(endTime3 - endTime2) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
}
