#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}treenode;

//??? ??? ????
treenode* link() {
	treenode* n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9, *n10, *n11;
	n1 = (treenode*)malloc(sizeof(treenode));
	n2 = (treenode*)malloc(sizeof(treenode));
	n3 = (treenode*)malloc(sizeof(treenode));
	n4 = (treenode*)malloc(sizeof(treenode));
	n5 = (treenode*)malloc(sizeof(treenode));
	n6 = (treenode*)malloc(sizeof(treenode));
	n7 = (treenode*)malloc(sizeof(treenode));
	n8 = (treenode*)malloc(sizeof(treenode));
	n9 = (treenode*)malloc(sizeof(treenode));
	n10 = (treenode*)malloc(sizeof(treenode));
	n11 = (treenode*)malloc(sizeof(treenode));

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

//?? ??? ????
treenode n4 = { 4,NULL,NULL };
treenode n5 = { 5,NULL,NULL };
treenode n6 = { 6,NULL,NULL };
treenode n8 = { 8,NULL,NULL };
treenode n10 = { 10,NULL,NULL };
treenode n11 = { 11,NULL,NULL };
treenode n9 = { 9,&n10,&n11 };
treenode n7 = { 7,&n8,&n9 };
treenode n3 = { 3, &n4, &n5 };
treenode n2 = { 2, &n3, &n6 };
treenode n1 = { 1,&n2,&n7 };
	
treenode* root = &n1;

//inorder
inorder(treenode* root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

//preorder
preorder(treenode* root) {
	if (root) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//postorder
postorder(treenode* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

int main(void) {

	treenode* linkenode = &n1;

	printf("<Linked Tree>\n");
	printf("1. preorder\n");
	preorder(linkenode);
	printf("\n");

	printf("\n2. inorder\n");
	inorder(linkenode);
	printf("\n");

	printf("\n3. postorder  \n");
	postorder(linkenode);
	printf("\n");



	    printf("\n\n<Array Tree>\n");
	printf("1. preorder\n");
	preorder(root);
	printf("\n");

	printf("\n2. inorder\n");
	inorder(root);
	printf("\n");

	printf("\n3. postorder  \n");
	postorder(root);
	printf("\n");
	printf("\n");
	return 0;
}