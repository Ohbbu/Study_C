#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
	int is_thread; //만약 오른쪽 링크가 스레드이면 TRUE
} TreeNode;

TreeNode *find_successor(TreeNode *p)
{
	// q는 p의 오른쪽 포인터
	TreeNode *q = p->right;
	// 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환
	if( q==NULL || p->is_thread==TRUE)
		return q;
	// 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
	while( q->left != NULL ) q = q->left;
	return q;
}
void thread_inorder(TreeNode *t)
{
	TreeNode *q;
	q=t;

	while (q->left) q = q->left;		// 가장 왼쪽 노드로 이동

	do  {
		printf("%c ", q->data);	// 데이터 출력
		q = find_successor(q); 	// 후속자 함수 호출
	} while(q);			// NULL이 아니면
}
TreeNode n1 = { 4, NULL, NULL, 1 };
TreeNode n2 = { 5, NULL, NULL, 1 };
TreeNode n3 = { 3, &n1, &n2, 0 };
TreeNode n4 = { 6, NULL, NULL, 1 };
TreeNode n5 = { 2, &n3, &n4, 0 };
TreeNode n6 = { 8, NULL, NULL, 1 };
TreeNode n7 = { 10, NULL, NULL, 1 };
TreeNode n8 = { 11, NULL, NULL, 0 };
TreeNode n9 = { 9, &n7, &n8, 0 };
TreeNode n10 = { 7  , &n5, &n9, 0 };
TreeNode n11 = { 1, &n5, &n10, 0 };
TreeNode* root = &n11;

int main()
{
  // 스레드 설정
  n1.right = &n3;
  n2.right = &n5;
  n4.right = &n11;
  n6.right = &n10;
  n7.right = &n9;

 
  // 중위 순회
  printf("1.중위 순회 결과");
  thread_inorder(root);
}