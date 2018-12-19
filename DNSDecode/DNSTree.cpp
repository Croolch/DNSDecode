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
		throw "头节点分配出错";
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
		//cout << "继续吗？（y/n）" << endl;
		cin >> flag;
	}
}

void DNSTree::DNSInsert(char data[],char IP[])		//输入域名和ip，存在内存里。
{

	int i = 0, j = 0;
	char temp[50];
	memset(temp, '\0', 50);
	stack<TreeNode*> s;
	while (1)
	{	
		temp[i++] = data[j++];                    //获取每个'.'之前或结束之前的字符串
		if (data[j] == '.' || data[j] == '\0')
		{
			TreeNode *N = new TreeNode;
			N->name = temp;						  //并存储到新节点
			s.push(N);							  //节点存入栈
			j++;
			i = 0;
			memset(temp, '\0', 50);
		}
		if (data[j - 1] == '\0')
			break;
	}
	TreeNode *spnode = NULL;                  //栈顶节点
	TreeNode *tpnode = TreeHead;       //指向的头节点
	TreeNode *lastchild = NULL;			   //记录上一个节点
	while (!s.empty())
	{
		spnode = s.top();
		if (!tpnode->child) {//判断当前层次的下一层有无节点，无则建立；
			tpnode->child = spnode;
			tpnode = spnode;
		}
		else
		{//若有节点则遍历这一层直到找到相同节点
			tpnode = tpnode->child;
			while (tpnode != NULL && spnode->name != tpnode->name) {
				lastchild = tpnode;//找到相同层次的域名，若没有相同节点则tpnode为NULL
				tpnode = tpnode->brother;
			}
			if (!tpnode)//tpnode为NULL则建立这个域名节点
			{
				lastchild->brother = spnode;
				tpnode = spnode;
			}
		}
		s.pop();
	}
	tpnode->ip = IP;//将ip埋在最后一层节点中
}

void DNSTree::DNSSearch()		//输入一个域名。在内存寻找对应的ip地址
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

	TreeNode *spnode = NULL;                         //栈顶节点
	TreeNode *tpnode = TreeHead->child;       //指向的头节点
	TreeNode *lastchild = NULL;			          //记录上一个节点

	while (!s.empty())
	{
		spnode = s.top();
		while (tpnode != NULL && tpnode->name != spnode->name)
		{//找到相同层次的域名，若无则为NULL
			tpnode = tpnode->brother;
		}
		if (!tpnode)//为NULL则跳出，查找失败
		{
			break;
		}
		else//不为NULL，则进入下一层，继续匹配下一层次域名
		{
			lastchild = tpnode;
			tpnode = tpnode->child;
		}
		s.pop();
	}
	if (lastchild->ip != "0")
	{
		cout << "IP为：" << lastchild->ip << endl;
	}
	else
	{
		cout << "找不到服务器或发生DNS错误" << endl;
	}
}

void DNSTree::SaveTreeFile()	//用于向文件中写入新的域名、ip信息的函数	/*作者：郭雨丰*/
{
	char data[Data_Lenth];
	char IP[Ip_Lenth];		//声明两个变量，分别用来临时储存即将写入文件的ip地址和域名
	memset(data, '\0', 50);
	memset(IP, '\0', 20);	//初始化

	cout << "请输入域名：";	//变量的输入
	cin >> data;
	cout << "请输入IP：";
	cin >> IP;

	fstream fbin("info.txt", ios::binary | ios::out | ios::app);	//以二进制方式打开文件，在文件末尾添加信息
	if (!fbin) {													//文件读取正确性的判断
		cout << "文件读取发生错误" << endl;
		return;
	}
	fbin.write(data, Data_Lenth);	//将信息写入文件
	fbin.write(IP, Ip_Lenth);

	fbin.close();			//关闭文件流
	DNSInsert(data, IP);
	cout << "写入完成！" << endl;
	return;
}

void DNSTree::ReadTreeFile()	//用于从文件中读取域名及ip地址的信息到内存中的函数	/*作者：郭雨丰*/
{
	char data[Data_Lenth];
	char IP[Ip_Lenth];		//声明两个变量，分别用来临时储存即将写入文件的ip地址和域名
	memset(data, '\0', Data_Lenth);
	memset(IP, '\0', Ip_Lenth);	//初始化

	fstream fbin("info.txt", ios::binary | ios::in | ios::out);		//以二进制方式打开文件，指针指向文件起始处
	if (!fbin) {													//文件读取正确性的判断
		cout << "文件读取发生错误" << endl;
		return;
	}
	int i = 0;			//用于控制循环的变量
	while (fbin.peek() != EOF)
	{
		memset(data, '\0', Data_Lenth);
		memset(IP, '\0', Ip_Lenth);
		fbin.seekg(i*(Data_Lenth + Ip_Lenth), ios::beg);	//用于定位输出位置
		fbin.read(data, Data_Lenth);
		fbin.read(IP, Ip_Lenth);		//依次读取已经写在文件中的信息
		DNSInsert(data, IP);			//调用insert函数，将临时变量中的信息写入树结构里
		i++;						//i自加，带动读取指针移动
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
//	cout << "请输入域名：";
//	cin >> data;
//	cout << "请输入IP：";
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
	cout << "请输入要删除的域名：";
	cin >> data;
	
	while (1)									
	{
		temp[i++] = data[j++];                    //获取每个'.'之前或结束之前的字符串
		if (data[j] == '.' || data[j] == '\0')
		{
			TreeNode *N = new TreeNode;
			N->name = temp;						  //并存储到新节点
			s.push(N);							  //节点存入栈
			j++;
			i = 0;
			memset(temp, '\0', 50);
		}
		if (data[j - 1] == '\0')
			break;
	}
	TreeNode *spnode = NULL;                  //栈顶节点
	TreeNode *tpnode = TreeHead->child;       //指向的头节点的孩子
	TreeNode *lastchild = NULL;			   //记录上一个节点
	deStack.push(TreeHead);
	while (!s.empty())
	{
		spnode = s.top();
		while (tpnode != NULL && tpnode->name != spnode->name)
		{//找到相同层次的域名，若无则为NULL
			tpnode = tpnode->brother;
		}
		if (!tpnode)//为NULL则跳出，查找失败
		{
			break;
		}
		else//不为NULL，则进入下一层，继续匹配下一层次域名
		{
			deStack.push(tpnode);
			lastchild = tpnode;
			tpnode = tpnode->child;
		}
		s.pop();
	}
	if (deStack.size() != s.size() + 1)
	{
		cout << "删除出错" << endl;
		return;
	}
	while (1)
	{
		if (deStack.top() == TreeHead)
		{
			break;
		}
		spnode = deStack.top();//指向要删除的底层节点
		deStack.pop();
		tpnode = deStack.top();
		lastchild = tpnode;
		tpnode = tpnode->child;
		while (tpnode != NULL && tpnode->name != spnode->name)
		{//找到相同层次的域名，若无则为NULL
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
	stack<TreeNode*> bStack;		//存有兄弟节点的节点
	stack<TreeNode*> cStack;		//该栈中节点进行输出
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
		"*                    域名解析系统                    *\n"
		"*                                                    *\n"
		"*                      欢迎使用                      *\n"
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
			"*             1.插入域名                             *\n"
			"*             2.显示域名树                           *\n"
			"*             3.从文件读取                           *\n"
			"*             4.删除域名                             *\n"
			"*             0.退出程序                             *\n"
			"*                                                    *\n"
			"******************************************************\n");
		cout << "请输入选择：";
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