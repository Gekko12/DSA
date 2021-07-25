/*
Maximum Pairwise Product Problem

Find the maximum product of two distinct numbers in a sequence of non-negative integers.
Input: A sequence of non-negative integers.
Output: The maximum value that can be obtained by multiplying two different elements from the 
sequence.

Given a sequence of non-negative integers a1 , . . . , an , compute max(ai · aj)  1≤i,j≤n
Note that i and j should be different, though it may be the case that ai = aj.

Input format. 
The first line contains an integer n. 
The next line contains n non-negative integers a1 , . . . , an (separated by spaces).

Output format. 
The maximum pairwise product.

Constraints. 
2 ≤ n ≤ 2·10^5 ; 
0 ≤ a1 , . . . , an ≤ 2·10^5 .

Sample 1.
Input:
3
123
Output:
6
*/

#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define fast_io  ios_base::sync_with_stdio(false); cin.tie(NULL);

using ll = long long ;



ll maxProduct_pairwise(vector <int> v)
{
    int n = v.size();
    ll max_pro = LONG_LONG_MIN;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            ll tmp = (ll) v[i] * v[j];      
            // without type-conversion it results in int and results wrong answer 
            if(tmp > max_pro  &&  i != j)
                max_pro = tmp;
            
        }
    }
    return max_pro;
}


ll maxProduct_pairwise_fast(vector <int> v)
{
    int n = v.size();
    ll max1 = LONG_LONG_MIN;
    int indx1 = -1;
    ll max2 = LONG_LONG_MIN;

    for(int i=0; i<n; i++)
        if(v[i] > max1)
        {
            max1 = v[i];
            indx1 = i;
        }
    
    for(int j=0; j<n; j++)
        if(v[j] > max2 && indx1 != j)
            max2 = v[j];

    return (max1 * max2);
}


int main(void)
{
    //Testing naive and fast solution
    /*
    while(true)
    {
        ll n = rand() % 10 + 2;     // to generate random number between 2 to (9+2) ie. 11
        cout << n << endl;

        vector<int> v(n, 0);    // vector filled with zero
        
        for(int i=0; i<n; i++)
        {
            v[i] = rand() % 100000; // filling the vector with pseudo random number between 0 to 9
        }

        for(auto i: v)
            cout << i << " ";
        cout << endl;

        ll res1 = maxProduct_pairwise(v);
        ll res2 = maxProduct_pairwise_fast(v);
        cout << res1 << " " << res2 << endl;

        if(res1 == res2)
            cout<< "OK \n";
        else
        {
            cout << "Wrong answer !\n";
            break;
        }
    }
    */

    int n;
    cin >> n;

    vector <int> v(n, 0);

    for(int i=0; i<n; i++)
    {
       int ele;
       cin >> ele;
       v[i] = ele;
    }

    cout << maxProduct_pairwise_fast(v) << endl;
    return 0;
}