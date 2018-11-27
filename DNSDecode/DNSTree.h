#pragma once
#include <string>
using std::string;

typedef struct Node
{
	string Name;
	Node *child = NULL;
	Node *brother = NULL;
}*Tree, TreeNode;

class DNSTree
{
public:
	DNSTree();
	~DNSTree();
	void InitTree();
	void SaveTreeFile();
	void ReadTreeFile();
	void TreeToString();
	void DNSMatch();
	void DNSInsert();
	void Display();

private:
	Tree TreeHead;
};

void Menu();
