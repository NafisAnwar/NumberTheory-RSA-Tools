#include <stdio.h>
#include <stdlib.h>

// Function to compute the greatest common divisor (Euclid's Algorithm)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// This function performs the Extended Euclidean Algorithm on a and b.
// It returns the gcd(a,b) and sets *x and *y such that a*x + b*y = gcd(a,b).
// We'll also print a table of the steps as requested.
long long extended_euclidean_table(long long a, long long b, long long *x, long long *y) {
    // We'll store the steps in arrays for printing
    // In practice, the number of steps is at most the number of digits of a, but let's just assume a safe upper bound.
    const int MAX_STEPS = 100;
    long long r[MAX_STEPS], q[MAX_STEPS], X[MAX_STEPS], Y[MAX_STEPS];
    int i = 0;

    // Initialize:
    // According to a common convention for extended Euclidean:
    // r[-1] = a, r[0] = b
    // x[-1]=1, y[-1]=0; x[0]=0, y[0]=1
    // but since we don't have negative indexing easily in C, we shift the indices by 1.
    // We'll do:
    // i= -1 corresponds to i=0 in arrays: r[0] = a, x[0]=1,y[0]=0
    // i= 0 corresponds to i=1 in arrays: r[1] = b, x[1]=0,y[1]=1

    r[0] = a; X[0] = 1; Y[0] = 0;
    r[1] = b; X[1] = 0; Y[1] = 1;

    // Print header for the table
    printf("\nExtended Euclidean Algorithm Steps:\n");
    printf("-----------------------------------------------------------------\n");
    printf("| i  |   q_i  |     r_i     |    x_i    |    y_i    |\n");
    printf("-----------------------------------------------------------------\n");

    // Print initial known rows:
    // i = -1 -> i=0 in code: no q for the first line, so we can just print '-'
    printf("| %2d |    -   | %11lld | %9lld | %9lld |\n", -1, r[0], X[0], Y[0]);
    printf("| %2d |    -   | %11lld | %9lld | %9lld |\n",  0, r[1], X[1], Y[1]);

    // Now iterate
    int step = 1;
    // We'll proceed until we find remainder 0 or exceed steps
    while (step < MAX_STEPS) {
        int i1 = step - 1; // corresponds to r[i], x[i], y[i]
        int i2 = step;     // corresponds to r[i+1], x[i+1], y[i+1]
        int i3 = step + 1; // next index for new row

        if (r[i2] == 0) {
            // we reached the end
            break;
        }

        q[i3] = r[i1] / r[i2];
        r[i3] = r[i1] % r[i2];
        X[i3] = X[i1] - q[i3] * X[i2];
        Y[i3] = Y[i1] - q[i3] * Y[i2];

        printf("| %2d | %6lld | %11lld | %9lld | %9lld |\n", step, q[i3], r[i3], X[i3], Y[i3]);

        if (r[i3] == 0) {
            // gcd found at previous remainder
            // The gcd is r[i2]
            // The coefficients are X[i2], Y[i2]
            *x = X[i2];
            *y = Y[i2];
            return r[i2];
        }

        step++;
    }

    // If we somehow didn't return inside the loop:
    // Just use the last computed values
    *x = X[step];
    *y = Y[step];
    return r[step];
}

long long mod_inverse(long long e, long long phi_n) {
    long long x, y;
    // Call with (e, phi_n)
    long long g = extended_euclidean_table(e, phi_n, &x, &y);
    if (g != 1) {
        // Inverse doesn't exist
        return -1;
    } else {
        // Normalize x to be in [0, phi_n-1]
        return (x % phi_n + phi_n) % phi_n;
    }
}


int main(void) {
    long long p, q, e;
    printf("Enter prime p: ");
    scanf("%lld", &p);

    printf("Enter prime q: ");
    scanf("%lld", &q);

    printf("Enter public exponent e: ");
    scanf("%lld", &e);

    // Compute n and phi(n)
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);

    printf("\n n = p*q = %lld\n", n);
    printf(" phi(n) = (p-1)*(q-1) = %lld\n", phi_n);

    // Print the definition of E(x)
    printf("\nE(x) = x^(%lld) mod %lld\n", e, n);

    // Compute gcd(phi(n), e) and also find the inverse d
    // The extended_euclidean_table function will print the steps and return the gcd and set x,y.
    // But we call mod_inverse(e, phi_n) which encapsulates this logic.
    long long d = mod_inverse(e, phi_n);

    if (d == -1) {
        printf("\nNo modular inverse found. gcd(phi(n), e) != 1.\n");
        return 1;
    }

    // Check that d*e ≡ 1 (mod phi(n))
    long long check = (d * e) % phi_n;
    printf("\nd = %lld (the modular inverse of e mod phi(n))\n", d);
    printf("Verify: (d*e) mod phi(n) = %lld\n", check);
    if (check == 1) {
        printf("Verification successful: d*e ≡ 1 (mod phi(n))\n");
    } else {
        printf("Verification failed: d*e ≢ 1 (mod phi(n))\n");
    }

    return 0;
}
