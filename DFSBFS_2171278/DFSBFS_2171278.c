#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {	//그래프 타입, 인접행렬을 나타냄
	int n;
	int* visited;
	int** adj_mat;
}GraphType;

typedef struct {	//스택 타입, DFS 구현할 때 사용
	int top;
	int StackSize;
	int* stack;
}StackType;

typedef struct {	//큐 타입, BFS 구현시 사용
	int front, rear, QueSize;
	int* queue;
}QueueType;

// 큐 삽입 연산
void enque(QueueType* q, int n) {
	if ((q->rear+1) % q->QueSize == q->front) {
		printf("Queue is FULL\n");
		return;
	}
	q->queue[q->rear] = n;
	q->rear++;
}

// 큐 삭제 연산
int deque(QueueType* q) {
	if (q->front == q->rear) {
		printf("Queue is EMPTY\n");
		return 0;
	}
	return q->queue[q->front++];
}

// BFS 탐색
void BFS(GraphType* gr, int v) {
	// 큐 생성
	QueueType q;
	int w;
	q.front = q.rear = 0;
	q.QueSize = gr->n + 1;
	q.queue = (int*)malloc(sizeof(int) * q.QueSize);

	// 시작 정점 방문 표시
	gr->visited[v] = 1;
	printf("%d 방문 -> ", v);
	enque(&q, v);	//시작 정점을 큐에 저장
	while (q.front < q.rear) {	//큐가 비어있지 않을 때까지 반복
		v = deque(&q);	//큐에서 정점을 추출해내고
		for (w = 1; w <= gr->n; w++)	//인접 정점을 탐색함
			if (gr->adj_mat[v][w] && !gr->visited[w]) {	//인접 정점이 존재하고, 방문하지 않을 때까지 반복
				gr->visited[w] = 1;	// 방문한 정점을 방문했다고 표시
				printf("%d 방문-> ", w);
				enque(&q, w);	// 큐에 저장
			}
	}
}

void makeGraph(GraphType* gr, int no)	//그래프를 만드는 함수
{
	gr->n = no;
	gr->visited = (int*)malloc(sizeof(int) * (no + 1));	//방문한 정점을 표시하기 위한 배열을 동적할당
	gr->adj_mat = (int**)malloc((sizeof(int*) * (no + 1)));	//인접행렬 구현을 위한 행렬 동적할당
	for (int i = 1; i <= no; i++) {
		gr->adj_mat[i] = (int*)malloc(sizeof(int) * (no + 1));
		gr->visited[i] = 0;
	}
	for (int i = 1; i <= no; i++) { //행렬과 배열 초기화
		gr->visited[i] = 0;
		for (int j = 1; j <= no; j++)
			gr->adj_mat[i][j] = 0;
	}
}

void push(StackType* st, int n) { //스택 push 연산
	if (st->top == st->StackSize - 1) {
		printf("Stack is FULL\n");
		return;
	}
	st->stack[++(st->top)] = n;
}

int pop(StackType* st) {	//스택 pop 연산
	if (st->top == -1) {
		printf("Stack is EMPTY\n");
		return 0;
	}
	return st->stack[(st->top)--];
}

void addGraphEdge(GraphType* gr, int a, int b) {	//인접행렬에 간선을 표시함
	gr->adj_mat[a][b] = 1;
}

void DFS(GraphType* gr, int v) {	//재귀함수로 구현한 DFS
	int w;
	gr->visited[v] = 1;
	printf("%d 방문 -> ", v);
	for (w = 1; w <= gr->n; w++)
		if (gr->adj_mat[v][w] && !gr->visited[w])
			DFS(gr, w);
}

void DFS_Stack(GraphType* gr, int v) {	//스택을 사용한 DFS
	StackType st;
	int w;

	st.top = -1;
	st.StackSize = gr->n + 1;
	st.stack = (int*)malloc(sizeof(int) * st.StackSize);
	push(&st, v);
	gr->visited[v] = 1;
	while (st.top != -1) {
		v = pop(&st);
		printf("%d 방문 -> ", v);
		for (w = gr->n; w >= 1; w--)
			if (gr->adj_mat[v][w] && !gr->visited[w]) {
				push(&st, w);
				gr->visited[w] = 1;
			}
	}
}

int main() {
	GraphType gr1;
	int no, v;

	no = 4;

	makeGraph(&gr1, no);
	addGraphEdge(&gr1, 2, 1);
	addGraphEdge(&gr1, 3, 1);
	addGraphEdge(&gr1, 3, 2);
	addGraphEdge(&gr1, 1, 3);
	addGraphEdge(&gr1, 4, 3);
	addGraphEdge(&gr1, 3, 4);

	printf("그래프에서 탐색을 시작할 노드의 번호를 입력하시오(1~%d): ", no);
	scanf("%d", &v);

	/*
	DFS(&gr1, v);
	for (int i = 0; i <= no; i++)
		gr1.visited[i] = 0;
	printf("\n");
	*/
	printf("스택을 사용한 DFS 결과 \n");
	DFS_Stack(&gr1, v);
	for (int i = 0; i <= no; i++)
		gr1.visited[i] = 0;
	printf("\n");
	printf("큐를 사용한 BFS 결과 \n");
	BFS(&gr1, v);
	printf("\n");
}