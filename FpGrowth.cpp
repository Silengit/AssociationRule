#include "FpGrowth.h"

FpGrowth::FpGrowth(vector<vector<string>> &dataset, int threshold, double conf)
{
	d = dataset;
	min_sup = threshold;
	min_conf = conf;
	gen();
}

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

vector<PAIR> FpGrowth::fpsort()
{
	map<string, int> ctr_1;

	for (auto &it1: d)
		for (auto &it2 : it1)
			ctr_1[it2] += 1;

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
}

void FpGrowth::gen()
{
	fptree = Tree();

	vector<PAIR> ctr_1 = fpsort();

	vector<PAIR> L_1;
	for (auto& it : ctr_1)
	{
		if (it.second >= min_sup)
		{
			L_1.push_back(it);
			vector<TreeNode*> tmp;
			tuple<string, int, vector<TreeNode*>> item(it.first, it.second, tmp);
			item_head.push_back(item);
		}
	}

	resortDataSet(L_1);

	for (auto& it1 : d)
	{
		TreeNode *parent = fptree.get_root();
		for (auto& it2 : it1)
		{
			parent = fptree.add_child(parent, it2, item_head);
		}
	}
}

void grow(FpGrowth &f, vector<string> &prefix, int &fq_ctr, map<vector<string>, int> &freq)
{
	for (auto it1 : f.item_head)
	{
		vector<vector<string>> condition_d;
		vector<string> new_pre(prefix);
		new_pre.push_back(get<0>(it1));

		vector<string> tmp;
		//cout << "{";
		for (auto &it0 : new_pre)
		{
			tmp.push_back(it0);
			//cout << it0 << ", ";
		}
		//cout << "}: " << get<1>(it1) << endl;
		fq_ctr++;
		sort(tmp.begin(), tmp.end());
		freq[tmp] = get<1>(it1);

		for (auto it2 : get<2>(it1))
		{
			vector<string> condpatbase;
			//cout << it2->item.first << " -> ";
			TreeNode *p = it2->parent;
			while (p->item.first != "null")
			{
				condpatbase.push_back(p->item.first);
				//cout << p->item.first << " -> ";
				p = p->parent;
			}
			//cout <<"null"<<endl;
			if (condpatbase.size() != 0)
			{
				for (int i = 0; i < it2->item.second; i++)
				{
					condition_d.push_back(condpatbase);
				}
			}
		}
		 
		FpGrowth conditionFpTree(condition_d, f.min_sup, f.min_conf);
		if (conditionFpTree.fptree.get_root()->first_child != NULL) 
			grow(conditionFpTree, new_pre, fq_ctr, freq);
	}
}

void fpgrowth(FpGrowth &f)
{
	vector<string> null;
	int count1 = 0;
	map<vector<string>, int> Freq_item_set;
	grow(f, null, count1, Freq_item_set);
	int count2 = find_asso_rule_of(Freq_item_set, f.min_conf);

	cout << "counter of frequency item set: " << count1 << endl;
	cout << "counter of association rule: " << count2 << endl;
}

void FpGrowth::print_tree()
{
	fptree.print();
}