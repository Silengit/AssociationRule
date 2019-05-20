#pragma once
#include "Assorule.h"

class Apriori 
{
private:
	vector<vector<string>> d;	//Dataset
	int min_sup;	//min support
	double min_conf;	//min confidence
	map<vector<string>, int> freq_item_set;		
public:
	Apriori(vector<vector<string>> &dataset, int threshold, double confidence, int dummy);
	void printDataSet();
	void process(int dummy);
	vector<vector<string>> gen(map<vector<string>, int> &L_kminus1, int kminus1, int dummy);
	bool has_infrequency_subset(vector<string> &c, map<vector<string>, int> &L_kminus1);
};
