#pragma once
#include "Assorule.h"
#include <tuple>
using namespace std;

typedef pair<string, int> PAIR;

class TreeNode {
public:
	PAIR item;
	TreeNode *parent;
	TreeNode *first_child;
	TreeNode *sibling;
	TreeNode(string name)
	{
		item.first = name;
		item.second = 1;
		parent = NULL;
		first_child = NULL;
		sibling = NULL;
	}
	void increase()
	{
		item.second += 1;
	}
	void parent_is(TreeNode *p)
	{
		parent = p;
	}
	void fisrt_child_is(TreeNode *child)
	{
		first_child = child;
	}
	void sibling_is(TreeNode *sib)
	{
		sibling = sib;
	}
	bool find_it(string child_name)
	{
		TreeNode *child = first_child;
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
	TreeNode *root;
public:
	Tree()
	{
		string root_name("null");
		root = new TreeNode(root_name);
	}
	TreeNode *get_root()
	{
		return root;
	}
	TreeNode *add_child(TreeNode *parent, string child_name, 
		vector<tuple<string, int, vector<TreeNode*>>> &item_head)
	{
		TreeNode *child;
		if (!parent->find_it(child_name))
		{
			child = new TreeNode(child_name);
			if (parent->first_child == NULL)
			{
				parent->fisrt_child_is(child);
				child->parent_is(parent);
			}
			else
			{
				TreeNode *last_child = parent->first_child;
				while (last_child->sibling)
					last_child = last_child->sibling;
				last_child->sibling = child;
				child->parent_is(parent);
			}
			for (auto &it : item_head)
			{
				if (get<0>(it) == child_name)
				{
					get<2>(it).push_back(child);
				}
			}
			return child;
		}
		else
		{
			child = parent->first_child;
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
		return child;
	}
	void print_node(TreeNode *t)
	{
		if (t != NULL)
		{
			cout << t->item.first << " " << t->item.second << " ";
			if (t->item.first != "null")
			{
				cout << t->parent->item.first << endl;
			}
			else
				cout << endl;
			TreeNode *child = t->first_child;
			print_node(child);
			TreeNode *sib = t->sibling;
			print_node(sib);
		}
	}
	void print()
	{
		print_node(root);
	}
};

class FpGrowth
{
public:
	Tree fptree;
	vector<vector<string>> d;	//Dataset
	int min_sup;	//min support
	double min_conf;	//min confidence
	vector<tuple<string, int, vector<TreeNode*>>> item_head;

	FpGrowth(vector<vector<string>> &dataset, int threshold, double conf);
	vector<PAIR> fpsort();
	void resortDataSet(vector<PAIR> L_1);
	void gen();
	void print_tree();
	
};

void grow(FpGrowth &f, vector<string> &prefix, int &fq_ctr, map<vector<string>, int> &freq);
void fpgrowth(FpGrowth &f);