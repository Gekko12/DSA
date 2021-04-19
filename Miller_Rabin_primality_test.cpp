/*
The Miller-Rabin test extends the ideas from the Fermat test.

Fermat's little theorem states, that for a prime number p and a coprime integer a
the following equation holds:
a^(p−1) ≡ 1 mod p

In general this theorem doesn't hold for composite numbers.

This can be used to create a primality test. We pick an integer 2≤a≤p−2, and check if the equation 
holds or not. If it doesn't hold, e.g. ap−1≢1modp, we know that p cannot be a prime number. In this 
case we call the base a a Fermat witness for the compositeness of p.

However it is also possible, that the equation holds for a composite number. So if the equation 
holds, we don't have a proof for primality. We only can say that p is probably prime. If it turns out 
that the number is actually composite, we call the base a a Fermat liar.

By running the test for all possible bases a, we can actually prove that a number is prime. However 
this is not done in practice, since this is a lot more effort that just doing trial division. Instead 
the test will be repeated multiple times with random choices for a. If we find no witness for the 
compositeness, it is very likely that the number is in fact prime.

---------------------------------------------------------------------------------------------------
                                Miller-Rabin primality test
---------------------------------------------------------------------------------------------------
                                ### Probabilistic version:

For an odd number n, n−1 is even and we can factor out all powers of 2. We can write:
n−1=(2^s)⋅d, with d odd.

This allows us to factorize the equation of Fermat's little theorem:
a^(n−1)≡1modn ⟺ a^((2^s)d)−1≡0modn ⟺ (a^((2^(s−1).d)+1)(a^((2^(s−1).d)−1)≡0modn
⟺(a^(2^(s−1).d)+1)(a^(2^(s−2).d)+1)(a^(2^(s−2).d)−1)≡0modn⋮
⟺(a^(2^(s−1).d)+1)(a^(2^(s−2).d)+1)⋯(a^d+1)(a^d−1)≡0modn

If n is prime, then n has to divide one of these factors. And in the Miller-Rabin primality test we 
check exactly that statement, which is a more stricter version of the statement of the Fermat test. 
For a base 2≤a≤n−2 we check if either
        a^d ≡ 1modn   holds or
        a^((2^r).d) ≡ −1modn  holds for some 0≤r≤s−1.

If we found a base a which doesn't satisfy any of the above equalities, than we found a witness for 
the compositeness of n. In this case we have proven that n is not a prime number.

Similar to the Fermat test, it is also possible that the set of equations is satisfied for a 
composite number. In that case the base a is called a strong liar. If a base a satisfies the 
equations (one of them), n is only strong probable prime. However, there are no numbers like the 
Carmichael numbers, where all non-trivial bases lie. In fact it is possible to show, that at most 14 
of the bases can be strong liars. If n is composite, we have a probability of ≥75% that a random base 
will tell us that it is composite. By doing multiple iterations, choosing different random bases, we 
can tell with very high probability if the number is truly prime or if it is composite.

                                    -pseudocode -
Input #1: n > 3, an odd integer to be tested for primality
Input #2: k, the number of rounds of testing to perform
Output: “composite” if n is found to be composite, “probably prime” otherwise

write n as 2^r ·d + 1 with d odd (by factoring out powers of 2 from n − 1)
WitnessLoop: repeat k times:
    pick a random integer a in the range [2, n − 2]
    x ← a^d mod n
    if x = 1 or x = n − 1 then
        continue WitnessLoop
    repeat r − 1 times:
        x ← x^2 mod n
        if x = n − 1 then
            continue WitnessLoop
    return “composite”
return “probably prime”

Using repeated squaring, the running time of this algorithm is O(k log^3 n), where n is the number 
tested for primality, and k is the number of rounds performed; thus this is an efficient, 
polynomial-time algorithm. FFT-based multiplication can push the running time down to O(k log^2 n log 
log n log log log n) = Õ(k log^2 n). 

                            ### Deterministic Version:

Miller showed that it is possible to make the algorithm deterministic by only checking all 
bases ≤ O((ln n)^2). Bach later gave a concrete bound, it is only necessary to test all bases 
a≤2ln(n)^2.

This is still a pretty large number of bases. So people have invested quite a lot of computation 
power into finding lower bounds. It turns out, for testing a 32 bit integer it is only necessary to 
check the first 4 prime bases: 2, 3, 5 and 7. The smallest composite number that fails this test is 3,
215,031,751=151⋅751⋅28351. And for testing 64 bit integer it is enough to check the first 12 prime 
bases: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.

When the number n to be tested is small, trying all a < 2(ln n)2 is not necessary, as much smaller sets of potential witnesses are known to suffice. For example, Pomerance, Selfridge, Wagstaff and Jaeschke have verified that

    if n < 2,047, it is enough to test a = 2;
    if n < 1,373,653, it is enough to test a = 2 and 3;
    if n < 9,080,191, it is enough to test a = 31 and 73;
    if n < 25,326,001, it is enough to test a = 2, 3, and 5;
    if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
    if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
    if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
    if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
    if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
    if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.

Using the work of Feitsma and Galway enumerating all base 2 pseudoprimes in 2010, this was extended ,
with the first result later shown using different methods in Jiang and Deng:

if n < 3,825,123,056,546,413,051, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
if n < 18,446,744,073,709,551,616 = 2^64, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23,   
    29, 31, and 37.

Sorenson and Webster verify the above and calculate precise results for these larger than 64‐bit 
results:

if n < 318,665,857,834,031,151,167,461, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 
    29, 31, and 37.
if n < 3,317,044,064,679,887,385,961,981, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 
    29, 31, 37, and 41.

This results in the following deterministic implementation:
*/

#include <bits/stdc++.h>
using namespace std;

#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL);
using u64 = uint64_t;
using u128 = __uint128_t;       //unsigned 128-bit integer

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int main(void)
{
    //fast_io;
    int t;
    
    cout<<"Enter number of test cases :\n";
    cin>>t;
    u64 n;
    
    while(t--){
        cout<<"Enter a number for primality test :\n";
        cin>>n;

        if(MillerRabin(n))
            cout<<n<<" is a prime number.\n";
        else
            cout<<n<<" is not a prime number. \n";
    }
    return 0;
}