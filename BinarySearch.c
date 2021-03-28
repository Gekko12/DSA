/*
  Program for binary search (BinSearch works for sorted data)
*/

#include <stdio.h>

int BinSrch(int low ,int high ,int key ,int ary[]);
void sort(int low ,int high ,int ary[]);
void merge(int low,int mid,int high,int ary[]);

int main()
{
  int n ;

  printf("\nEnter the size of ary :");
  scanf("%d",&n);

  int ary[n];
  printf("\nEnter the %d elements of ary :",n);
  for(int i=0;i<n;i++)
    scanf("%d",&ary[i]);

  sort(0 ,n-1 ,ary);
  printf("\nSorted ary : ");
  for(int i=0;i<n;i++)
    printf("%2d ",ary[i]);

  int key=0;
  printf("\nEnter key to find :");
  scanf("%d",&key);
  
  int pos = BinSrch(0 ,n-1 ,key ,ary);

  if(pos < 0)
    printf("\nNot found..........\n\n");
  else
    printf("\nKey = %d found at pos =  %d\n\n",key ,pos);

  return 0;
}
  

void sort(int low ,int high,int ary[]) //Implementing merge-sort
{
  if(low < high)
    {
      int mid = (low+high)/2;

      sort(low ,mid ,ary);
      sort(mid+1 ,high ,ary);

      merge(low ,mid ,high ,ary);
    }
}

void merge(int low,int mid,int high,int ary[])
{
  int n1 = mid - low + 1;
  int n2 = high - mid;

  int i=0 ,j=0 ,k=low ;

  int L[n1] ,R[n2];

  for(int p=0;p<n1;p++)
    L[p] = ary[low+p];

  for(int p=0;p<n2;p++)
    R[p] = ary[mid+p+1];

  while(i<n1 && j<n2)
    {
      if(L[i] <= R[j])
	{
	  ary[k] = L[i];
	  i++;
	}
      else
	{
	  ary[k] = R[j];
	  j++;
	}
      k++;
    }

  while(i<n1)
    {   
      ary[k] = L[i];
      i++;
      k++;
    }

  while(j<n2)
    {   
      ary[k] = R[j];
      j++;
      k++;
    }
}

int BinSrch(int low ,int high ,int key ,int ary[])
{
  int mid = ( low + high ) / 2;

  while(low < high && key != ary[mid])
    {
      if( key > ary[mid])
	low = mid+1;
      else
	high = mid -1;

      mid = ( low + high)/2;
    }

  if(key == ary[mid])
    return mid;
  else
    return -1;
}	  

