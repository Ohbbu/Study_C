#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
	int is_thread; //���� ������ ��ũ�� �������̸� TRUE
} TreeNode;

TreeNode *find_successor(TreeNode *p)
{
	// q�� p�� ������ ������
	TreeNode *q = p->right;
	// ���� ������ �����Ͱ� NULL�̰ų� �������̸� ������ �����͸� ��ȯ
	if( q==NULL || p->is_thread==TRUE)
		return q;
	// ���� ������ �ڽ��̸� �ٽ� ���� ���� ���� �̵�
	while( q->left != NULL ) q = q->left;
	return q;
}
void thread_inorder(TreeNode *t)
{
	TreeNode *q;
	q=t;

	while (q->left) q = q->left;		// ���� ���� ���� �̵�

	do  {
		printf("%c ", q->data);	// ������ ���
		q = find_successor(q); 	// �ļ��� �Լ� ȣ��
	} while(q);			// NULL�� �ƴϸ�
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
  // ������ ����
  n1.right = &n3;
  n2.right = &n5;
  n4.right = &n11;
  n6.right = &n10;
  n7.right = &n9;

 
  // ���� ��ȸ
  printf("1.���� ��ȸ ���");
  thread_inorder(root);
}