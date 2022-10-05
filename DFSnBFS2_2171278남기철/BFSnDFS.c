#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	int n;			// number of nodes
	int* visited;	// visit check array
	int** adj_mat;	// adjaceny magrix
} GraphType;

typedef struct {
	int top;
	int st_size;		// stack size
	int* stack;		// stack array
} StackType;

void makeGraph(GraphType* gr, int no)
{
	gr->n = no;
	gr->visited = (int*)malloc(sizeof(int) * (no + 1));
	gr->adj_mat = (int**)malloc((sizeof(int*) * (no + 1)));
	for (int i = 1; i <= no; i++) {
		gr->adj_mat[i] = (int*)malloc(sizeof(int) * (no + 1));
		gr->visited[i] = 0;
	}
	for (int i = 1; i <= no; i++) {
		gr->visited[i] = 0;
		for (int j = 1; j <= no; j++)
			gr->adj_mat[i][j] = 0;
	}
}

// ���� ��ķ� ǥ���� Ʈ���� ���� ���� �켱 Ž��
void DFS(GraphType* gr, int v)
{
	int w;
	gr->visited[v] = 1;		// ���� v�� �湮 ǥ�� 
	printf("%d ", v);		// �湮�� ���� ���
	for (w = 1; w <= gr->n; w++) 		// ���� ���� Ž��
		if (gr->adj_mat[v][w] && !gr->visited[w])
			DFS(gr, w);	//���� w���� DFS ���ν���
}

void st_push(StackType* st, int n)
{
	if (st->top == st->st_size - 1)
		return;		// full
	st->stack[++(st->top)] = n;
}

int st_pop(StackType* st)
{
	if (st->top == -1)
		return 0;		// empty
	return st->stack[(st->top)--];
}

void DFS_stack(GraphType* gr, int v)
{
	StackType st;
	int w;

	st.top = -1;
	st.st_size = gr->n + 1;
	st.stack = (int*)malloc(sizeof(int) * st.st_size);
	st_push(&st, v);
	gr->visited[v] = 1;		// ���� v�� �湮 ǥ�� 
	while (st.top != -1) {
		v = st_pop(&st);
		printf("%d ", v);		// �湮�� ���� ���
		//		for (w = 1; w <= gr->n; w++) 		// ���� ���� Ž��
		for (w = gr->n; w >= 1; w--) 		// ���� ���� Ž��
			if (gr->adj_mat[v][w] && !gr->visited[w]) {
				st_push(&st, w);
				gr->visited[w] = 1;		// ���� v�� �湮 ǥ�� 
			}
	}
}

void addGraphEdge(GraphType* gr, int a, int b)
{
	gr->adj_mat[a][b] = 1;
}

void main()
{
	GraphType gr1;
	int no, v;

	//	printf("Type the number of nodes in Graph1: ");
	//	scanf("%d", &no);
#if 1
	no = 7;
	makeGraph(&gr1, no);
	addGraphEdge(&gr1, 1, 2);
	addGraphEdge(&gr1, 1, 7);
	addGraphEdge(&gr1, 2, 3);
	addGraphEdge(&gr1, 2, 6);
	addGraphEdge(&gr1, 3, 1);
	addGraphEdge(&gr1, 3, 4);
	addGraphEdge(&gr1, 4, 5);
#else
	no = 4;
	makeGraph(&gr1, no);
	addGraphEdge(&gr1, 1, 2);
	addGraphEdge(&gr1, 1, 3);
	addGraphEdge(&gr1, 2, 3);
	addGraphEdge(&gr1, 3, 1);
	addGraphEdge(&gr1, 3, 4);
	addGraphEdge(&gr1, 4, 3);
#endif
	printf("Type the number of start node in Graph1 for DFS(1~%d): ", no);
	scanf("%d", &v);
	DFS(&gr1, v);
	for (int i = 0; i <= no; i++)
		gr1.visited[i] = 0;
	printf("\n");
	DFS_stack(&gr1, v);
}
