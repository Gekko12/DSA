/*
Given a matrix (or 2D array) a[][] of integers, find prefix sum matrix for it. Let prefix sum matrix be psa[][]. The value of psa[i][j] contains sum of all values which are above it or on left of it.
Eg.
        _         _       _          _
       |  10 20 30 |     |  10 30 60  |
       |  5  10 20 |  =  |  15 45 95  |
       |_ 2  4  6 _|     |_ 17 51 107_|

A simple solution is to find psa[i][j] by traversing and adding values from a[0][0] to a[i][j]. Time complexity of this solution is O(R * C * R * C).

An efficient solution is to use previously computed values to compute psa[i][j]. Unlike 1D array prefix sum, this is tricky, here if we simply add psa[i][j-1] and psa[i-1][j], we get sum of elements from a[0][0] to a[i-1][j-1] twice, so we subtract psa[i-1][j-1]. 

Time Complexity : O(R*C) 
Auxiliary Space : O(R*C)

Example : 
psa[3][3] = psa[2][3] + psa[3][2] - psa[2][2] + a[2][2]
          = 6 + 6 - 4 + 1
          = 9

The general formula: 
psa[i][j] = psa[i-1][j] + psa[i][j-1] - psa[i-1][j-1] + a[i][j]

Corner Cases (First row and first column)
If i = 0 and j = 0
   psa[i][j] = a[i][j]
If i = 0 and j > 0
   psa[i][j] = psa[i][j-1] + a[i][j]
If i > 0 and j = 0
   psa[i][j] = psa[i-1][j] + a[i][j]
*/

#include <bits/stdc++.h>
#define MAX_SIZE 10

using namespace std;

int ary[MAX_SIZE][MAX_SIZE];

void sumMatrix(int m, int n)
{
    int sum[m][n];
    /*for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            sum[i][j] = 0;*/

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

int main(void)
{
    int m, n;
    cout<<"Enter m and n: \n";
    cin>>m>>n;

    cout<<"\nEnter mxn matrix :\n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
            cin>>ary[i][j];
    }

    sumMatrix(m, n);
    return 0;
}