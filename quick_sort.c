/*
  Quick sort algorithm(Best suited) having best and average case complexity of O(nlogn) and worst case complexity of O(n^2)

*/

#include<stdio.h>

#define MAX 30

void quick(int ,int ,int [] );
int partition(int  ,int  ,int []);
void swap(int *,int *);

int main(){
  int size , ary[MAX];
  
  printf("\nEnter the size of array :");
  scanf("%d",&size);

  printf("Enter the elements of array :\n");
  for(int i=0;i<size;i++){
    scanf("%d",&ary[i]);
  }

  quick( 0 , size-1 , ary );

  for(int i=0;i<size;i++)
    printf("ary[%d] = %d\t",i,ary[i]);

  return 0;
}



void swap(int *a,int *b){
  int temp = *b; //temp store the value of b
  *b = *a; //value at a
  * a = temp;
}

int partition(int low ,int high ,int arr[]){
  int pivot = arr[high]; // last element as pivot 
  int i = (low - 1); // Index of smaller element 

  for (int j = low; j <= high- 1; j++) 
    { 
      // If current element is smaller than the pivot 
      if (arr[j] < pivot) 
	{ 
	  i++; // increment index of smaller element 
	  swap(&arr[i], &arr[j]); 
	} 
    } 
  swap(&arr[i + 1], &arr[high]); // Don't put &pivot  rather than &arr[high] as we want to swap ary elements
  return (i + 1); 
}
 
void quick(int start ,int end ,int ary[]){
  if(start < end){
    int split_pos = partition(start,end,ary);
    quick( start , split_pos - 1 , ary);
    quick( split_pos+1 , end , ary);
  }
}

