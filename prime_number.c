/*
    The Miller-Rabin primality test - the most efficient algorithm to check if a number is prime
- This is a probabilistic algorithm, which means that it can give incorrect results with a certain probability, 
but this probability can be made arbitrarily small by running the test multiple times.
- To perform the Miller-Rabin primality test, you need to do the following:
    + Choose a number k, which is the number of times you want to run the test.
    + For each iteration of the test (from 1 to k):
        1. Choose a random integer a between 2 and n-2, where n is the number you want to test for primality.
        2. Calculate d and s such that n-1 = d * 2^s, where d is an odd integer.
    + Calculate x = a^d mod n.
    + If x is 1 or x is n-1, go to the next iteration of the test.
    + For i from 1 to s-1:
        1. Calculate x = x^2 mod n.
        2. If x is n-1, go to the next iteration of the test.
    + If none of the above conditions were met, the number is composite.
- If the number passes all k iterations of the test, it is probably prime, although there is a small 
probability that it is actually composite. To make this probability arbitrarily small, you can increase 
the value of k. For example, if you choose k = 40, the probability of a composite number passing the test 
is less than 2^-40, which is approximately 2.2 x 10^-12.
*/

/*
The complexity of the Miller-Rabin primality test is O(k * log n), where k is the number of times the test is run 
and n is the number being tested for primality. This means that the running time of the test is directly proportional 
to the value of k and the logarithm of n.

In general, the Miller-Rabin primality test is considered to be a very efficient algorithm for testing the primality 
of large numbers. It is much faster than other deterministic primality testing algorithms, such as the AKS primality 
test or the general number field sieve, which have complexities of O(exp(1/2 * log n * log log n)) and O(exp(1/3 * log n * log log n)), respectively.

However, it is important to note that the Miller-Rabin primality test is a probabilistic algorithm, which means that 
it can give incorrect results with a certain probability, although this probability can be made arbitrarily small by 
running the test multiple times. This is in contrast to deterministic algorithms, which always give correct results.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

// Returns true if n is probably prime, false if it is definitely composite.
bool is_prime(unsigned long long n, unsigned int k)
{
    if (n <= 1)
    {
        return false;
    }
    if (n == 2 || n == 3)
    {
        return true;
    }

    if (n % 2 == 0)
    {
        return false;
    }

    unsigned long long d = n - 1;
    unsigned int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s += 1;
    }

    for (unsigned int i = 0; i < k; i++)
    {
        unsigned long long a = rand() % (n - 2) + 2;
        unsigned long long x = 1;
        for (unsigned long long j = 0; j < d; j++)
        {
            x = (x * a) % n;
        }
        if (x == 1 || x == n - 1)
        {
            continue;
        }

        for (unsigned int j = 0; j < s - 1; j++)
        {
            x = (x * x) % n;
            if (x == n - 1)
            {
                break;
            }
        }

        if (x != n - 1)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    // Seed the random number generator with the current time.
    srand(time(NULL));

    // Test if the number is prime.
    printf("%d\n", is_prime(12345678904234567890ull, 40));

    return 0;
}