#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

typedef pair<string, int> PAIR;

class tNode {
public:
	PAIR item;
	tNode *first_child;
	tNode *sibling;
	tNode(string name)
	{
		item.first = name;
		item.second = 1;
		first_child = NULL;
		sibling = NULL;
	}
	void increase()
	{
		item.second += 1;
	}
	void fisrt_child_is(tNode *child)
	{
		first_child = child;
	}
	void sibling_is(tNode *sib)
	{
		sibling = sib;
	}
	bool find_it(string child_name)
	{
		tNode *child = first_child;
		while (child)
		{
			if (child->item.first == child_name)
				return true;
			child = child->sibling;
		}
		return false;
	}
};

class Tree
{
private:
	tNode *root;
public:
	Tree()
	{
		string root_name("null");
		root = new tNode(root_name);
	}
	tNode *get_root()
	{
		return root;
	}
	void grow(tNode *parent, string child_name)
	{
		if (!parent->find_it(child_name))
		{
			tNode *child = new tNode(child_name);
			parent->fisrt_child_is(child);
		}
		else
		{
			tNode *child = parent->first_child;
			while (child)
			{
				if (child->item.first == child_name)
				{
					child->item.second += 1;
					break;
				}
				child = child->sibling;
			}
		}
	}
};

class FpGrowth
{
private:
	vector<vector<string>> d;	//Dataset
	int alpha;	//Threshold
	Tree fptree;
public:
	FpGrowth(vector<vector<string>> dataset, int threshold);
	vector<PAIR> fpsort();
	void resortDataSet(vector<PAIR> L_1);
	void gen();
	void dine();
};
