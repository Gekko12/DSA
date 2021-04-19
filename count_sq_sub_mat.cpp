/*
Given a matrix mat[][] and two integers K and S, the task is to count all K x K sub-matrix such that the sum of all the elements in sub-matrix is greater than or equal to S.

Examples: 
Input:  K = 2, S = 15
        mat[][] = {{1, 2, 3}, 
                {4, 5, 6},
                {7, 8, 9}} 
Output: 3

Explanation:
In the given matrix there are 3 sub-matrix
Sub-Matrix 1: (0, 1) to (1, 2)
Sum = 2 + 3 + 5 + 6 = 16
Sub-matrix 2: (1, 0) to (2, 1)
Sum = 4 + 5 + 7 + 8 = 24
Sub-matrix 3: (1, 1) to (2, 2)
Sum = 5 + 6 + 8 + 9 = 28

Input:  K = 3, S = 35
        arr[][] = {{1, 7, 1, 1, 1}, 
                {2, 2, 2, 2, 2}, 
                {3, 9, 6, 7, 3}, 
                {4, 3, 2, 4, 5}, 
                {5, 1, 5, 3, 1}}
Output: 5

 

Naive Approach: Iterate over all the possible sub-matrix of size K x K and find the sum of each matrix. If the sum of the any sub-matrix is greater than the given sum S, then increment the count by 1.

Efficient Approach: The idea is to precompute the prefix sum of the matrix such that the sum of every sub-matrix sum can be computed in O(1) time. Finally, Iterate over all the possible positions of the matrix and check the sum of the sub-matrix of size K x K from that positions with inclusion and exclusion principle. If the sum is greater than the given sum then increment the count of such sub-matrix by 1.
*/
#include <bits/stdc++.h>
#define MAX_SIZE 10

using namespace std;

int ary[MAX_SIZE][MAX_SIZE];
int sum[MAX_SIZE][MAX_SIZE];

void sumMatrix(int m, int n)
{
    sum[0][0] = ary[0][0];
    
    //for 0th row
    for(int i=1; i<n; i++)
        sum[0][i] = sum[0][i-1] + ary[0][i];
    
    //for 0th col
    for(int i=1; i<m; i++)
        sum[i][0] = sum[i-1][0] + ary[i][0];

    //for rest of col and row
    for(int i=1; i<m; i++)
    {
        for(int j=1; j<n; j++)
        {
            //we subtract sum(i-1, j-1) because it adds up twice during summation of sum(i-1, j) and sum(i, j-1)
            sum[i][j] = sum[i-1][j] + sum[i][j-1] + ary[i][j] - sum[i-1][j-1];
        }
    }

    cout<<"\nPrefix Sum-matrix :\n";

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
            cout<<sum[i][j]<<" ";
        cout<<endl;
    }  
}

int countSubMatrix(int m, int n, int k, int s)
{
    int c = 0;
    int subMatSum = 0;

    for(int i=k-1; i<m; i++)
    {
        for(int j=k-1; j<n; j++)
        {
            if(j==k-1 || i==k-1)
            {
                if(i==k-1 && j==k-1)
                    subMatSum = sum[i][j];
                else if(i==k-1)
                    subMatSum = sum[i][j] - sum[i][j-k];
                else
                    subMatSum = sum[i][j] - sum[i-k][j];
            }
            else
                subMatSum = sum[i][j] - sum[i-k][j] - sum[i][j-k] + sum[i-k][j-k];

            if(subMatSum >= s)
            {
                //cout<<i<<" "<<j<<" "<<subMatSum<<endl;
                c++;
            }
        }
    }
    return c;
}

int main(void)
{
    int m, n;
    cout<<"Enter m and n: ";
    cin>>m>>n;

    cout<<"\nEnter mxn matrix :\n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
            cin>>ary[i][j];
    }

    sumMatrix(m, n);

    int k, s;
    cout<<"\nEnter K and S respectively: ";
    cin>>k>>s;

    cout<<"Count = "<<countSubMatrix(m, n, k, s)<<endl;
    return 0;
}

