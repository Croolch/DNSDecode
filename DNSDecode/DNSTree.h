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
	void SaveTreeFile();	//�������ڴ���д���µ�������ip��Ϣ�ĺ���
	void ReadTreeFile();
	void DNSSearch();
	void DNSDelete();
	void DNSInsert(char data[], char IP[]);
	//void InsertFunc();
	void Display();
	void PrintT(Tree p, int n);
	void TreeToString();

private:
	Tree TreeHead;
};

void Menu();
