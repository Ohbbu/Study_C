#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
    struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

//��� �߰� �Լ� 
TreeNode* createnode(int data) {
	TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->data = data;
	newnode->left = newnode->right = NULL;
	return newnode;
}

//���� ��ȸ �Լ�(���)
void inorder(TreeNode* root, int* node_count) {
	if (root == NULL) return;
	inorder(root->left,node_count);
	(*node_count)++;
	printf("%d ", root->data);
	inorder(root->right, node_count);
}

// ���� ���� ���� ã�� �Լ�(�ּҰ� ��� ��ȯ)
TreeNode* minValueNode(TreeNode* node) {
	TreeNode* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

//��� ���� �Լ�(���)
TreeNode* delete_recursive(TreeNode* root, int data, int* node_count) {
	if (root == NULL) {
		return root;
	}

	// ������ ��� ã��
	(*node_count)++;
	if (data < root->data) {
		root->left = delete_recursive(root->left, data, node_count);
	}
	else if (data > root->data) {
		root->right = delete_recursive(root->right, data, node_count);
	}
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// �� ���� �ڽ� ��尡 �ִ� ���
		TreeNode* temp = minValueNode(root->right);
		root->data = temp->data;
		root->right = delete_recursive(root->right, temp->data, node_count);
	}

	return root;
}

//��� ���� �Լ�(�ݺ�)
TreeNode* delete_iterative(TreeNode* root, int data, int* node_count) {
	TreeNode* current = root;
	TreeNode* parent = NULL;
	TreeNode* parent_stack[100]; // �θ� ��带 �����ϴ� ���� (����� ũ��� ����)

	// ��带 ã�ư��� ���ÿ� �θ� ��� ����
	while (current != NULL && current->data != data) {
		parent = current;
		parent_stack[*node_count] = parent;
		(*node_count)++;

		if (data < current->data) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	if (current == NULL) {
		// ������ ��尡 �������� ����
		return root;
	}

	// ������ ��带 ã���� ���
	if (current->left == NULL) {
		// ���� �ڽ��� ���� ���
		if (parent == NULL) {
			// ��Ʈ ��带 �����ϴ� ���
			TreeNode* temp = current->right;
			free(current);
			return temp;
		}
		if (parent->left == current) {
			parent->left = current->right;
		}
		else {
			parent->right = current->right;
		}
		free(current);
	}
	else if (current->right == NULL) {
		// ������ �ڽ��� ���� ���
		if (parent == NULL) {
			// ��Ʈ ��带 �����ϴ� ���
			TreeNode* temp = current->left;
			free(current);
			return temp;
		}
		if (parent->left == current) {
			parent->left = current->left;
		}
		else {
			parent->right = current->left;
		}
		free(current);
	}
	else {
		// �� ���� �ڽ� ��尡 �ִ� ���
		TreeNode* temp = minValueNode(current->right); // ������ ����Ʈ������ ���� ���� ���� ã��
		current->data = temp->data; // ������ ����� ���� ���� ���� ������ ��ü

		// ��ü�� ���� ���� ��带 ���� (��������� ���� �Լ� ȣ��)
		current->right = delete_recursive(current->right, temp->data, node_count);
	}

	return root;
}

//��� ���� �Լ�(�ݺ�)
TreeNode* insert_iterative(TreeNode* root, int data, int* node_count) {
	TreeNode* newnode = createnode(data);
	if (root == NULL) {
		(*node_count)++;
		return newnode;
	}

	TreeNode* current = root;
	TreeNode* parent = NULL;

	while (current != NULL) {
		parent = current;
		if (data < current->data) {
			(*node_count)++;
			current = current->left;
		}
		else if (data > current->data) {
			(*node_count)++;
			current = current->right;
		}
		else {
			// �ߺ��� ���� ���⿡�� ó���� �� �ֽ��ϴ�.
			free(newnode); // �ߺ� ���� �����ϰ� �޸� ����
			return root; // ���� ��Ʈ�� ��ȯ
		}
	}

	if (data < parent->data) {
		parent->left = newnode;
	}
	else {
		parent->right = newnode;
	}

	return root;
}

// ��� ���� �Լ�(���)
TreeNode* insert(TreeNode* root, int data, int* node_count) {

	if (root == NULL) {
		(*node_count)++;
		return createnode(data);
	}
	if (data < root->data) {
		(*node_count)++;
		root->left = insert(root->left, data, node_count);
	}
	else if (data > root->data) {
		(*node_count)++;
		root->right = insert(root->right, data, node_count);
	}
	return root;
}

//��� ���� ��ȸ �Լ�(���)
void inorderwithcount(TreeNode* root) {
	int node_count = 0;
	inorder(root, &node_count);
	printf("\nNumber of nodes visited : %d\n", node_count);
}

//��� ���� �Լ�(�˻���)
TreeNode* node_delete(TreeNode* root, char choice) {
	int data, node_count=0;
	printf("value to delete : ");
	scanf("%d", &data);
	while (getchar() != '\n'); // ���� Ű('\n')�� �о ���۸� ���ϴ�.
	if (choice == 'd')
		root = delete_recursive(root, data, &node_count);
	else if (choice == 'D')
		root = delete_iterative(root, data, &node_count);

	printf("Number of nodes visited : %d\n", node_count);
	inorder(root,&node_count); // ��� ���� �� ���� ��ȸ�� �ٽ� �����Ͽ� Ʈ�� ���¸� ���
	return root; // ������ ��Ʈ ��带 ��ȯ�մϴ�.
}

// ��� ���� �Լ�(�˻���)
TreeNode* node_insert(TreeNode* root, char choice) {
	int data, node_count = 1;
	printf("value to add : ");
	scanf("%d", &data);
	while (getchar() != '\n'); // ���� Ű('\n')�� �о ���۸� ���ϴ�.
	if (choice == 'i')
		root = insert(root, data, &node_count);
	else if (choice == 'I')
		root = insert_iterative(root, data, &node_count);

	printf("Number of nodes visited : %d\n", node_count);
	inorder(root, &node_count); // ��� ���� �� ���� ��ȸ�� �ٽ� �����Ͽ� Ʈ�� ���¸� ���
	return root; // ������ ��Ʈ ��带 ��ȯ
}

//��� �˻� �Լ�(�ݺ�)
void search(TreeNode* root, int data) {
	int node_count = 0; //Number of nodes visited ����

	while (root != NULL)
	{
		if (data == root->data) { //root�� ���� ã���� �ϴ� ����� ���� ��ġ�� ���  �˻� ���� + �湮 ����� �� ���
			node_count += 1;
			printf("search success : %d\n", root->data);
			printf("Number of nodes visited : %d\n", node_count);
			break;
		}
		//data�� ���� ���� ��� ������ ������ ���� ���� Ʈ���� �̵�
		else if (data < root->data) {
			node_count += 1;
			root = root->left;
		}
		//data�� ���� ���� ��� ������ ũ�� ������ ���� Ʈ���� �̵�
		else {
			node_count += 1;
			root = root->right;
		}
	}
    
}

//��� �˻� �Լ�(�˻���)
void node_search(TreeNode* root) {
	int find_num, node_count = 0;
	printf("value to search : ");
	scanf("%d", &find_num);
	while (getchar() != '\n'); // ���� Ű('\n')�� �о ���۸� ���
	search(root, find_num);
	inorder(root, &node_count); // ��� ���� �� ���� ��ȸ�� �ٽ� �����Ͽ� Ʈ�� ���¸� ���
}

void menu(){
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

int main(){
    //�⺻ ��� ����
	TreeNode* root = createnode(60);
	//���� 1
	root->left = createnode(41);
	root->right = createnode(74);
	//���� 2
	root->left->left = createnode(16);
	root->left->right = createnode(53);
	root->right->left = createnode(65);
	//���� 3
	root->left->left->right = createnode(25);
	root->left->right->left = createnode(46);
	root->left->right->right = createnode(55);
	root->right->left->left = createnode(63);
	root->right->left->right = createnode(70);
	//���� 4
	root->left->right->left->left = createnode(42);
	root->right->left->left->left = createnode(62);
	root->right->left->left->right = createnode(64);

    char choice;
    int num;
    menu();
    while(1){
        printf("\nselect menu : ");
        scanf("%c" ,&choice);

        if (choice == 's') {
			node_search(root);
			printf("\n\n");
		}
		else if (choice == 'i' || choice == 'I') {
			root = node_insert(root, choice);
			printf("\n\n");
		}
		else if (choice == 'd' || choice == 'D') {
			root = node_delete(root, choice);
			printf("\n\n");
		}
		else if (choice == 't') {
			inorderwithcount(root);
			printf("\n");
		}
		else if (choice == 'c')
			break;

    }
        return 0;
    
}