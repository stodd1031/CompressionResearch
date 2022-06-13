/* C++ program to find a prime factor of composite using
   Pollard's Rho algorithm */
#include <bits/stdc++.h>
using namespace std;

#include "pollardrho.h"

/* Function to calculate (base^exponent)%modulus */
long long int modular_pow(long long int base, int exponent,
                          long long int modulus)
{
    /* initialize result */
    long long int result = 1;

    while (exponent > 0)
    {
        /* if y is odd, multiply base with result */
        if (exponent & 1)
            result = (result * base) % modulus;

        /* exponent = exponent/2 */
        exponent = exponent >> 1;

        /* base = base * base */
        base = (base * base) % modulus;
    }
    return result;
}

/* method to return prime divisor for n */
long long int PollardRho(long long int n)
{
    /* initialize random seed */
    srand(time(NULL));

    /* Initialize candidate divisor (or result) */
    long long int d = 1;

    /* no prime divisor for 1 */
    if (n == 1)
        return n;

    /* even number means one of the divisors is 2 */
    if (n % 2 == 0)
        return 2;

    for (unsigned long index = 1; index <= n; index++)
    {

        /* the constant in f(x).
         * Algorithm can be re-run with a different c
         * if it throws failure for a composite. */
        for (unsigned long index2 = 2; index2 <= n; index2++)
        {
            // long long int c = (rand() % (n - 1)) + 1;
            long long int c = index;

            /* we will pick from the range [2, N) */
            // long long int x = (rand() % (n - 2)) + 2;
            long long int x = index2;
            long long int y = x;

            /* until the prime factor isn't obtained.
               If n is prime, return n */
            while (d == 1)
            {
                /* Tortoise Move: x(i+1) = f(x(i)) */
                x = (modular_pow(x, 2, n) + c + n) % n;

                /* Hare Move: y(i+1) = f(f(y(i))) */
                y = (modular_pow(y, 2, n) + c + n) % n;
                y = (modular_pow(y, 2, n) + c + n) % n;

                /* check gcd of |x-y| and n */
                d = __gcd(abs(x - y), n);

                /* retry if the algorithm fails to find prime factor
                 * with chosen x and c */
                // if (d == n)
                //     return PollardRho(n);
                if (d != n && d != 1)
                {
                    // std::cout << "num: " << n << std::endl;
                    // std::cout << "d: " << d << std::endl;
                    return d;
                }
            }
        }
    }

    return n;
}

MyArr<unsigned long> getFactorsPollard(unsigned long num)
{
    MyArr<unsigned long> ret;
    while (num != 1)
    {
        unsigned long long int prime = PollardRho(num);
        // std::cout << PollardRho(prime) << " " << prime << std::endl;
        if (PollardRho(prime) != prime)
        {
            MyArr<unsigned long> factors = getFactorsPollard(prime);
            for (int index = 0; index < factors.size(); index++)
            {
                ret.push_back(factors[index]);
            }
        }
        num = num / prime;
        ret.push_back(prime);
    }
    return ret;
}
