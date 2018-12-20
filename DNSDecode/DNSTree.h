#pragma once
#include <string>
using std::string;

#define Data_Lenth 50

#define Ip_Lenth 20

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
	void SaveTreeFile();	//用于向内存中写入新的域名，ip信息的函数
	void ReadTreeFile();
	void DNSSearch();
	void DNSDelete(char data[]);
	void DNSInsert(char data[], char IP[]);
	//void InsertFunc();
	void Display();
	void PrintT(Tree p, int n);
	void Destroy();
	//bool Repeat(char data[]);

private:
	Tree TreeHead;
};

void Menu();
