#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcd function
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find x,y for a*x + b*y = gcd(a,b)
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

// modular inverse
long long mod_inverse(long long e, long long phi_n) {
    long long x, y;
    long long g = extended_euclidean(e, phi_n, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % phi_n + phi_n) % phi_n;
}

// modular exponentiation
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
    long long phi_n = (p - 1)*(q - 1);

    // Compute d
    long long d = mod_inverse(e, phi_n);
    if (d == -1) {
        printf("No modular inverse found. Check your values.\n");
        return 1;
    }

    printf("\nn = %lld\n", n);
    printf("phi(n) = %lld\n", phi_n);
    printf("d (inverse of e mod phi(n)) = %lld\n", d);
    printf("\nD(x) = x^%lld mod %lld\n", d, n);

    // Get U-number from user (e.g. "U20920991" or something similar)
    // We'll assume the U-number is something like "U20920991".
    // If the user just has digits, adjust accordingly.
    // We only care about the digits. Let's strip the leading 'U' if present.
    char U_number[100];
    printf("\nEnter your U-Number (e.g. U20920991): ");
    scanf("%s", U_number);

    // Strip leading non-digit characters if any
    int start_index = 0;
    while (U_number[start_index] && (U_number[start_index] < '0' || U_number[start_index] > '9')) {
        start_index++;
    }

    char *digits = U_number + start_index; // pointer to the first digit
    int length = (int)strlen(digits);

    // Create the table
    // k is the position of the digit from the left, starting at 1
    // digit (t) is the character converted to int
    // x = 10k + t
    // D(x) = x^d mod n
    printf("\n-------------------------------------------------\n");
    printf("|  k  | Digit (t) |  x=10k+t  |      D(x)       |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < length; i++) {
        int k = i + 1;
        int t = digits[i] - '0'; // convert char to int
        long long x = 10*k + t;
        long long D_x = mod_exp(x, d, n);
        printf("| %2d |     %d     |   %6lld  |   %10lld   |\n", k, t, x, D_x);
    }
    printf("-------------------------------------------------\n");

    // Optional: Verify E(D(x)) = x for each value
    // This is a check on your work. You can comment this out if not required.
    printf("\nVerification check (E(D(x)) should equal x):\n");
    printf("-------------------------------------------------\n");
    printf("|  k  |   x   |   D(x)   | E(D(x)) mod n | Check |\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        int k = i + 1;
        int t = digits[i] - '0';
        long long x = 10*k + t;
        long long D_x = mod_exp(x, d, n);
        long long E_of_Dx = mod_exp(D_x, e, n);
        printf("| %2d | %5lld | %8lld | %13lld  |", k, x, D_x, E_of_Dx);
        if (E_of_Dx == x) printf("  OK  |\n");
        else printf(" FAIL |\n");
    }
    printf("-------------------------------------------------\n");

    printf("\nIf all checks show 'OK', then E(D(x)) = x for all digits.\n");
    printf("This confirms that D and E are indeed inverses modulo n, and we have successfully signed each digit.\n");

    return 0;
}
