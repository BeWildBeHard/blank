// ConsoleApplication6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<exception>
#define LISTINITSIZE 100
#define LISTMEROY 10
typedef struct {
	int *elme;
	int length;
	int listsize;
}Sqlist;
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int patition(Sqlist &L , int Left , int Right)
{
	int j = Left;      //j用来遍历
	int i = j - 1;     //用来指向小于基准元素的位置 
	int key = L.elme[Right];  //基准元素
	for (; j < Right; j++)
	{
		if (L.elme[j] <= key)
		{
			swap(&L.elme[++i], &L.elme[j]);
		}
	}
	swap(&L.elme[Right], &L.elme[++i]);  //将基准元素放在中间位置
	return i;
}
void SortList(Sqlist &L, int Left, int Right)//排序
{
	if (Left >= Right)   //递归终止条件
		return;
	int mid = patition(L, Left, Right);
	SortList(L, Left, mid - 1);
	SortList(L, mid + 1, Right);
}
void InitList_sq(Sqlist &L)   //初始化
{
	L.elme = (int*)malloc(LISTINITSIZE * sizeof(int));
	if (!L.elme)        //判断有没有成功的分配到内存很关键
	{
		exit(OVERFLOW);
	}
	L.length = 0;      //默认长度为0
	L.listsize = LISTINITSIZE;//线性表最大长度
}
void ClearList(Sqlist &L)   //变成空表
{
	if (L.elme != NULL)
	{
		L.length = 0;
		L.listsize = 0;
	}
}
void ListInsert_sq(Sqlist &L, int i, int e) //添加
{
	if (i<1 || i>L.length + 1)  //判断删除的位置是否合理
	{
		exit(0);
	}
	if (L.length >= L.listsize) //看看是否要拓展线性表的最大长度
	{
		int *newbase = (int*)realloc(L.elme, (L.listsize + LISTMEROY) * sizeof(int)); //新基址
		if (!newbase) exit(OVERFLOW);
		L.elme = newbase;
		L.listsize += LISTMEROY;
	}
	int *q = L.elme+i-1;    //想要添加元素的位置
	for (int *p = L.elme + L.length - 1; p >= q; --p)//往前移
	{
		*(p + 1) = *p;
	}
	*q = e;
	++L.length;
}
void ListDelet_sq(Sqlist &L, int i , int &e) //删除
{
	if (i<1 || i>L.length)
	{
		exit(0);
	}
	int *p = L.elme + i - 1;  //被删除元素的位置
	e = *p;
	int *q = L.elme + L.length - 1; //表尾的位置
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;
	}
	--L.length;
}
bool equal(int a, int b)     //判断相等与否
{
	if (a == b)
	{
		return true;
	}
	else return false;
}
int LocateElem_sq(Sqlist &L, int e)   //查找
{
	int i = 1;                      //我认为起到了一个计数的作用
	int *p = L.elme;                //p代表了线性表的初始位置
	while (i <= L.length && !(*equal)(*p++, e)) 
	{
		++i;
	}
	if (i <= L.length)
	{
		return i;
	}
	else return 0;
}
void MergeList(Sqlist &lc, Sqlist &lb, Sqlist &la)   //有序合并
{
	int *qa_s = la.elme;
	int *qb_s = lb.elme;
	lc.length = lc.listsize = la.length + lb.length;
	int *pc = lc.elme = (int *)malloc(lc.listsize * sizeof(int));
	if (!lc.elme)
	{
		exit(OVERFLOW);
	}
	int *qa_l = la.elme + la.length - 1;
	int *qb_l = lb.elme + lb.length - 1;
	while (qa_s <= qa_l && qb_s <= qb_l)
	{
		if (*qa_s >= *qb_s)
		{
			*pc++ = *qb_s++;
		}
		else *pc++ = *qa_s++;
	}
	while (qa_s <= qa_l)
	{
		*pc++ = *qa_s++;
	}
	while (qb_s <= qb_l)
	{
		*pc++ = *qb_s++;
	}
}
void MergeNonList(Sqlist &lc, Sqlist &lb, Sqlist &la)
{
	SortList(la, 0, la.length - 1);
	SortList(lb, 0, lb.length - 1);
	MergeList(lc, lb, la);
}
void TravelList(Sqlist &L)   //遍历整个线性表，并且输出出来
{
	int i = 0;
	for (; i < L.length; i++)
	{
		if(i!=L.length-1) printf("%d ", L.elme[i]);
		else printf("%d", L.elme[i]);	
	}
}
int main()
{
	Sqlist L;
	int e = 0;
	InitList_sq(L);
	ListInsert_sq(L, 1, 9);
	ListInsert_sq(L, 1, 10);
	ListInsert_sq(L, 1, 7);
	ListInsert_sq(L, 1, 8);
	Sqlist l1;
	Sqlist l2;
	InitList_sq(l1);
	InitList_sq(l2);
	ListInsert_sq(l1, 1, 7);
	ListInsert_sq(l1, 1, 4);
	ListInsert_sq(l1, 1, 6);
	ListInsert_sq(l1, 1, 5);
	MergeNonList(l2, l1, L);
	TravelList(l2);
	printf("length is : %d", l2.length);
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
