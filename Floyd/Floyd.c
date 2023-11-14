#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES	100	
#define INF	1000000	/* ���Ѵ� (������ ���� ���) */
typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];


//��ü ���
// void printA(GraphType* g) {
//     printf("===============\n");
//     for (int i = 0; i < g->n; i++) {
//         for (int j = 0; j < g->n; j++) {
//             if (A[i][j] == INF) {
//                 printf("  *  ");
//             } else {
//                 printf("%3d  ", A[i][j]);
//             }
//         }
//         printf("\n");
//     }
//     printf("===============\n");
// }

void floyd(GraphType* g)
{
	int i, j, k;
	for (i = 0; i<g->n; i++){
		for (j = 0; j<g->n; j++){
			A[i][j] = g->weight[i][j];
            }
    }
    //�ִ� ��� ����ؼ� ����
	for (k = 0; k<g->n; k++) {
		for (i = 0; i<g->n; i++)
			for (j = 0; j<g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
	}
}

int main(void)
{
	GraphType g = { 10,
    // 1  2  3    4    5   6   7  8  9  10  
	{{ 0, 3, INF, INF, INF, 11, 12,INF,INF,INF },//1
	{ 3,  0, 5, 4, 1, 7, 8,INF,INF,INF },//2
	{ INF, 5, 0, 2, INF, INF, 6,5,INF,INF,},//3
	{ INF, 4, 2, 0, 13, INF, INF,14,INF,16},//4
	{ INF, 1, INF, 13, 0, 9, INF,INF,18,17 },//5
	{ 11,7, INF, INF, 9, 0,INF,INF,INF, INF },//6
	{ 12,8,6,INF,INF,INF,0,13,INF,INF }, //7
    {INF,INF,5,14,INF,INF,13,0,INF,15} , //8
    {INF,INF,INF,INF,18,INF,INF,INF,0,10}, //9
    {INF,INF,INF,16,17,INF,INF,15,10,0}
    }  //��� �Է�
	};
	floyd(&g);
    int start, end;
    printf("Floyd-Warshall Algorithm\n");
    for(int i =0; i<=6; i++){ 
        start= 0;
        end = 0;
        printf("\nStart Node :");
        scanf("%d", &start);  //���� ��带 �Է�
        printf("End Node : ");
        scanf("%d", &end);  //���� ��带 �Է�

        if (start < 1 ||start > g.n || end < 1 || end > g.n) {  //��尡 0���� ���� ��쳪 ������ �������� ū ���
            printf("wrong input\n");
        } else {
            printf("Shortest Distance : %d\n", A[start - 1][end - 1]);
        }
    }
	return 0;
}