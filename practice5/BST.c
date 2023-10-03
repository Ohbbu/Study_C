#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
    struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

//노드 추가 함수 
TreeNode* createnode(int data) {
	TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->data = data;
	newnode->left = newnode->right = NULL;
	return newnode;
}

//중위 순회 함수(재귀)
void inorder(TreeNode* root, int* node_count) {
	if (root == NULL) return;
	inorder(root->left,node_count);
	(*node_count)++;
	printf("%d ", root->data);
	inorder(root->right, node_count);
}

// 가장 작은 값을 찾는 함수(최소값 노드 반환)
TreeNode* minValueNode(TreeNode* node) {
	TreeNode* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

//노드 삭제 함수(재귀)
TreeNode* delete_recursive(TreeNode* root, int data, int* node_count) {
	if (root == NULL) {
		return root;
	}

	// 삭제할 노드 찾기
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

		// 두 개의 자식 노드가 있는 경우
		TreeNode* temp = minValueNode(root->right);
		root->data = temp->data;
		root->right = delete_recursive(root->right, temp->data, node_count);
	}

	return root;
}

//노드 삭제 함수(반복)
TreeNode* delete_iterative(TreeNode* root, int data, int* node_count) {
	TreeNode* current = root;
	TreeNode* parent = NULL;
	TreeNode* parent_stack[100]; // 부모 노드를 저장하는 스택 (충분한 크기로 조절)

	// 노드를 찾아가며 스택에 부모 노드 저장
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
		// 삭제할 노드가 존재하지 않음
		return root;
	}

	// 삭제할 노드를 찾았을 경우
	if (current->left == NULL) {
		// 왼쪽 자식이 없는 경우
		if (parent == NULL) {
			// 루트 노드를 삭제하는 경우
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
		// 오른쪽 자식이 없는 경우
		if (parent == NULL) {
			// 루트 노드를 삭제하는 경우
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
		// 두 개의 자식 노드가 있는 경우
		TreeNode* temp = minValueNode(current->right); // 오른쪽 서브트리에서 가장 작은 값을 찾음
		current->data = temp->data; // 삭제할 노드의 값을 가장 작은 값으로 대체

		// 대체된 값을 가진 노드를 삭제 (재귀적으로 삭제 함수 호출)
		current->right = delete_recursive(current->right, temp->data, node_count);
	}

	return root;
}

//노드 삽입 함수(반복)
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
			// 중복된 값은 여기에서 처리할 수 있음
			free(newnode); // 중복 값은 무시하고 메모리 해제
			return root; // 기존 루트를 반환
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

// 노드 삽입 함수(재귀)
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

//노드 중위 순회 함수(재귀)
void inorderwithcount(TreeNode* root) {
	int node_count = 0;
	inorder(root, &node_count);
	printf("\nNumber of nodes visited : %d\n", node_count);
}

//노드 삭제 함수(검색용)
TreeNode* node_delete(TreeNode* root, char choice) {
	int data, node_count=0;
	printf("value to delete : ");
	scanf("%d", &data);
	while (getchar() != '\n'); // 엔터 키('\n')를 읽어서 버퍼를 비움
	if (choice == 'd')
		root = delete_recursive(root, data, &node_count);
	else if (choice == 'D')
		root = delete_iterative(root, data, &node_count);

	printf("Number of nodes visited : %d\n", node_count);
	inorder(root,&node_count); // 노드 삭제 후 중위 순회를 다시 수행하여 트리 상태를 출력
	return root; // 수정된 루트 노드를 반환합니다.
}

// 노드 삽입 함수(검색용)
TreeNode* node_insert(TreeNode* root, char choice) {
	int data, node_count = 1;
	printf("value to add : ");
	scanf("%d", &data);
	while (getchar() != '\n'); // 엔터 키('\n')를 읽어서 버퍼를 비움
	if (choice == 'i')
		root = insert(root, data, &node_count);
	else if (choice == 'I')
		root = insert_iterative(root, data, &node_count);

	printf("Number of nodes visited : %d\n", node_count);
	inorder(root, &node_count); // 노드 삭제 후 중위 순회를 다시 수행하여 트리 상태를 출력
	return root; // 수정된 루트 노드를 반환
}

//노드 검색 함수(반복)
void search(TreeNode* root, int data) {
	int node_count = 0; //Number of nodes visited 변수

	while (root != NULL)
	{
		if (data == root->data) { //root의 값과 찾고자 하는 노드의 값이 일치할 경우  검색 성공 + 방문 노드의 수 출력
			node_count += 1;
			printf("search success : %d\n", root->data);
			printf("Number of nodes visited : %d\n", node_count);
			break;
		}
		//data의 값이 현재 노드 값보다 작으면 왼쪽 서브 트리로 이동
		else if (data < root->data) {
			node_count += 1;
			root = root->left;
		}
		//data의 값이 현재 노드 값보다 크면 오른쪽 서브 트리로 이동
		else {
			node_count += 1;
			root = root->right;
		}
	}
    
}

//노드 검색 함수(검색용)
void node_search(TreeNode* root) {
	int find_num, node_count = 0;
	printf("value to search : ");
	scanf("%d", &find_num);
	while (getchar() != '\n'); // 엔터 키('\n')를 읽어서 버퍼를 비움
	search(root, find_num);
	inorder(root, &node_count); // 노드 삭제 후 중위 순회를 다시 수행하여 트리 상태를 출력
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
	//노드 설정
	TreeNode* root = createnode(60);
	//레벨 1
	root->left = createnode(41);
	root->right = createnode(74);
	//레벨 2
	root->left->left = createnode(16);
	root->left->right = createnode(53);
	root->right->left = createnode(65);
	//레벨 3
	root->left->left->right = createnode(25);
	root->left->right->left = createnode(46);
	root->left->right->right = createnode(55);
	root->right->left->left = createnode(63);
	root->right->left->right = createnode(70);
	//레벨 4
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
