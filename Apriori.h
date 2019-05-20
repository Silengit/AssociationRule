#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Apriori 
{
private:
	vector<vector<string>> d;	//Dataset
	int alpha;	//Threshold
public:
	Apriori(vector<vector<string>> dataset, int threshold);
	void printDataSet();
	void process();
	vector<vector<string>> gen(vector<vector<string>> L_kminus1, int kminus1);
	bool has_infrequency_subset(vector<string> c, vector<vector<string>> L_kminus1);
};
