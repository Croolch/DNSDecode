#pragma once
#include <string>
using std::string;

typedef struct Node
{
	string name;
	string ip = "0";
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
	void DNSSearch();
	void DNSInsert();
	void Display();

private:
	Tree TreeHead;
};

void Menu();
