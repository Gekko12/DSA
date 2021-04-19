/*
Given an array, print the Next Greater Element (NGE) for every element. The Next greater Element for an element x is the first greater element on the right side of x in the array. Elements for which no greater element exist, consider next greater element as -1. 

Examples: 
    For an array, the rightmost element always has the next greater element as -1.
    For an array which is sorted in decreasing order, all elements have next greater element as -1.
    
For the input array [4, 5, 2, 25}, the next greater elements for each element are as follows.
Element       NGE
4      -->   5
5      -->   25
2      -->   25
25     -->   -1

For the input array [13, 7, 6, 12}, the next greater elements for each element are as follows.  
Element        NGE
13      -->    -1
7       -->     12
6       -->     12
12      -->     -1

Method 1 (Simple) 
Use two loops: The outer loop picks all the elements one by one. The inner loop looks for the first greater element for the element picked by the outer loop. If a greater element is found then that element is printed as next, otherwise -1 is printed.
Time Complexity: O(N^2)
Auxiliary Space: O(1)

Method 2 (Using Stack) 
Push the first element to stack.
Pick rest of the elements one by one and follow the following steps in loop. 
    1.Mark the current element as next.
    2.If stack is not empty, compare top element of stack with next.
    3.If next is greater than the top element,Pop element from stack. next is the next greater 
      element for the popped element.
    4.Keep popping from the stack while the popped element is smaller than next. next becomes the     
      next greater element for all such popped elements
Finally, push the next in the stack.
After the loop in step 2 is over, pop all the elements from stack and print -1 as next element for them
Time Complexity: O(N)
Auxiliary Space: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

void next_greater(int ary[], int n)
{
    stack<int> s;
    unordered_map<int, int> mp;     //To get the output in same order as we input

    s.push(ary[0]);

    for(int i=1; i<n; i++)
    {
        if(s.empty())
        {
            s.push(ary[i]);
            continue;
        }

        while(!s.empty() && ary[i]>s.top())
        {
            //cout<<s.top()<<" --> "<<ary[i]<<endl;
            mp[s.top()] = ary[i];
            s.pop();
        }
        s.push(ary[i]);
    }

    while(!s.empty())
    {
        //cout<<s.top()<<" --> "<<" -1\n";
        mp[s.top()] = -1;
        s.pop();
    }

    for (int i = 0; i < n; i++)
        cout << ary[i] << " ---> " << mp[ary[i]] << endl;

}

int main()
{
    int n;
    cout<<"Enter the size of array: ";
    cin>>n;

    cout<<"\nEnter the "<<n<<" array elements :\n";
    int ary[n];
    memset(ary, 0, sizeof(ary));
    for(int i=0; i<n; i++)
        cin>>ary[i];

    next_greater(ary, n);
    return 0;
}