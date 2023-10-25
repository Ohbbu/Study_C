#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_SIZE 200

typedef struct {
	int key;
}element;

//히프 구조체 
typedef struct Heap {
	element array[MAX_HEAP_SIZE];//heap 배열
	int size;
}Heap;

//히프 생성 함수
Heap* create() {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->size = 0;
	return heap;
}

//두 노드의 위치를 바꾸는 함수
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int insert(Heap *heap, element value) {
	int i = ++(heap->size);
	heap->array[i] = value;

	int count = 0; //방문한 노드 선언
	//처음 노드에 값을 삽입한 배열 출력
	for (int j = 1; j <= heap->size; j++) {
		printf("%d ", heap->array[j]);
	}
	printf("\n");

	// 트리를 거슬러 올라가면서 부모 노드와 비교하며 위치 조정
	while ((i != 1) && (value.key > heap->array[i / 2].key)) {
		heap->array[i] = heap->array[i / 2];
		i /= 2;
		heap->array[i] = value;
		for (int k = 1; k <= heap->size; k++)
		{
			printf("%d ", heap->array[k].key);
		}
		printf("\n");

		count++;
	}

	return count;
}

//특정 노드를 삭제하는 함수
int delete(Heap* heap, int value) {
	int count = 0; //찾는 노드의 인덱스

	int delete_index, child_index; //제거할 인덱스와 자식 인덱스 설정
	int	temp = heap->array[(heap->size)--].key;

	//찾는 노드의 값의 인덱스를 구하기
	for (int i = 1; i <= heap->size; i++) {
		if (heap->array[i].key == value) {
			delete_index = i;
			child_index = 2 * i;
		}
	}

	// 찾는 노드를 삭제하지 않고 힙을 재구성
	while (child_index <= heap->size) {
		// 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다.
		if ((child_index < heap->size) && (heap->array[child_index].key < heap->array[child_index + 1].key)) {
			child_index++;
		}
		while (temp >= heap->array[child_index].key) {
			break;
		}

		heap->array[delete_index] = heap->array[child_index];
		delete_index = child_index;
		child_index *= 2;

		for (int k = 1; k <= heap->size; k++)
		{
			printf("%d ", heap->array[k].key);
		}
		printf("\n");

		count++; // 방문한 노드의 횟수 증가
	}
	heap->array[delete_index].key = temp;

	return count; // 방문한 노드의 총 횟수를 반환
}

void insert_menu(Heap* heap) {
	element data;
	int value, count = 0;
	printf("add to value : ");
	scanf("%d", &value);
	data.key = value;
	count = insert(heap, data);
	printf("visit node : %d\n", count);
}

void delete_menu(Heap* heap) {
	int value, count = 0;
	printf("delete to value : ");
	scanf("%d", &value);
	count = delete(heap, value);
	printf("visit node : %d\n", count);
}

// 레벨별로 출력하는 함수
void levelOrder(Heap* heap) {
	int currentLevel = 1; // 현재 레벨
	int levelStartIndex = 1; // 현재 레벨의 첫 번째 노드 인덱스

	for (int i = 1; i <= heap->size; i++) {
		if (i == levelStartIndex) {
			printf("[%d] ", currentLevel);
			currentLevel++;
			levelStartIndex = i * 2;
		}
		printf("%d ", heap->array[i].key);
		if (i == levelStartIndex - 1) {
			printf("\n");
		}
	}
	printf("\n");
}

void menu() {
	printf("----------------------\n");
	printf("| i   : add node    |\n");
	printf("| d   : del node    |\n");
	printf("| p   : print level |\n");
	printf("| c   : exit        |\n");
	printf("----------------------\n");
}

int main() {
	//히프에 넣을 값 선언
	element e1 = { 90 }, e2 = { 89 }, e3 = { 70 }, e4 = { 36 }, e5 = { 75 }, e6 = { 63 }, e7 = { 65 }, e8 = { 21 }, e9 = { 18 }, e10 = { 15 };

	//히프 선언
	Heap* heap = create();
	insert(heap, e1);
	insert(heap, e2);
	insert(heap, e3);
	insert(heap, e4);
	insert(heap, e5);
	insert(heap, e6);
	insert(heap, e7);
	insert(heap, e8);
	insert(heap, e9);
	insert(heap, e10);

	menu(); // 메뉴 보여주기
	char choice; // 메뉴 입력 변수

	while (1)
	{
		printf("menu : ");
		scanf(" %c", &choice);

		switch (choice)
		{
		//노드 추가
		case 'i':
			insert_menu(heap);
			printf("\n");
			break;
		//노드 삭제
		case 'd':
			delete_menu(heap);
			printf("\n");
			break;
		//레벨별 출력
		case 'p':
			levelOrder(heap);
			printf("\n");
			break;
		}
		if (choice == 'c')
		{
			printf("exit\n");
			break;
		}
	}

	free(heap);
	return 0;
}