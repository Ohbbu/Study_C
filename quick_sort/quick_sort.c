#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_SIZE 20
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
int quick_compare[MAX_SIZE], quick_move[MAX_SIZE];
int comp = 0;
int move = 0;

void init_list(int arr[]) {
    for (int i = 0; i < 20; i++) {
        arr[i] = 0;
    }
}



void RandomArray(int arr[]) {
	for (int i = 0; i < 20; i++) {
		arr[i] = rand() % 100; //0부터 99까지의 난수를 생성한 후 리스트에 저장
	}
}
// 배열 출력 함수
void printArray(int arr[]) {
	for (int i = 0; i < 20; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int patition(int list[],int left,int right,int count){
    int pivot,temp;
    int low,high;
    low=left;
    high=right+1;
    pivot=list[left];
    do
    {
        do
        {
            low++;
            comp++;
        } while (low<=right && list[low]<pivot);
        do
        {
            high--;
            comp++;
        } while (high>=left && list[high]>pivot);
        if (low<high)
        {
            SWAP(list[low],list[high],temp);
            move++;
        }        
    } while (low<high);

    SWAP(list[left],list[high],temp);
    move++;
    for(int i=0;i<MAX_SIZE;i++)
        printf("%d ",list[i]);
    printf("\n");
    return high;
}

void quick_sort(int list[],int left,int right,int count){
    if (left<right)
    {
        for (int i = 0; i < MAX_SIZE; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");
        int q = patition(list,left,right,count);
        quick_sort(list,left,q-1,count);
        quick_sort(list,q+1,right,count);
    }
    quick_compare[count] = comp;
    quick_move[count] = move;
}

void result(int move[], int comp[]) {
    float avg_move = 0;
    float avg_compare = 0;

    for (int i = 0; i < 20; i++) {
        avg_move += move[i];
        avg_compare += comp[i];
    }

    printf("Averge Move Count : %.5f\n", (avg_move / 20));
    printf("Averge Compare Count : %.5f\n", (avg_compare / 20));
}

int main(void){
    int i,count;
    int list[MAX_SIZE];

    srand(time(NULL));
    for(i=0;i<MAX_SIZE;i++)
        list[i]=rand()%100;

    printf("Original List : ");
    for(i=0;i<MAX_SIZE;i++)
        printf("%d ",list[i]);
    printf("\n\n");

    quick_sort(list,0,MAX_SIZE-1,count);
    count++;
    for (int i = 0; i < 20; i++) {
        //선택 정렬
        init_list(list);
        RandomArray(list); // 랜덤 리스트 생성
        quick_sort(list,0,MAX_SIZE-1,count);
        printf("\n");
    }
    
    result(quick_move,quick_compare);
    return 0;
}   