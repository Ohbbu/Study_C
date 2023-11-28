#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX_SIZE 20
int sorted[MAX_SIZE];
int comparisons = 0; //비교 횟수 변수 선언
int movements = 0; //이동 횟수 변수 선언

int merge_compare[MAX_SIZE], merge_move[MAX_SIZE];

void init_list(int list[]) {
    for (int i = 0; i < 20; i++) {
        list[i] = 0;
    }
}

// i: 정렬된 왼쪽 리스트에 대한 인덱스
// j: 정렬된 오른쪽 리스트에 대한 인덱스
// k: 정렬될 리스트에 대한 인덱스
void merge(int list[],int left,int k,int right,int count){
    int start_num ,result;
    start_num = left; //분할된 리스트의 출발점
    result = left; //합체된 리스트의 출발점
    int middle = k +1 ; //중간 인덱스

    //작은 순서대로 배열에 삽입된다.
    while(start_num<=k && middle <=right){ //start -> k 까지 , middle -> finish까지    
        if(list[start_num] <= list [middle]){
            comparisons++;
            sorted[result++] = list[start_num++];}
        else{
            comparisons++;
            sorted[result++] = list[middle++];
        }
    }

    // start_num 모든 인덱스를 넣었다면 k를 넣는다.
    if(start_num>k){
        movements++;
        for(int i=middle ; i<=right; i++){
            sorted[result++] = list[result];
        }
    }
    //k 모든 값이  끝났다면start_num 인덱스를 넣어준다.
    else{
        movements++;
        for(int i=start_num ; i<=k; i++){
            sorted[result++] = list[i];
        }
    }
    //배열 sorted[]의 리스트를 배열 list[]로 재배열한다.
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

// 비교 횟수와 이동 횟수 평균 구하는 함수
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

    // 합병 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 7)
    merge_sort(list, 0, MAX_SIZE-1,count);
    count++;
    result(merge_move, merge_compare);

}