/*
  Merge Sort:-

  Time complexity:
  Best:- O(nlogn)   Worst:- O(nlogn), better than QuickSort in terms of Worst case
*/
        
         
#include<stdio.h>
         
#define MAX 50
         
void merge(int ary[],int low,int mid,int high){
  int n1=mid-low+1;
  int n2=high-mid;
  int i=0 ,j=0 ;
  int k=low;
         
  int Lary[n1] ,Rary[n2];
         
  for(int p=0;p<n1;p++)
    Lary[p]=ary[low+p];
                
  for(int p=0;p<n2;p++)
    Rary[p]=ary[mid+p+1];
                
  while(i<n1 && j<n2){
    if(Lary[i]<=Rary[j]){
      ary[k]=Lary[i];
      i++;
    }
    else{
      ary[k]=Rary[j];
      j++;
    }
    k++;
  }

  while(i<n1){
    ary[k]=Lary[i];
    i++;
    k++;
  }

  while(j<n2){
    ary[k]=Rary[j];
    j++;
    k++;
  }

}
     
void merge_sort(int ary[],int low,int high){
  if(low<high){
    int mid=(low+(high-1))/2;
    merge_sort(ary,low,mid);
    merge_sort(ary,mid+1,high);
                
    merge(ary,low,mid,high); 
  }
}

int main(){
  int n , ary[MAX];
        
  printf("Enter the size of array :");
  scanf("%d",&n);
        
  printf("Enter the array elements :\n");
  for(int i=0;i<n;i++)
    scanf("%d",&ary[i]);
                
  merge_sort(ary,0,n-1);
        
  printf("\nSorted array  : ");
  for(int i=0;i<n;i++)
    printf("%d ",ary[i]);
                
  printf("\n\n\n");
        
  return 0;
}
