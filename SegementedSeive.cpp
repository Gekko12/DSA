/*
Segmented Seive follows from the optimization "sieving till root" that there is no need to keep the whole array is_prime[1...n] at all time. For performing of sieving it's enough to keep just prime numbers until root of n, i.e. prime[1... sqrt(n)], split the complete range into blocks, and sieve each block separately. In doing so, we never have to keep multiple blocks in memory at the same time, and the CPU handles caching a lot better.

Segmented Sieve :-
The idea of segmented sieve is to divide the range [0..n-1] in different segments and compute primes 
in all segments one by one. This algorithm first uses Simple Sieve to find primes smaller than or 
equal to √(n). 
Below are steps used in Segmented Sieve.
    1. Use Simple Sieve to find all primes upto square root of ‘n’ and store these primes in an array “prime[]”. Store the found primes in an array ‘prime[]’.
    2. We need all primes in range [0..n-1]. We divide this range in different segments such that size of every segment is at-most √n
    3. Do following for every segment [low..high] 
        a. Create an array mark[high-low+1]. Here we need only O(x) space where x is number of elements in given range.
        b. Iterate through all primes found in step 1. For every prime, mark its multiples in given range [low..high].

In Simple Sieve, we needed O(n) space which may not be feasible for large n. Here we need O(√n) space and we process smaller ranges at a time (locality of reference).
Note that time complexity (or number of operations) by Segmented Sieve is same as Simple Sieve. It has advantages for large ‘n’ as it has better locality of 
reference thus allowing better caching by the CPU and also requires less memory space.
*/

#include <bits/stdc++.h>
using namespace std;

#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL);
#define endl "\n"
#define MAX_SIZE 1e10

using ll = long long;


vector <ll> seive_normal(ll n)
{
    vector <bool> marker(n+1, true);

    for(ll i=2; i*i <= n; i++)
    {
        if(marker[i])
        {
            for(ll j=i*i; j <= n; j += i)
                marker[j] = false;
        }
    }
    marker[0] = marker[1] = false;      // for 0 and 1 as they're not prime numbers

    vector <ll> is_prime;

    is_prime.push_back(2);      // as we know 2 is the only even prime
    for(ll i=3; i <= n; i+= 2)
        if(marker[i])
            is_prime.push_back(i);

    return is_prime;
}

void segmented_seive(ll low, ll high, vector <ll> primes)
{
    vector <bool> mark (high-low+1, true);

    for(ll i=0; primes[i]*primes[i] <= high; i++)
    {
        ll p = primes[i];
        ll base_start = (low / p) * p;


        if(base_start < low)
            base_start += p;
        if(base_start == p)
            base_start += p;

        for(ll j = base_start; j <= high; j += p)
            mark[j-low] = false;
        
    }

    for(ll k=low; k <= high; k++)
        if(mark[k - low] && k != 1)
            cout << k << " ";
    cout << endl;
}

int main(void)
{
    fast_io;

    ll sq = sqrt(MAX_SIZE);
    vector <ll> primes = seive_normal(sq);
    
    /*
    for(auto i: primes)
        cout << i<< "  ";
    cout << endl; */

    int t;
    cin >> t;

    while (t--)
    {
        ll low, high;
        cin >> low >> high;

        segmented_seive(low, high, primes);
    }    
    return 0;
}