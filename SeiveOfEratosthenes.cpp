/*
  This algorithm is superb with time complexity of O(n*log(log(n))) and used to find prime numbers in a given 
  range .

  1. Create a list of consecutive integers from 2 to n: (2, 3, 4, …, n).
  2. Initially, let p equal 2, the first prime number.
  3. Starting from p2, count up in increments of p and mark each of these numbers greater than or equal to p2
  itself in the list. These numbers will be p(p+1), p(p+2), p(p+3), etc..
  4.Find the first number greater than p in the list that is not marked. If there was no such number, stop.
  Otherwise, let p now equal this number (which is the next prime), and repeat from step 3.

*/

#include <bits/stdc++.h>
using namespace std;

void SeiveEra(int);
void printPrime(bool[] ,int);

int main(void)
{
  int range;

  cout<<"\nEnter the range upto which prime numbers will print  :";
  cin>>range;

  cout<<"\n";
  SeiveEra(range);

  return 0;
}

void SeiveEra(int r)
{
  bool prime[r+1];
  memset(prime ,true ,sizeof(prime));//Initialy set all true ie assumed all are prime
  
  for(int i=2 ;i*i<=r ;i++)
    {
      if(prime[i])
	{
	  for(int j=i*i ;j<=r ;j += i)
	    prime[j] = false;
	}
    }

  prime[0] = prime[1] = false; //As 0 and 1 are not prime
  printPrime(prime ,r+1);
}

void printPrime(bool prime[] ,int n)
{
  for(int i=2;i<n;i++)
    if(prime[i])
      cout<<i<<" ";

  cout<<"\n\n";
}
	      
	      
