#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Compute gcd
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find x,y such that a*x + b*y = gcd(a,b)
long long extended_euclidean(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_euclidean(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a/b)*y1;
    return g;
}

// Compute modular inverse of e mod phi_n
long long mod_inverse(long long e, long long phi_n) {
    long long x, y;
    long long g = extended_euclidean(e, phi_n, &x, &y);
    if (g != 1) return -1;
    long long d = (x % phi_n + phi_n) % phi_n;
    return d;
}

// Modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    long long cur = base % mod;
    long long e = exp;
    while (e > 0) {
        if (e & 1) {
            result = (result * cur) % mod;
        }
        cur = (cur * cur) % mod;
        e >>= 1;
    }
    return result;
}

// Factor a number into its prime factors and return them along with their powers.
// We'll store them in arrays factors[] and powers[], and return the count of distinct factors.
int factorize(long long n, long long factors[], long long powers[]) {
    int count = 0;
    // Check factor 2
    while (n % 2 == 0) {
        if (count == 0 || factors[count-1] != 2) {
            factors[count] = 2;
            powers[count] = 1;
            count++;
        } else {
            powers[count-1]++;
        }
        n /= 2;
    }

    // Check odd factors
    for (long long i = 3; i*i <= n; i += 2) {
        while (n % i == 0) {
            if (count == 0 || factors[count-1] != i) {
                factors[count] = i;
                powers[count] = 1;
                count++;
            } else {
                powers[count-1]++;
            }
            n /= i;
        }
    }

    // If remaining n > 1, it is a prime factor
    if (n > 1) {
        factors[count] = n;
        powers[count] = 1;
        count++;
    }

    return count;
}

// Compute phi(m) given prime factorization of m
// phi(m) = m * Π (1 - 1/p) for each prime factor p
long long phi_of(long long m) {
    // Factorize m
    long long factors[50], powers[50];
    int fcount = factorize(m, factors, powers);

    // phi(m) = m * product(1 - 1/p) = m * product((p-1)/p)
    // = m * Π (p-1)/p
    // We'll compute this directly: phi(m) = m * Π (p-1)/p
    long long phi = m;
    for (int i = 0; i < fcount; i++) {
        long long p = factors[i];
        phi = phi - phi/p; // standard formula: phi(m) = m Π (1 - 1/p)
    }
    return phi;
}

// Print binary decomposition of exponent
// We'll also return the number of bits used
int print_binary_decomposition(long long exponent) {
    printf("\nφ(φ(n))-1 = %lld\n", exponent);
    printf("Binary decomposition (from LSB to MSB): ");
    long long temp = exponent;
    int bits = 0;
    while (temp > 0) {
        printf("%d", (int)(temp & 1));
        temp >>= 1;
        bits++;
    }
    printf(" (reversed order: from least significant bit first)\n");
    return bits;
}

int main(void) {
    long long p, q, e;
    // Prompt for p, q, e (same values as Problem 1)
    printf("Enter prime p: ");
    scanf("%lld", &p);

    printf("Enter prime q: ");
    scanf("%lld", &q);

    printf("Enter public exponent e: ");
    scanf("%lld", &e);

    // Compute n and phi(n)
    long long n = p * q;
    long long phi_n = (p - 1)*(q - 1);

    printf("\nn = %lld\n", n);
    printf("phi(n) = %lld\n", phi_n);

    // From Problem 1, we had d as the inverse of e mod phi(n). Let's recompute for reference.
    long long d = mod_inverse(e, phi_n);
    if (d == -1) {
        printf("No modular inverse found. Check p,q,e.\n");
        return 1;
    }
    printf("\nPreviously computed d = %lld (mod phi(n))\n", d);

    // Problem 2 steps:
    // 2. Compute phi(phi(n))
    long long phi_phi_n = phi_of(phi_n);
    printf("\nphi(phi(n)) = %lld\n", phi_phi_n);

    // 3. Now subtract 1 from this result:
    long long exponent = phi_phi_n - 1;
    printf("phi(phi(n))-1 = %lld\n", exponent);

    // 4. Now we compute e^(phi(phi(n))-1) mod phi(n)
    // We must use repeated squaring and print out all repeated squares up to at least the largest power needed.

    // To know how many powers of two we need, find the highest power of 2 that is <= exponent.
    // We'll compute repeated squares until we exceed exponent.
    // We'll store and print them in a table.
    printf("\nCompute all repeated squares of e modulo phi(n):\n");
    printf("------------------------------------------------\n");
    printf("   Exponent   |      e^(Exponent) mod phi(n)\n");
    printf("------------------------------------------------\n");

    // We'll compute powers: e^(1), e^(2), e^(4), e^(8), ... until we exceed exponent
    // Just do up to a certain large power. For safety, let's do up to 65536 as in your example.
    // Adapt if needed.
    long long max_power = 65536; // adjust if phi(phi(n))-1 < 65536 or is much bigger
    long long current = e % phi_n;
    long long power_val = 1;
    printf("e^1 mod phi(n)= %lld\n", current);
    long long results[20]; // store results for powers of 2
    results[0] = current; // e^1

    int count = 1;
    while ((1LL << count) <= max_power) {
        current = (current * current) % phi_n;
        printf("e^%lld mod phi(n)= %lld\n", (1LL << count), current);
        results[count] = current;
        count++;
        if ((1LL << count) > exponent) {
            break;
        }
    }

    // 7. Write φ(φ(n))-1 as sum of powers of 2 in ascending order.
    // We'll also pick out which results we need.
    printf("\nNow, express φ(φ(n))-1 in binary form:\n");
    // Let's print decomposition in ascending order:
    long long temp = exponent;
    long long power = 1;
    int idx = 0;
    printf("φ(φ(n))-1 = ");
    int started = 0;
    // We'll also store which indices of results we use
    int used_indices[64];
    int used_count = 0;
    while (temp > 0) {
        if (temp & 1) {
            if (started) printf(" + ");
            printf("%lld", power);
            started = 1;
            // Find which power of two this is
            int log_p = 0;
            long long pp = power;
            while (pp > 1) {pp >>= 1; log_p++;}
            // log_p gives us the index in results array: e^(2^log_p)
            used_indices[used_count++] = log_p;
        }
        power <<= 1;
        temp >>= 1;
    }
    printf("\n");

    // 8. According to this expression, print out the values from the repeated squares:
    printf("\nThe repeated squares used for the final calculation:\n");
    for (int i = 0; i < used_count; i++) {
        long long pow_val = (1LL << used_indices[i]);
        printf("e^%lld mod phi(n) = %lld\n", pow_val, results[used_indices[i]]);
    }

    // 9. Now write e^(phi(phi(n))-1) as an unevaluated product:
    printf("\ne^(φ(φ(n))-1) = ");
    for (int i = 0; i < used_count; i++) {
        if (i > 0) printf(" * ");
        long long pow_val = (1LL << used_indices[i]);
        printf("(e^%lld mod phi(n))", pow_val);
    }
    printf("\n");

    // 10. Evaluate the product modulo phi(n).
    // Let's compute it:
    long long final_result = 1;
    for (int i = 0; i < used_count; i++) {
        final_result = (final_result * results[used_indices[i]]) % phi_n;
    }

    printf("\ne^(φ(φ(n))-1) mod phi(n) = %lld\n", final_result);

    // If we did everything correctly, final_result should be equal to the original d (the inverse).
    printf("\nPreviously computed d was %lld.\n", d);
    if (final_result == d) {
        printf("This matches the previously computed d!\n");
    } else {
        printf("This does NOT match the previously computed d. Check calculations.\n");
    }

    // 11. If we let d = final_result above, the theorem that justifies that de ≡ 1 (mod φ(n)) is Euler's Theorem.
    // Just print it:
    printf("\nBy Euler's Theorem (or a direct result of the Extended Euclidean Algorithm), we conclude d and e are inverses mod φ(n).\n");

    return 0;
}
