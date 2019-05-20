#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
void combination_recursive(vector<vector<string>> &p_set,
	vector<string> &rec, const vector<string> &arr, int r, int k1, int k2);
void combination(vector<vector<string>> &p_set,
	vector<string> &rec, const vector<string> &arr);//输出n个元素的全部组合 
int find_support_of(vector<string> &items, map<vector<string>, int> &freq);//找到特定串的支持计数
int find_asso_rule_of(map<vector<string>, int> &freq, double min_conf);//找到满足最小置信度的关联规则