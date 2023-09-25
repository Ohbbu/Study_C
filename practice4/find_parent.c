#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
	int is_thread; //���� ������ ��ũ�� �������̸� TRUE
}TreeNode;

TreeNode n1 = { 4, NULL, NULL, 1 };
TreeNode n2 = { 5, NULL, NULL, 1 };
TreeNode n3 = { 3, &n1, &n2, 0 };
TreeNode n4 = { 6, NULL, NULL, 1 };
TreeNode n5 = { 2, &n3, &n4, 0 };
TreeNode n6 = { 8, NULL, NULL, 1 };
TreeNode n7 = { 10, NULL, NULL, 1 };
TreeNode n8 = { 11, NULL, NULL, 0 };
TreeNode n9 = { 9, &n7, &n8, 0 };
TreeNode n10 = { 7  , &n6, &n9, 0 };
TreeNode n11 = { 1, &n5, &n10, 0 };
TreeNode* root = &n11;

TreeNode* find_successor(TreeNode* root) {
    TreeNode* q = root->right;
    if (q == NULL || root->is_thread == TRUE)
        return q;
    while (q->left != NULL)
        q = q->left;
    return q;
}

// ���� ��ȸ 
void thread_inorder(TreeNode* root) {
    TreeNode* q = root;
    while (q->left != NULL)
        q = q->left;
    do {
        printf("%d ", q->data);
        q = find_successor(q);
    } while (q);
}

TreeNode* parent_helper(TreeNode* root, TreeNode* child) {
    if (root == NULL) //root ��尡 NULL�� ��� NULL�� ��ȯ��
        return NULL;
    if (root->left == child || root->right == child) //child�� root�� ������, ���� �ڽ� ������� Ȯ�� �� root ��� ��ȯ
        return root;
    TreeNode* left_parent = parent_helper(root->left, child); //root�� ���� ��忡 child ����� �θ� ��尡 �ִ��� Ȯ��
    if (left_parent != NULL) //���� left_parent �� null�� �ƴϸ� left_parent ��带 ��ȯ
        return left_parent;

    return parent_helper(root->right, child); //�ƴ� ��쿡�� root�� ������ ��忡 child ����� �θ� ��尡 �ִ��� Ȯ��
}

TreeNode* parent(TreeNode* child) {
    TreeNode* parent = parent_helper(root, child); //child ����� �θ� ��� �˻�
    return printf("parent node of node %d : %d", child->data, parent->data); //�˻� �� ã�� �θ����� ����� ���� ����ϰ� ��.
}
int main()
{
  // ������ ����
  n1.right = &n3;
  n2.right = &n5;
  n4.right = &n11;
  n6.right = &n10;
  n7.right = &n9;

 
  // ���� ��ȸ
  printf("1.inorder result \n");
  thread_inorder(root);

      //node4 parent
    TreeNode* child = &n1; // node 4
    printf("\n\n2. ");
    TreeNode* parent_node = parent(child);

    //node5 parent
    child = &n2; // node 5
    printf("\n3. ");
    parent_node = parent(child);

    //node4 parent
    child = &n4; 
    printf("\n4. ");
    parent_node = parent(child);
}