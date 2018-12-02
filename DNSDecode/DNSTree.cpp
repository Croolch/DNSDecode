#include "DNSTree.h"
#include <iostream>
#include <stack>
using namespace std;


DNSTree::DNSTree()
{
	TreeHead = new TreeNode;
	if (TreeHead == NULL)
		throw "头节点分配出错";
}


DNSTree::~DNSTree()
{
}

void DNSTree::InitTree()
{
	char data[50];
	char IP[20];
	char flag = 'y';

	memset(data, '\0', 50);
	memset(IP, '\0', 20);
	while (flag == 'y')
	{
		//cout << "请输入域名：";
		cin >> data;
		//cout << "请输入IP：";
		cin >> IP;

		int i = 0, j = 0;
		char temp[50];
		stack<TreeNode*> s;
		while (1)
		{
			memset(temp, '\0', 50);
			temp[i++] = data[j++];                    //获取每个'.'之前或结束之前的字符串
			if (data[j] == '.' || data[j] == '\0')
			{
				TreeNode *N = new TreeNode;
				N->name = temp;						  //并存储到新节点
				s.push(N);							  //节点存入栈
				j++;
				i = 0;
			}
			if (data[j - 1] == '\0')
				break;
		}

		TreeNode *spnode;                  //栈顶节点
		TreeNode *tpnode = TreeHead;       //指向的头节点
		TreeNode *lastchild;			   //记录上一个节点
		//int stimes = 0;		 //栈的层次

		while (!s.empty())
		{
			spnode = s.top();
			
			//stimes++;
			if (!tpnode->child) {
				tpnode->child = spnode;
				tpnode = spnode;
				s.pop();
			}
			else
			{
				tpnode = tpnode->child;
				while (tpnode != NULL && spnode->name != tpnode->name) {
					lastchild = tpnode;
					tpnode = tpnode->brother;
				}
				if (!tpnode)
				{
					lastchild->brother = spnode;
					tpnode = spnode;
					
				}
				s.pop();
			}
		}
		tpnode->ip = IP;

		//cout << "继续吗？（y/n）" << endl;
		cin >> flag;
	}
}

void DNSTree::DNSInsert()
{
	string DNS, IP;
	cout << "请输入域名及IP地址：" << endl;
	cin >> DNS >> IP;

}

void DNSTree::DNSSearch()
{
	char data[50] = { '\0' };
	cout << "输入域名：";
	cin >> data;

	int i = 0, j = 0;
	char temp[50];
	stack<TreeNode*> s;
	while (1)
	{
		memset(temp, '\0', 50);
		temp[i++] = data[j++];                    //获取每个'.'之前或结束之前的字符串
		if (data[j] == '.' || data[j] == '\0')
		{
			TreeNode *N = new TreeNode;
			N->name = temp;						  //并存储到新节点
			s.push(N);							  //节点存入栈
			memset(temp, '\0', 50);
			j++;
			i = 0;
		}
		if (data[j - 1] == '\0')
			break;
	}

	TreeNode *spnode;                         //栈顶节点
	TreeNode *tpnode = TreeHead->child;       //指向的头节点
	TreeNode *lastchild;			          //记录上一个节点
	
	while (!s.empty())
	{
		spnode = s.top();
		while (tpnode != NULL && tpnode->name != spnode->name)
		{
			tpnode = tpnode->brother;
		}
		if (!tpnode)
		{
			break;
		}
		else
		{
			lastchild = tpnode;
			tpnode = tpnode->child;
		}
		s.pop();
	}
	//if (lastchild->ip != "0")
	//{
		cout << "IP为：" << lastchild->ip << endl;
	//}
	//else
	//{
	//	cout << "找不到服务器或发生DNS错误" << endl;
	//}
}

int main() {
	DNSTree T;
	T.InitTree();
	T.DNSSearch();
	return 0;
}