#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode {
	int key;
    struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

TreeNode n2 = { 25 ,NULL,NULL};
TreeNode n1 = { 16 ,NULL,&n2 };
TreeNode n3 = { 41 ,&n1,&n6};
TreeNode n4 = { 42 ,NULL,NULL};
TreeNode n5 = { 46 ,&n4,NULL};
TreeNode n6 = { 53 ,&n5,&n7};
TreeNode n7 = { 55 ,NULL,NULL};
TreeNode n8 = { 60 ,&n3,&n14};
TreeNode n9 = { 62 ,NULL,NULL};
TreeNode n10 = { 63 ,&n9,&n11};
TreeNode n11 = { 64 ,NULL,NULL};
TreeNode n12 = { 65 ,&n10,&n11};
TreeNode n13 = { 70 ,NULL,NULL};
TreeNode n14 = { 74 ,&n12,NULL};
TreeNode* root = &n8;

TreeNode *search(TreeNode *node, int key){
    if ( node == NULL ) return NULL;
    if ( key == node->key ) return node;
    else if( key<node->key) return search(node->left,key);
    else return search(node->right,key);
}

TreeNode *new_node(int item){
    TreeNode *temp=(TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right =NULL;
    return temp;
}

TreeNode *insert_node(TreeNode *node, int key){
    if(node == NULL) return new_node(key); //트리가 공백일때 새운 노드 반환
    if(key<node->key)
        node->left = insert_node(node->left,key);
    else if(key>node->key)
        node->right = insert_node(node->right,key);

    return node;
}

TreeNode *min_value_node(TreeNode *node){
    TreeNode *current = node;
    while (current->left != NULL)
        current= current->left;

    return current;    
}

TreeNode *delete_node(TreeNode *root,int key){
    if(root == NULL ) return root;
    if (key<root->key)
        root->left = delete_node(root->left,key);
    else if(key>root->key)
        root->right = delete_node(root->right,key);
    else{
        if(root->left == NULL ){
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if( root->right == NULL ){
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        TreeNode *temp = min_value_node(root->right);

        root->key = temp->key;
        
        root->right = delete_node(root->right,temp->key);
    }
    return root;
}



int main(){
    printf("---------------------\n");
    printf("| s  : search       |\n");
    printf("| i  : add node     |\n");
    printf("| d  : del node     |\n");
    printf("| t  : inorder      |\n");
    printf("| I  : add node(Re) |\n");
    printf("| D  : del node(Re) |\n");
    printf("| c  : exit         |\n");
    printf("---------------------");
            


}