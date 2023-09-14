#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define SIZE 100
typedef struct TreeNode {
	struct TreeNode* left;
	int data;
	struct TreeNode* right;
} TreeNode;

int top = -1;
TreeNode *stack[SIZE];

void push(TreeNode *p) //left �������� �̵���
{
	if (top < SIZE - 1 && p != NULL)
		stack[++top] = p;
}
TreeNode *pop()
{
	TreeNode *p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}
void preorder(TreeNode *root)  //������ȸ
{
	push(root); 
	while (root != NULL) {
		root = pop();
		if(!root) break;
		printf("%d ",root->data);  //���
		push(root->right);  
		push(root->left);  //���ʰ� ������ ��带 ���ʴ�� ���ÿ� Ǫ��
	}
}


void inorder_iter(TreeNode *root)  //������ȸ
{
	while (1) {
		for ( ;root; root = root->left)
			push(root); //��Ʈ�� push�� �ƴ� �ּҸ� Ǫ���Ѵ�.
		root = pop();
		if (!root) break; // ��Ʈ�� NULL ���
		printf("%d ", root->data); 
		root = root->right; 
	}
}

void postorder(TreeNode *root){  //������ȸ
	while(1){
	do{
		if(root->data != NULL && root!= NULL){  //��Ʈ���������� ��µǾ���ϴ� ������ �Ǿտ� Ǫ��
			push(root);
			root=root->left;
		}
		else{
			break;
		}	
		}while(root!=NULL);
	root = pop();

	if(!root) break;
	if(root->right != NULL){
		if(root->right->data == NULL)
		{
			printf("%d ", root->data);
			root->data=NULL;
		}
		else{
			push(root);
			root = root->right ;
		}
	} 
	else{
		printf("%d " , root->data);
		root->data =NULL;
	}
}
}

TreeNode n11 = {NULL, 11, NULL};
TreeNode n10 = {NULL, 10, NULL};
TreeNode n9 = {NULL, 5, NULL};
TreeNode n8 = {NULL, 4, NULL};
TreeNode n7 = { &n10,9,&n11 };
TreeNode n6 = { NULL,8,NULL };
TreeNode n5 = { NULL,6,NULL };
TreeNode n4 = { &n8,3,&n9 };
TreeNode n3 = { &n6,7,&n7 };
TreeNode n2 = { &n4,2,&n5 };
TreeNode n1 = { &n2,1,&n3 };
TreeNode* root = &n1;
//��ũ Ʈ�� ����
TreeNode* link() {
	TreeNode* n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9, *n10, *n11;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));
	n4 = (TreeNode*)malloc(sizeof(TreeNode));
	n5 = (TreeNode*)malloc(sizeof(TreeNode));
	n6 = (TreeNode*)malloc(sizeof(TreeNode));
	n7 = (TreeNode*)malloc(sizeof(TreeNode));
	n8 = (TreeNode*)malloc(sizeof(TreeNode));
	n9 = (TreeNode*)malloc(sizeof(TreeNode));
	n10 = (TreeNode*)malloc(sizeof(TreeNode));
	n11 = (TreeNode*)malloc(sizeof(TreeNode));

	n1->data = 1;
	n1->left = n2;
	n1->right = n7;

	n2->data = 2;
	n2->left = n3;
	n2->right = n6;

	n3->data = 3;
	n3->left = n4;
	n3->right = n5;

	n4->data = 4;
	n4->left = NULL;
	n4->right = NULL;

	n5->data = 5;
	n5->left = NULL;
	n5->right = NULL;

	n6->data = 6;
	n6->left = NULL;
	n6->right = NULL;

	n7->data = 7;
	n7->left = n8;
	n7->right = n9;

	n9->data = 9;
	n9->left = n10;
	n9->right = n11;

	n10->data = 10;
	n10->left = NULL;
	n10->right = NULL;

	n11->data = 11;
	n11->left = NULL;
	n11->right = NULL;

	n8->data = 8;
	n8->left = NULL;
	n8->right = NULL;

	return &n1;
}
int main(void)
{
	TreeNode * linkenode = &n1;
	printf("<Traversal with Stack>\n\n");
	
    printf("1. preorder \n");
	preorder(linkenode);
    printf("\n");
	
    printf("\n2. inorder \n ");
	inorder_iter(linkenode);
	printf("\n");
    
    printf("\n3. postorder \n ");
	postorder(linkenode);
    printf("\n");
	return 0;
}