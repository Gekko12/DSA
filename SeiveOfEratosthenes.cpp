/*
  This algorithm is superb with time complexity of O(n*log(log(n))) and used to find prime numbers in a given 
  range .

  1. Create a list of consecutive integers from 2 to n: (2, 3, 4, …, n).
  2. Initially, let p equal 2, the first prime number.
  3. Starting from p2, count up in increments of p and mark each of these numbers greater than or equal to p2
  itself in the list. These numbers will be p(p+1), p(p+2), p(p+3), etc..
  4. Find the first number greater than p in the list that is not marked. If there was no such number, stop.
  Otherwise, let p now equal this number (which is the next prime), and repeat from step 3.

Problems with Simple Sieve:
The Sieve of Eratosthenes looks good, but consider the situation when n is large, the Simple Sieve faces following issues.
    1. An array of size Θ(n) may not fit in memory
    2. The simple Sieve is not cache friendly even for slightly bigger n. The algorithm traverses the array without locality of reference

Segmented Sieve :-
The idea of segmented sieve is to divide the range [0..n-1] in different segments and compute primes in all segments one by one. This algorithm first 
uses Simple Sieve to find primes smaller than or equal to √(n). 
Below are steps used in Segmented Sieve.
    1. Use Simple Sieve to find all primes upto square root of ‘n’ and store these primes in an array “prime[]”. Store the found primes in an array ‘prime[]’.
    2. We need all primes in range [0..n-1]. We divide this range in different segments such that size of every segment is at-most √n
    3. Do following for every segment [low..high] 
        a. Create an array mark[high-low+1]. Here we need only O(x) space where x is number of elements in given range.
        b. Iterate through all primes found in step 1. For every prime, mark its multiples in given range [low..high].

In Simple Sieve, we needed O(n) space which may not be feasible for large n. Here we need O(√n) space and we process smaller ranges at a 
time (locality of reference).
Note that time complexity (or number of operations) by Segmented Sieve is same as Simple Sieve. It has advantages for large ‘n’ as it has better locality of 
reference thus allowing better caching by the CPU and also requires less memory space.
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
	      
	      
