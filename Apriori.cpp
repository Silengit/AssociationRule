#include "Apriori.h"

Apriori::Apriori(vector<vector<string>> dataset, int threshold)
{
	d = dataset;
	alpha = threshold;
}

void Apriori::printDataSet()
{
	for (unsigned int i = 0; i < d.size(); i++) {
		for (unsigned int j = 0; j < d[i].size(); j++)
			cout << d[i][j] << " ";
		cout << endl;
	}
}

void Apriori::process()
{
	vector<vector<vector<string>>> L;	//set of frequency items sets
								//e.g. L[0] is 1-frequency set
	map<vector<string>, int> ctr_1;

	for (unsigned int i = 0; i < d.size(); i++) 
		for (unsigned int j = 0; j < d[i].size(); j++)
		{
			vector<string> item_1 = { d[i][j] };
			ctr_1[item_1] += 1;
		}

	vector<vector<string>> L_1;
	for (auto it = ctr_1.begin(); it != ctr_1.end(); it++) {
		if(it->second >= alpha)
			L_1.push_back(it->first);
	}
	L.push_back(L_1);


	vector<vector<vector<string>>> C;
	C.push_back(d); //here is not right, but C[0] is useless
	for (int k = 1; L[k - 1].size() != 0; k++)
	{
		vector<vector<string>> C_k = gen(L[k - 1], k - 1);
		map<vector<string>, int> ctr_k;

		//count C_k
		for (unsigned a = 0; a < d.size(); a++)
		{
			for (unsigned b = 0; b < C_k.size(); b++)
			{
				int find = 1;
				for (unsigned i = 0; i < C_k[b].size(); i++)
				{
					int flag = 0;
					for (unsigned j = 0; j < d[a].size(); j++)
					{
						if (C_k[b][i] == d[a][j]) {
							flag = 1;
							break;
						}
					}
					if (flag == 0) {
						find = 0;
						break;
					}
					else
						continue;
				}
				if (find == 1)
				{
					ctr_k[C_k[b]] += 1;
				}
			}
		}

		vector<vector<string>> L_k;
		for (auto it = ctr_k.begin(); it != ctr_k.end(); it++) {
			if (it->second >= alpha)
				L_k.push_back(it->first);
		}
		L.push_back(L_k);
	}

	int count = 0;
	for (unsigned i = 0; i < L.size(); i++)
	{
		for (unsigned j = 0; j < L[i].size(); j++)
		{
			count++;
			for (unsigned k = 0; k < L[i][j].size(); k++)
			{
				cout << L[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	cout << count << endl;
}

vector<vector<string>> Apriori::gen(vector<vector<string>> L_kminus1, int kminus1)
{
	vector<vector<string>> C_k;
	for (unsigned int i = 0; i < L_kminus1.size(); i++)
		for (unsigned int j = 0; j < L_kminus1.size(); j++)
		{
			int flag = 0;
			for (int k = 0; k < kminus1; k++)
				if (L_kminus1[i][k] != L_kminus1[j][k])
				{
					flag = 1;
					break;
				}
			if (flag == 0 && L_kminus1[i][kminus1] < L_kminus1[j][kminus1])
			{
				//connect L_kminus1[i] and  L_kminus1[j]
				vector<string> c{L_kminus1[i]};
				c.push_back(L_kminus1[j][kminus1]);
				if (!has_infrequency_subset(c, L_kminus1))
					C_k.push_back(c);
			}
		}
	return C_k;
}

bool Apriori::has_infrequency_subset(vector<string> c, vector<vector<string>> L_kminus1)
{
	for (unsigned int i = 0; i < c.size(); i++)
	{
		vector<string> s;
		for (unsigned int j = 0; j < c.size(); j++)
		{
			if (j != i)
				s.push_back(c[j]);
		}
		int find = 0;
		for (unsigned j = 0; j < L_kminus1.size(); j++)
		{
			int flag = 1;
			for (unsigned int k = 0; k < s.size(); k++)
				if (L_kminus1[j][k] != s[k])
				{
					flag = 0;
					break;
				}
			if (flag == 1) {
				find = 1;
				break;
			}
			else
				continue;
		}
		if (find == 0)
			return true;
	}
	return false;
}
