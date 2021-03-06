// ConsoleApplication7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode, *LinkList;
void CreateList_L(LinkList &L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;                    //创建一个空表
	if (n == 0)
	{
		
	}
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			LNode *p = (LinkList)malloc(sizeof(LNode));
			scanf_s("%d", &p->data);
			p->next = L->next;
			L->next = p;
		}
	}
}
void GetElem(LinkList L, int i, int &e)//对e进行取指操作，这样就能够保持到第i个节点的值
{
	LNode *p = L->next;
	int j = 1;
	while (p&&j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
	{
		exit(0);
	}
	e = p->data;
}
void ListInsert(LinkList &L, int i, int e)
{
	LNode *p = L;  //指向头结点
	int j = 0;
	while (p&&j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
	{
		exit(0);
	}
	LNode *newNode = (LinkList)malloc(sizeof(LNode));
	newNode->next = p->next;
	p->next = newNode;
	newNode->data = e;
}
void ListDelete(LinkList &L, int i)
{
	LNode *p = L;
	int j = 0;
	while (p&&j < i - 1) //找到第i-1个节点，并且指向它的前驱
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
	{
		exit(0);
	}
	LNode *s = p->next;
	p->next = s->next;
	free(s);
}
void TravelList(LinkList &L)
{
	LNode *p = L;
	while (p->next)
	{
		printf("%d ", p->next->data);
		p = p->next;
	}
}
void MergeList(LinkList &lc,LinkList &lb,LinkList &la)
{
	LNode *pc;
	LNode *b = lb->next;
	LNode *a = la->next;
	pc = lc = la;
	while (b && a)
	{
		if (a->data <= b->data)
		{
			pc->next = a;
			pc = a;
			a = a->next;
		}
		else
		{
			pc->next = b;
			pc = b;
			b = b->next;
		}
	}
	pc->next = a ? a : b;
	free(lb);
}
int main()
{
	LinkList L1,L2,L3;
	CreateList_L(L1, 0);
	CreateList_L(L2, 0);
	ListInsert(L1, 1, 2);
	ListInsert(L1, 1, 1);
	ListInsert(L2, 1, 2);
	ListInsert(L2, 1, 1);
	MergeList(L3, L2, L1);
	TravelList(L3);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
