/*
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
*/

// C++ program Miller-Rabin primality test
#include <bits/stdc++.h>
using namespace std;

// Utility function to do modular exponentiation.
// It returns (x^y) % p
int power(int x, unsigned int y, int p)
{
	int res = 1;	 // Initialize result
	x = x % p; // Update x if it is more than or
				// equal to p
	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res*x) % p;

		// y must be even now
		y = y>>1; // y = y/2
		x = (x*x) % p;
	}
	return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that d*2<sup>r</sup> = n-1
// for some r >= 1
bool miillerTest(int d, int n)
{
	// Pick a random number in [2..n-2]
	// Corner cases make sure that n > 4
	int a = 2 + rand() % (n - 4);

	// Compute a^d % n
	int x = power(a, d, n);

	if (x == 1 || x == n-1)
	return true;

	// Keep squaring x while one of the following doesn't
	// happen
	// (i) d does not reach n-1
	// (ii) (x^2) % n is not 1
	// (iii) (x^2) % n is not n-1
	while (d != n-1)
	{
		x = (x * x) % n;
		d *= 2;

		if (x == 1)	 return false;
		if (x == n-1) return true;
	}

	// Return composite
	return false;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
	// Corner cases
	if (n <= 1 || n == 4) return false;
	if (n <= 3) return true;

	// Find r such that n = 2^d * r + 1 for some r >= 1
	int d = n - 1;
	while (d % 2 == 0)
		d /= 2;

	// Iterate given nber of 'k' times
	for (int i = 0; i < k; i++)
		if (!miillerTest(d, n))
			return false;

	return true;
}

// Driver program
int main()
{
	int k = 5; // Number of iterations

	cout << "All primes smaller than 1000: \n";
	for (int n = 1; n < 1000; n++)
	    if (isPrime(n, k))
		    cout << n << " ";

	return 0;
}
