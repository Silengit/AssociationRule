#include "FpGrowth.h"

FpGrowth::FpGrowth(vector<vector<string>> dataset, int threshold)
{
	d = dataset;
	alpha = threshold;
}

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

vector<PAIR> FpGrowth::fpsort()
{
	map<string, int> ctr_1;

	for (unsigned int i = 0; i < d.size(); i++)
		for (unsigned int j = 0; j < d[i].size(); j++)
		{
			string item_1 = d[i][j];
			ctr_1[item_1] += 1;
		}

	vector<PAIR> ctr_1_vec(ctr_1.begin(), ctr_1.end());
	sort(ctr_1_vec.begin(), ctr_1_vec.end(), CmpByValue());

	return ctr_1_vec;
}

void FpGrowth::resortDataSet(vector<PAIR> L_1)
{
	vector<vector<PAIR>> weight_d;

	for (auto& it1 : d)
	{
		map<string, int> weight_item;
		for (auto& it2 : it1)
		{
			for (auto& it3 : L_1)
			{
				if (it2 == it3.first)
					weight_item[it2] = it3.second;
			}
		}
		if (weight_item.size() != 0)
		{
			vector<PAIR> item_vec(weight_item.begin(), weight_item.end());
			sort(item_vec.begin(), item_vec.end(), CmpByValue());
			weight_d.push_back(item_vec);
		}
	}

	d.clear();

	for (auto& it1 : weight_d)
	{
		vector<string> item;
		for (auto& it2 : it1)
			item.push_back(it2.first);
		d.push_back(item);
	}

/*	
	for (auto& it1 : d) {
		for (auto& it2 : it1)
			cout << it2 << " ";
		cout << endl;
	}
*/
}

void FpGrowth::gen()
{
	fptree = Tree();

	vector<PAIR> ctr_1 = fpsort();

	for (auto& it : ctr_1)
		cout << it.first << " " << it.second << endl;

	vector<PAIR> L_1;
	for (auto& it : ctr_1) 
	{
		if (it.second >= alpha)
			L_1.push_back(it);
	}

	resortDataSet(L_1);

	for (auto& it1 : d) 
	{
		tNode *parent = fptree.get_root();
		for (auto& it2 : it1)
		{
			fptree.grow(parent, it2);
		}
	}

}

void FpGrowth::dine()
{

}