// 图.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <limits>
#include <string.h>
//队列
typedef struct node {
	int data;
	struct node * next;
}node;
//定义队列（保存队首和队尾指针）
typedef struct queue_link {
	node * front;
	node * rear;
}que;
//初始化队列
que * InitQueue()
{
	que * q = (que*)malloc(sizeof(que));
	q->front = q->rear = NULL;
	return q;
}
//判断队列是否为空
int EmptyQueue(que * q)
{
	return q->front == NULL;
}
//入队
void EnQueue(que *q, int data)
{
	node * n = (node *)malloc(sizeof(node));
	if (n == NULL)//内存分配失败
		return;
	n->data = data;
	n->next = NULL;//尾插法，插入元素指向空
	if (q->rear == NULL)
	{
		q->front = n;
		q->rear = n;
	}
	else {
		q->rear->next = n;//让n成为当前的尾部节点下一节点
		q->rear = n;//尾部指针指向n
	}

}
//出队(删除队首元素)
void DeQueue(que *q, int &u)
{
	node * n = q->front;
	u = n->data;
	if (q->front == NULL)//判断队列是否为空
		return;
	if (q->front == q->rear)//是否只有一个元素
	{
		q->front = NULL;
		q->rear = NULL;
	}
	else {
		q->front = q->front->next;
		free(n);
	}
}
//栈
typedef struct LNode {
	LNode *top;
	struct LNode *next;
	int date;
}*SqStack, LNode;
void InitStack(SqStack &S)
{
	S = (SqStack)malloc(sizeof(LNode));
	S->next = NULL;
	S->top = S->next;
}
bool EmptyStack(SqStack &S)
{
	if (S->top == NULL) return true;
	else return false;
}
void Push(SqStack &S, int e)   //进栈
{
	LNode *p = (SqStack)malloc(sizeof(LNode));
	p->date = e;
	S->next = p;
	p->next = S->top;
	S->top = p;
}
void Pop(SqStack &S, int &a)    //出栈
{
	LNode *p = S->top;
	a = p->date;
	S->next = S->top->next;
	S->top = S->next;
	free(p);
}
int GetTop(SqStack &S)
{
	if (EmptyStack) exit(-1);
	else return S->top->date;
}
//图的邻接矩阵实现
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct ArcCell
{
	int adj;//对于无权图，0或1表示相邻与否
	        //对于有权图表示的则是权值
	int *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
	char vex[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;         //邻接矩阵
	int vexnum, arcnum;     //顶点数和弧数
	GraphKind kind;
}MGraph;
int LocateVex(MGraph &G, char v1)
{
	int i = 0;
	for (; i < G.vexnum; i++)
	{
		if (v1 == G.vex[i])
		{
			return i;
		}
	}
}
void CreateUDN(MGraph &G)   //无向网
{
	printf("请输入图的顶点数以及弧数：\n");
	scanf_s("%d%d",&G.vexnum, &G.arcnum);
	printf("请输入顶点信息：\n");
	for (int i = 0; i < G.vexnum; i++)//输入顶点信息
	{
		scanf_s("%c%*c", &G.vex[i]);
	}
	for (int i = 0; i < G.vexnum; i++)//构造邻接矩阵
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		int w;
		printf("请输入第%d条弧的两个顶点以及权值:\n", k + 1);
		scanf_s("%c", &v1);
		scanf_s(" %c", &v2);
		scanf_s(" %d%*c", &w);
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[i][j] = G.arcs[j][i];
	}
	G.kind = UDN;
}
void CreateDG(MGraph &G)//构造有向图
{
	printf("请输入图的顶点数以及弧数：\n");
	scanf_s("%d%d%*c", &G.vexnum, &G.arcnum);
	printf("请输入顶点信息：\n");
	for (int i = 0; i < G.vexnum; i++)//输入顶点信息
	{
		scanf_s("%c%*c", &G.vex[i]);
	}
	for (int i = 0; i < G.vexnum; i++)//构造邻接矩阵
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		printf("请输入第%d条弧的弧尾和弧头:\n", k + 1);
		scanf_s("%c", &v1);
		scanf_s(" %c%*c", &v2);
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		G.arcs[i][j] = G.arcs[j][i];
	}
	G.kind = DG;
}
void CreateDN(MGraph &G)//构造有向网
{
	printf("请输入图的顶点数以及弧数：\n");
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	printf("请输入顶点信息：\n");
	for (int i = 0; i < G.vexnum; i++)//输入顶点信息
	{
		scanf_s("%c%*c", &G.vex[i]);
	}
	for (int i = 0; i < G.vexnum; i++)//构造邻接矩阵
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		int w;
		printf("请输入第%d条弧的弧尾和弧头以及权值:\n", k + 1);
		scanf_s("%c", &v1);
		scanf_s(" %c", &v2);
		scanf_s(" %d%*c", &w);
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[i][j] = G.arcs[j][i];
	}
	G.kind = DN;
}
void CreateUDG(MGraph &G)//构造无向图
{
	printf("请输入图的顶点数以及弧数：\n");
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	printf("请输入顶点信息：\n");
	for (int i = 0; i < G.vexnum; i++)//输入顶点信息
	{
		scanf_s("%c%*c", &G.vex[i]);
	}
	for (int i = 0; i < G.vexnum; i++)//构造邻接矩阵
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		printf("请输入第%d条弧的两个顶点:\n", k + 1);
		scanf_s("%c", &v1);
		scanf_s(" %c%*c", &v2);
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		G.arcs[i][j] = G.arcs[j][i];
	}
	G.kind = UDG;
}
void GreateGraph(MGraph &G)
{
	printf("输入你想要创建的图的类型(0为DG，1为DN，2为UDG，3为UDN):\n");
	scanf_s("%d", &G.kind);
	switch (G.kind)
	{
	case DG: CreateDG(G); break;
	case DN: CreateDN(G); break;
	case UDN: CreateUDN(G); break;
	case UDG: CreateUDG(G); break;
	default: exit(-1);
	}
}
//图的邻接表表示
#define MAX_VERTEX_NUM 20
typedef struct ArcNode
{
	int adjvex;//弧所指向的顶点位置
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode
{
	char data;        //顶点的信息
	ArcNode *firstarc;//指向第一条依附于该节点的指针
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALgraph;
int LocateALgraph(ALgraph &G, char v1)
{
	int i = 0;
	for (; i < G.vexnum; i++)
	{
		if (v1 == G.vertices[i].data)
		{
			return i;
		}
	}
}
void CreateALgraph(ALgraph &G)
{
	printf("请输入图的顶点数以及弧数：\n");
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	printf("请输入顶点信息：\n");
	for (int i = 0; i < G.vexnum; i++)//输入顶点信息
	{   //输入的是顶点值
		getchar();
		G.vertices[i].data = getchar();
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
		printf("请输入第%d条弧的弧尾和弧头:\n", k + 1);
		getchar();
		v1 = getchar();
		v2 = getchar();
		int i = LocateALgraph(G, v1);
		int j = LocateALgraph(G, v2);
		p->adjvex = j;//弧头的位置
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
	}
	G.kind = DG;
}
void PrintALGraph(ALgraph &G)//将表中的内容打印出来
{
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("节点%c指向了:", G.vertices[i].data);
		ArcNode *p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			printf("%4c", G.vertices[p->adjvex].data);
			p = p->nextarc;
		}
		printf("\n");
	}
}
//图的深度优先搜索
bool visited[MAX_VERTEX_NUM];//访问标识符
/****************************************************/
/*
   返回v的第一个邻接顶点。若顶点在G中没有邻接顶点，就返回空
 */
 /***************************************************/
int FirstAdjVex(ALgraph &G, int v)
{
	if (G.vertices[v].firstarc)
		return G.vertices[v].firstarc->adjvex;
	else return NULL;
}
/**************************************************************/
/*
   返回v的（相对于w的）下一个邻接顶点。若w是v的最后一个顶点，就返回空
 */
/**************************************************************/
int NextAdjVex(ALgraph &G, int v, int w)
{
	ArcNode *p;
	if (G.vertices[v].firstarc == NULL)
	{
		return NULL;
	}
	else {
		p = G.vertices[v].firstarc;
		while (p->adjvex != w) p = p->nextarc;//w的位置是当前v不断的往后遍历的位置，找到w的位置
		if (p->nextarc == NULL) return NULL;  //如果w就已经是v遍历的最后一个位置了就返回空
		else return p->nextarc->adjvex;       //不然就指向w的下一个其实就是与v想连接的另一个
	}
}
void visitVex(ALgraph &G, int v)
{
	printf("%2c", G.vertices[v].data);
}
//深度遍历
void DFS(ALgraph &G, int v)
{
	visited[v] = true;
	visitVex(G, v);
	//从第一个开始不断往后 F相当于i=0,N相当于+1因为它的函数作用就是这个
	for (int w = FirstAdjVex(G, v); w >= 1; w = NextAdjVex(G, v, w))
	{
		if (!visited[w]) DFS(G, w);
	}
}
void DFSTraverse(ALgraph G)
{
	for (int v = 0; v < G.vexnum; v++) visited[v] = false;
	//对每个顶点都进行一次深度遍历，因为这样就能防止有些顶点即不指向其他顶点，也没被其他顶点指向而不能遍历了
	for (int m = 0; m < G.vexnum; m++)
		if (!visited[m]) DFS(G, m);
}
//图的广度优先搜索,因为要利用队列来实现
void BFSTraverse(ALgraph &G)
{
	for (int v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false;
	}
	int u;
	que* Q = InitQueue();
	for (int v = 0; v < G.vexnum; ++v)
	{
		if (!visited[v])
		{
			visited[v] = true; 
			visitVex(G, v);
			EnQueue(Q, v);
			while (!EmptyQueue)
			{
				DeQueue(Q, u);
				//不断遍历u的邻接点，从第一个到最后一个
				for (int w = FirstAdjVex(G, u); w >= 1; w = NextAdjVex(G, u, w))
				{
					if (!visited[w])//没被访问就入队列，就可以按照顺序来访问其邻接点
					{
						visited[w] = true;
						visitVex(G, w);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}
//拓扑排序
void FindDegree(ALgraph &G, int vexDegree[])
{
	for (int i = 0; i < G.vexnum; i++)
	{
		vexDegree[i] = 0;
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode *p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			vexDegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}
void TopologicSort(ALgraph &G)
{
	int count = 0;//对输出顶点计数
	int vexDegree[MAX_VERTEX_NUM];
	FindDegree(G, vexDegree);
	SqStack S;
	InitStack(S);
	//入度为0者进入栈
	for (int i = 0; i < G.vexnum; i++)
	{
		if (vexDegree[i] == 0) Push(S, i);
	}
	while (!EmptyStack(S))
	{
		int a = 0;
		Pop(S, a);
		visitVex(G, a);
		count++;
		ArcNode *p = G.vertices[a].firstarc;
		for (; p != NULL; p = p->nextarc)
		{
			//相当于将这个顶点抹去，包括以它为尾的边
			vexDegree[p->adjvex]--;
			//看是不是为0了，为0就入栈
			if (vexDegree[p->adjvex] == 0) Push(S, p->adjvex);
		}
	}
	if (count < G.vexnum) printf("该有向图含有回路");
}
int main()
{
	ALgraph G;
	CreateALgraph(G);
	TopologicSort(G);
	printf("\n");
	PrintALGraph(G);
	//DFSTraverse(G);
	//BFSTraverse(G);
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
