#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX_SIZE 20
int sorted[MAX_SIZE];
int comparisons = 0; //�� Ƚ�� ���� ����
int movements = 0; //�̵� Ƚ�� ���� ����

int merge_compare[MAX_SIZE], merge_move[MAX_SIZE];

void init_list(int list[]) {
    for (int i = 0; i < 20; i++) {
        list[i] = 0;
    }
}

// i: ���ĵ� ���� ����Ʈ�� ���� �ε���
// j: ���ĵ� ������ ����Ʈ�� ���� �ε���
// k: ���ĵ� ����Ʈ�� ���� �ε���
void merge(int list[],int left,int k,int right,int count){
    int start_num ,result;
    start_num = left; //���ҵ� ����Ʈ�� �����
    result = left; //��ü�� ����Ʈ�� �����
    int middle = k +1 ; //�߰� �ε���

    //���� ������� �迭�� ���Եȴ�.
    while(start_num<=k && middle <=right){ //start -> k ���� , middle -> finish����    
        if(list[start_num] <= list [middle]){
            comparisons++;
            sorted[result++] = list[start_num++];}
        else{
            comparisons++;
            sorted[result++] = list[middle++];
        }
    }

    // start_num ��� �ε����� �־��ٸ� k�� �ִ´�.
    if(start_num>k){
        movements++;
        for(int i=middle ; i<=right; i++){
            sorted[result++] = list[result];
        }
    }
    //k ��� ����  �����ٸ�start_num �ε����� �־��ش�.
    else{
        movements++;
        for(int i=start_num ; i<=k; i++){
            sorted[result++] = list[i];
        }
    }
    //�迭 sorted[]�� ����Ʈ�� �迭 list[]�� ��迭�Ѵ�.
    for(int i =left; i<=right; i++){
        movements++;
        list[i] = sorted[i];
    }
    for (int i = 0; i < MAX_SIZE-1 + 1; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    merge_compare[count] = comparisons;
    merge_move[count] = movements;
}

void merge_sort(int list[],int left, int right,int count){
    int mid;
    if(left<right){
        mid = (left+right)/2;
        merge_sort(list,left,mid,count);
        merge_sort(list,mid+1,right,count);
        merge(list,left,mid,right,count);
    }
}

// �� Ƚ���� �̵� Ƚ�� ��� ���ϴ� �Լ�
void result(int move[], int compar[]) {
    int avg_move = 0;
    int avg_compare = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        avg_move += move[i];
        avg_compare += compar[i];
    }

    printf("avg move count : %d\n", (avg_move / MAX_SIZE));
    printf("avg compare count : %d\n", (avg_compare / MAX_SIZE));
}

int main(){
  int i;
  int count;
  int list[MAX_SIZE];
  srand(time(NULL));
    for(i=0;i<MAX_SIZE;i++)
        list[i]=rand()%100;

    printf("orignal list : ");
    for(i=1;i<MAX_SIZE;i++)
        printf("%d ",list[i]);

    // �պ� ���� ����(left: �迭�� ���� = 0, right: �迭�� �� = 7)
    merge_sort(list, 0, MAX_SIZE-1,count);
    count++;
    result(merge_move, merge_compare);

}