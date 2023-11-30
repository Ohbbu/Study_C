#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_SIZE 20
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
int comp = 0;
int move = 0;
int patition(int list[],int left,int right,int comp,int move){
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
        } while (low<=right && list[low]<pivot);
        do
        {
            high--;
        } while (high>=left && list[high]>pivot);
        if (low<high)
        {
            SWAP(list[low],list[high],temp);
            move++;
        }        
    } while (low<high);

    SWAP(list[left],list[high],temp);
    move++;
    return high;
}

void quick_sort(int list[],int left,int right,int comp,int move){
    if (left<right)
    {
        int q = patition(list,left,right,comp,move);
        quick_sort(list,left,q-1,comp,move);
        quick_sort(list,q+1,right,comp,move);
    }
}

int main(void){
    int i;
    int list[MAX_SIZE];

    srand(time(NULL));
    for(i=0;i<MAX_SIZE;i++)
        list[i]=rand()%100;

    printf("Original List\n");
    for(i=0;i<MAX_SIZE;i++)
        printf("%d ",list[i]);
    printf("\n");

    quick_sort(list,0,MAX_SIZE-1,comp,move);
    for(i=0;i<MAX_SIZE;i++)
        printf("%d ",list[i]);
    printf("\n");
    printf("%d",move);
    return 0;
}   