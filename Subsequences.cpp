/*
Program to find the subsequences of a string.

Eg. 
Input:
abc

Output:
'', a, b, c, ab, ac, bc, abc    ie. 2^(len(str)) subsequence string including empty string.

To find the subsequences we can use recursion :-
print_subseq(input.substr(1), output)
print_subseq(input.substr(1), output+input[0])

                                    'abc'
                             /                   \
                        'bc',''                    'bc', 'a'
                     /           \              /               \
                'c',''      'c','b'           'c','a'          'c', 'ab'
                  /     \       /   \          /      \           /       \
            '',''   '','c'   '','b'  '','bc'   '','a'  '','ac'   '','ab'   '','abc'


Base condition:
    if(input.length() == 0)
        print(output)

At each input we consider -
    1. we ignore the input[0] and pass input[1:] 
    2. we consider the input[0] and add it to the output ie. input[1:]+input[0]
to the next stage we pass input[1:]

We use substr(from, to) built-in string function which return string[from : to]
if to arg is ommited then returns string[from:]

This algo. has a time complexity of O(2^n) where n is the length of string
*/

#include<bits/stdc++.h>
using namespace std;

//set<string> subseq;

void print_subseq(string input, string output)
{
    if(input.length() == 0)
    {
        if(output.length() == 0)
            cout<<"Empty-string"<<"  ";
            //subseq.insert("Empty-string");
        else
            cout<<output<<"  ";
            //subseq.insert(output);
        return ;
    }

    print_subseq(input.substr(1), output);
    print_subseq(input.substr(1), output+input[0]);
}

int main(void)
{
    string input;
    string output = "";

    cout<<"Enter a string: ";
    cin>>input;

    cout<<endl;
    print_subseq(input, output);
    //for(auto i:subseq)
    //    cout<<i<<" ";
    cout<<endl;

    return 0;
}