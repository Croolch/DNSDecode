#pragma once
#include "DNSTree.h"
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <iomanip>
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
	char flag = 'y';
	while (flag == 'y')
	{	
		SaveTreeFile();
		//cout << "�����𣿣�y/n��" << endl;
		cin >> flag;
	}
}

void DNSTree::DNSInsert(char data[],char IP[])		//����������ip�������ڴ��
{

	int i = 0, j = 0;
	char temp[50];
	memset(temp, '\0', 50);
	stack<TreeNode*> s;
	while (1)
	{	
		temp[i++] = data[j++];                    //��ȡÿ��'.'֮ǰ�����֮ǰ���ַ���
		if (data[j] == '.' || data[j] == '\0')
		{
			TreeNode *N = new TreeNode;
			N->name = temp;						  //���洢���½ڵ�
			s.push(N);							  //�ڵ����ջ
			j++;
			i = 0;
			memset(temp, '\0', 50);
		}
		if (data[j - 1] == '\0')
			break;
	}
	TreeNode *spnode = NULL;                  //ջ���ڵ�
	TreeNode *tpnode = TreeHead;       //ָ���ͷ�ڵ�
	TreeNode *lastchild = NULL;			   //��¼��һ���ڵ�
	while (!s.empty())
	{
		spnode = s.top();
		if (!tpnode->child) {//�жϵ�ǰ��ε���һ�����޽ڵ㣬��������
			tpnode->child = spnode;
			tpnode = spnode;
		}
		else
		{//���нڵ��������һ��ֱ���ҵ���ͬ�ڵ�
			tpnode = tpnode->child;
			while (tpnode != NULL && spnode->name != tpnode->name) {
				lastchild = tpnode;//�ҵ���ͬ��ε���������û����ͬ�ڵ���tpnodeΪNULL
				tpnode = tpnode->brother;
			}
			if (!tpnode)//tpnodeΪNULL������������ڵ�
			{
				lastchild->brother = spnode;
				tpnode = spnode;
			}
		}
		s.pop();
	}
	tpnode->ip = IP;//��ip�������һ��ڵ���
}

void DNSTree::DNSSearch()		//����һ�����������ڴ�Ѱ�Ҷ�Ӧ��ip��ַ
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

	TreeNode *spnode = NULL;                         //ջ���ڵ�
	TreeNode *tpnode = TreeHead->child;       //ָ���ͷ�ڵ�
	TreeNode *lastchild = NULL;			          //��¼��һ���ڵ�

	while (!s.empty())
	{
		spnode = s.top();
		while (tpnode != NULL && tpnode->name != spnode->name)
		{//�ҵ���ͬ��ε�������������ΪNULL
			tpnode = tpnode->brother;
		}
		if (!tpnode)//ΪNULL������������ʧ��
		{
			break;
		}
		else//��ΪNULL���������һ�㣬����ƥ����һ�������
		{
			lastchild = tpnode;
			tpnode = tpnode->child;
		}
		s.pop();
	}
	if (lastchild->ip != "0")
	{
		cout << "IPΪ��" << lastchild->ip << endl;
	}
	else
	{
		cout << "�Ҳ�������������DNS����" << endl;
	}
}

void DNSTree::SaveTreeFile()	//�������ļ���д���µ�������ip��Ϣ�ĺ���	/*���ߣ������*/
{
	char data[Data_Lenth];
	char IP[Ip_Lenth];		//���������������ֱ�������ʱ���漴��д���ļ���ip��ַ������
	memset(data, '\0', 50);
	memset(IP, '\0', 20);	//��ʼ��

	cout << "������������";	//����������
	cin >> data;
	cout << "������IP��";
	cin >> IP;

	fstream fbin("info.txt", ios::binary | ios::out | ios::app);	//�Զ����Ʒ�ʽ���ļ������ļ�ĩβ�����Ϣ
	if (!fbin) {													//�ļ���ȡ��ȷ�Ե��ж�
		cout << "�ļ���ȡ��������" << endl;
		return;
	}
	fbin.write(data, Data_Lenth);	//����Ϣд���ļ�
	fbin.write(IP, Ip_Lenth);

	fbin.close();			//�ر��ļ���
	DNSInsert(data, IP);
	cout << "д����ɣ�" << endl;
	return;
}

void DNSTree::ReadTreeFile()	//���ڴ��ļ��ж�ȡ������ip��ַ����Ϣ���ڴ��еĺ���	/*���ߣ������*/
{
	char data[Data_Lenth];
	char IP[Ip_Lenth];		//���������������ֱ�������ʱ���漴��д���ļ���ip��ַ������
	memset(data, '\0', Data_Lenth);
	memset(IP, '\0', Ip_Lenth);	//��ʼ��

	fstream fbin("info.txt", ios::binary | ios::in | ios::out);		//�Զ����Ʒ�ʽ���ļ���ָ��ָ���ļ���ʼ��
	if (!fbin) {													//�ļ���ȡ��ȷ�Ե��ж�
		cout << "�ļ���ȡ��������" << endl;
		return;
	}
	int i = 0;			//���ڿ���ѭ���ı���
	while (fbin.peek() != EOF)
	{
		memset(data, '\0', Data_Lenth);
		memset(IP, '\0', Ip_Lenth);
		fbin.seekg(i*(Data_Lenth + Ip_Lenth), ios::beg);	//���ڶ�λ���λ��
		fbin.read(data, Data_Lenth);
		fbin.read(IP, Ip_Lenth);		//���ζ�ȡ�Ѿ�д���ļ��е���Ϣ
		DNSInsert(data, IP);			//����insert����������ʱ�����е���Ϣд�����ṹ��
		i++;						//i�Լӣ�������ȡָ���ƶ�
		cout << i << "  ";
	}
	fbin.close();

}

void DNSTree::Display() {
	PrintT(TreeHead, 0);

}

void DNSTree::PrintT(Tree p, int n) {
	if (p == NULL)
		return;
	for (int i = 0; i < n; i++)
	{
		cout << "       ";
	}
	cout << p->name << endl;
	PrintT(p->child, n + 1);
	PrintT(p->brother, n);
}

//void DNSTree::InsertFunc() {
//	char data[Data_Lenth];
//	char IP[Ip_Lenth];
//	memset(data, '\0', Data_Lenth);
//	memset(IP, '\0', Ip_Lenth);
//	cout << "������������";
//	cin >> data;
//	cout << "������IP��";
//	cin >> IP;
//	DNSInsert(data, IP);
//}

void DNSTree::DNSDelete() {
	char data[Data_Lenth];
	int i = 0, j = 0;
	char temp[50];
	memset(temp, '\0', 50);
	memset(data, '\0', 50);
	stack<TreeNode*> s;
	stack<TreeNode*> deStack;
	cout << "������Ҫɾ����������";
	cin >> data;
	
	while (1)									
	{
		temp[i++] = data[j++];                    //��ȡÿ��'.'֮ǰ�����֮ǰ���ַ���
		if (data[j] == '.' || data[j] == '\0')
		{
			TreeNode *N = new TreeNode;
			N->name = temp;						  //���洢���½ڵ�
			s.push(N);							  //�ڵ����ջ
			j++;
			i = 0;
			memset(temp, '\0', 50);
		}
		if (data[j - 1] == '\0')
			break;
	}
	TreeNode *spnode = NULL;                  //ջ���ڵ�
	TreeNode *tpnode = TreeHead->child;       //ָ���ͷ�ڵ�ĺ���
	TreeNode *lastchild = NULL;			   //��¼��һ���ڵ�
	deStack.push(TreeHead);
	while (!s.empty())
	{
		spnode = s.top();
		while (tpnode != NULL && tpnode->name != spnode->name)
		{//�ҵ���ͬ��ε�������������ΪNULL
			tpnode = tpnode->brother;
		}
		if (!tpnode)//ΪNULL������������ʧ��
		{
			break;
		}
		else//��ΪNULL���������һ�㣬����ƥ����һ�������
		{
			deStack.push(tpnode);
			lastchild = tpnode;
			tpnode = tpnode->child;
		}
		s.pop();
	}
	if (deStack.size() != s.size() + 1)
	{
		cout << "ɾ������" << endl;
		return;
	}
	while (1)
	{
		if (deStack.top() == TreeHead)
		{
			break;
		}
		spnode = deStack.top();//ָ��Ҫɾ���ĵײ�ڵ�
		deStack.pop();
		tpnode = deStack.top();
		lastchild = tpnode;
		tpnode = tpnode->child;
		while (tpnode != NULL && tpnode->name != spnode->name)
		{//�ҵ���ͬ��ε�������������ΪNULL
			lastchild = tpnode;
			tpnode = tpnode->brother;
		}
		if (tpnode->child == NULL)
		{
				if (lastchild->child == tpnode)
				{
					lastchild->child = tpnode->brother;
					delete spnode;
					spnode = NULL;
				}
				else 
				{
					lastchild->brother = tpnode->brother;
					delete spnode;
					spnode = NULL;
				}
		}		
	}
}

void DNSTree::TreeToString() {
	stack<TreeNode*> bStack;		//�����ֵܽڵ�Ľڵ�
	stack<TreeNode*> cStack;		//��ջ�нڵ�������
	TreeNode *p = TreeHead->child;
	while (p->child != NULL)
	{
		if (p->brother)
		{
			bStack.push(p);
		}

		cStack.push(p);
		p = p->child;
	}


}

void Menu() {
	int select = 1;
	DNSTree T;

	printf(
		"******************************************************\n"
		"*                                                    *\n"
		"*                    ��������ϵͳ                    *\n"
		"*                                                    *\n"
		"*                      ��ӭʹ��                      *\n"
		"*                                                    *\n"
		"*                                                    *\n"
		"*                                                    *\n"
		"*                                                    *\n"
		"******************************************************\n");
	system("pause");
	system("cls");
	while(select)
	{
		printf(
			"******************************************************\n"
			"*                                                    *\n"
			"*             1.��������                             *\n"
			"*             2.��ʾ������                           *\n"
			"*             3.���ļ���ȡ                           *\n"
			"*             4.ɾ������                             *\n"
			"*             0.�˳�����                             *\n"
			"*                                                    *\n"
			"******************************************************\n");
		cout << "������ѡ��";
		cin >> select;
		system("cls");
		switch (select)
		{
		case 1:
			T.SaveTreeFile();
			break;
		case 2:
			T.Display();
			break;
		case 3:
			T.ReadTreeFile();
			break;
		case 4:
			T.DNSDelete();
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	
}

int main() {
	Menu();
	return 0;
}