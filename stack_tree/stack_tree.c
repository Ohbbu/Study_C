#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left,*right;    
}TreeNode;

#define SIZE 100
int top = -1;
TreeNode *stack[SIZE];

void push(TreeNode *p){
    if (top <SIZE -1 && p != NULL)
        stack[++top] = p;
}

TreeNode *pop(){
    TreeNode *p = NULL;
    if(top>=0)
        p=stack[top--];
    return p;
}

void inorder_iter(TreeNode *root){
    while (1)
    {
        for(;root;root=root->left)
            push(root);
        root = pop();
        if (!root)break;
        printf("%d ",root->data);
        root = root->right;
    }
}

void preoder_iter(TreeNode* root)
{
    push(root);
    while (root != NULL)
    {
        root = pop();
        if(!root) break;
        printf("%d ",root->data);
        push(root->right);
        push(root->left);
    }
}

void postorder_iter(TreeNode *root){
    while (1)
    {
        do{
            if(root->data != NULL && root != NULL){
                push(root);
                root = root -> left;
            }
            else{break;}

        }while (root != NULL);
        root = pop();
        if(!root) break;
        if(root -> right != NULL){
            if(root->right->data == NULL){
                printf("%d ",root->data);
                root->data=NULL;
            }
            else{
                push(root);
                root = root->right;
            }
        }
        else{
            printf("%d ",root->data);
            root->data = NULL;
        }
    }
}

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

//?? ??? ????
TreeNode n4 = { 4,NULL,NULL };
TreeNode n5 = { 5,NULL,NULL };
TreeNode n6 = { 6,NULL,NULL };
TreeNode n8 = { 8,NULL,NULL };
TreeNode n10 = { 10,NULL,NULL };
TreeNode n11 = { 11,NULL,NULL };
TreeNode n9 = { 9,&n10,&n11 };
TreeNode n7 = { 7,&n8,&n9 };
TreeNode n3 = { 3, &n4, &n5 };
TreeNode n2 = { 2, &n3, &n6 };
TreeNode n1 = { 1,&n2,&n7 };
	
TreeNode* root = &n1;


int main(void){
    printf("<Traversal with Stack>\n");
    printf("\n");

    printf("inorder = ");
    inorder_iter(root);
    printf("\n");
    
    printf("preorder = ");
    preorder_iter(root);
    printf("\n");

    printf("postorder = ");
    postorder_iter(root);
    printf("\n");
    return 0;
}