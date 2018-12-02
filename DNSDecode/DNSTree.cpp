#include "DNSTree.h"
#include <iostream>
#include <stack>
using namespace std;


DNSTree::DNSTree()
{
	TreeHead = new TreeNode;
	if (TreeHead == NULL)
		throw "ͷ�ڵ�������";
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
		//cout << "������������";
		cin >> data;
		//cout << "������IP��";
		cin >> IP;

		int i = 0, j = 0;
		char temp[50];
		stack<TreeNode*> s;
		while (1)
		{
			memset(temp, '\0', 50);
			temp[i++] = data[j++];                    //��ȡÿ��'.'֮ǰ�����֮ǰ���ַ���
			if (data[j] == '.' || data[j] == '\0')
			{
				TreeNode *N = new TreeNode;
				N->name = temp;						  //���洢���½ڵ�
				s.push(N);							  //�ڵ����ջ
				j++;
				i = 0;
			}
			if (data[j - 1] == '\0')
				break;
		}

		TreeNode *spnode;                  //ջ���ڵ�
		TreeNode *tpnode = TreeHead;       //ָ���ͷ�ڵ�
		TreeNode *lastchild;			   //��¼��һ���ڵ�
		//int stimes = 0;		 //ջ�Ĳ��

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

		//cout << "�����𣿣�y/n��" << endl;
		cin >> flag;
	}
}

void DNSTree::DNSInsert()
{
	string DNS, IP;
	cout << "������������IP��ַ��" << endl;
	cin >> DNS >> IP;

}

void DNSTree::DNSSearch()
{
	char data[50] = { '\0' };
	cout << "����������";
	cin >> data;

	int i = 0, j = 0;
	char temp[50];
	stack<TreeNode*> s;
	while (1)
	{
		memset(temp, '\0', 50);
		temp[i++] = data[j++];                    //��ȡÿ��'.'֮ǰ�����֮ǰ���ַ���
		if (data[j] == '.' || data[j] == '\0')
		{
			TreeNode *N = new TreeNode;
			N->name = temp;						  //���洢���½ڵ�
			s.push(N);							  //�ڵ����ջ
			memset(temp, '\0', 50);
			j++;
			i = 0;
		}
		if (data[j - 1] == '\0')
			break;
	}

	TreeNode *spnode;                         //ջ���ڵ�
	TreeNode *tpnode = TreeHead->child;       //ָ���ͷ�ڵ�
	TreeNode *lastchild;			          //��¼��һ���ڵ�
	
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
		cout << "IPΪ��" << lastchild->ip << endl;
	//}
	//else
	//{
	//	cout << "�Ҳ�������������DNS����" << endl;
	//}
}

int main() {
	DNSTree T;
	T.InitTree();
	T.DNSSearch();
	return 0;
}