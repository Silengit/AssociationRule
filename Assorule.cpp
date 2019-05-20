#include "Assorule.h"

//组合数的部分参考自https://blog.csdn.net/prstaxy/article/details/8748633
void combination_recursive(vector<vector<string>> &p_set,
	vector<string> &rec, const vector<string> &arr, int r, int k1, int k2)
{
	if (k1 == r)//输出当前序列
	{
		vector<string> tmp;
		for (int i = 0; i < r; i++)
		{
			tmp.push_back(rec[i]);
			//cout << rec[i] << " ";
		}
		p_set.push_back(tmp);
		//cout << endl;
	}
	else
		for (size_t i = k2; i < arr.size(); i++)
		{
			rec[k1] = arr[i]; //子序列赋值
			combination_recursive(p_set, rec, arr, r, k1 + 1, i + 1);//递归回溯
		}
}

void combination(vector<vector<string>> &p_set,
	vector<string> &rec, const vector<string> &arr)//输出n个元素的全部组合 
{
	for (size_t i = 1; i < arr.size(); i++)
		combination_recursive(p_set, rec, arr, i, 0, 0);
}

int find_support_of(vector<string> &items, map<vector<string>, int> &freq)
{
	return freq[items];
}

int find_asso_rule_of(map<vector<string>, int> &freq, double min_conf)
{
	int count = 0;

	for (auto &it1 : freq)
	{
		vector<vector<string>> p_set;
		vector<string> tmp(it1.first);
		combination(p_set, tmp, it1.first);
		tmp = it1.first;
		for (auto &p1 : p_set)
		{
			double support_t = it1.second;
			//find s
			double support_s = find_support_of(p1, freq);
			double confidence = support_t / support_s;
			if (confidence >= min_conf)
			{
				count++;
				sort(tmp.begin(), tmp.end());
				sort(p1.begin(), p1.end());
				vector<string> diff(tmp.size() - p1.size());
				set_difference(tmp.begin(), tmp.end(),
					p1.begin(), p1.end(), diff.begin());
				/*
				cout << "{ ";
				for (auto &t1 : p1)
				{
					cout << t1 << ", ";
				}
				cout << "} => { ";
				for (auto &t2 : diff)
					cout << t2 << ", ";
				cout << "}, confidence = " << confidence << endl;
				*/
			}
		}
	}

	return count;
}