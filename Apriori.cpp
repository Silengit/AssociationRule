#include "Apriori.h"

Apriori::Apriori(vector<vector<string>> &dataset, int threshold, double confidence, int dummy)
{
	d = dataset;
	min_sup = threshold;
	min_conf = confidence;
	freq_item_set.clear();
	process(dummy);
}

void Apriori::printDataSet()
{
	for (auto &it1 : d)
	{
		for (auto &it2 : it1)
			cout << it2 << " ";
		cout << endl;
	}
}

void Apriori::process(int dummy)
{
	//set of frequency item set
	//e.g. L[0] is 1-frequency set
	vector<map<vector<string>, int>> L;	

	//counter of item
	map<vector<string>, int> ctr_1;

	//counter of frequency item set
	int fq_count = 0;

	for (auto &it1 : d)
		for (auto &it2 : it1)
			ctr_1[vector<string>{it2}] ++;

	//find L[0]
	map<vector<string>, int> L_1;
	for (auto &it1 : ctr_1) {
		if (it1.second >= min_sup) {
			fq_count++;
			L_1[it1.first] = it1.second;
			freq_item_set[it1.first] = it1.second;
		}
	}
	L.push_back(L_1);

	//iterate
	for (int k = 1; L[k - 1].size() != 0; k++)
	{
		vector<vector<string>> C_k = gen(L[k - 1], k - 1, dummy);
		map<vector<string>, int> ctr_k;

		for (auto &it1 : d) 
		{
			sort(it1.begin(), it1.end());
			for (auto &it2 : C_k)
				if (includes(it1.begin(), it1.end(), it2.begin(), it2.end()))
					ctr_k[it2] ++;
		}

		map<vector<string>, int> L_k;
		for (auto &it1 : ctr_k)
		{
			if (it1.second >= min_sup)
			{
				fq_count++;
				L_k[it1.first] = it1.second;
				freq_item_set[it1.first] = it1.second;
			}
		}
		L.push_back(L_k);
	}

	int rule_count = find_asso_rule_of(freq_item_set, min_conf);
	cout << "counter of frequency item set: "<< fq_count << endl;
	cout << "counter of association rule: " << rule_count << endl;
}

vector<vector<string>> Apriori::gen(map<vector<string>, int> &L_kminus1, int kminus1, int dummy)
{
	vector<vector<string>> C_k;
	for (auto &it1 : L_kminus1)
		for (auto &it2 : L_kminus1)
		{
			int flag = 0;
			for (int k = 0; k < kminus1; k++) 
			{
				if (it1.first[k] != it2.first[k])
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0 && it1.first[kminus1] < it2.first[kminus1])
			{
				//connect L_kminus1[i] and  L_kminus1[j]
				vector<string> c{ it1.first };
				c.push_back(it2.first[kminus1]);
				if (dummy == 0) 
				{
					if (!has_infrequency_subset(c, L_kminus1))
						C_k.push_back(c);
				}
				else
				{
					C_k.push_back(c);
				}
			}
		}
	return C_k;
}

bool Apriori::has_infrequency_subset(vector<string> &c, map<vector<string>, int> &L_kminus1)
{
	for (auto &it1 : c)
	{
		vector<string> s;
		for (auto &it2 : c)
			if (it1 != it2)
				s.push_back(it2);

		if (L_kminus1[s] == 0)
			return true;
	}
	return false;
}
