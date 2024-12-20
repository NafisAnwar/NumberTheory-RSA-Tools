# NumberTheory-RSA-Tools
A simple demonstration of RSA key generation, encryption/decryption, and related discrete math computations for educational purposes.

# RSA-DiscreteMath-Playground

This repository provides a practical, educational introduction to RSA cryptography and related discrete mathematics concepts. It is designed for students learning about number theory, the Euler Phi function, modular arithmetic, and the RSA algorithm’s fundamental steps.

## Features

- **RSA Key Generation**: Compute `n = p*q`, `φ(n)`, and the public/private keys `(e, d)`.
- **Encryption & Decryption**: Demonstrate `E(x) = x^e mod n` and `D(x) = x^d mod n`.
- **Extended Euclidean Algorithm**: Implement and showcase the steps for finding `d` such that `(d*e) mod φ(n) = 1`.
- **Repeated Squaring**: Efficiently compute large modular exponentiations.
- **Additional Computations**: Illustrate how to compute `φ(φ(n))`, verify Euler’s theorem, and sign messages digitally using RSA.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`) installed on your system.
- Basic knowledge of the command line to compile and run the programs.
- Familiarity with C programming and arithmetic operations.

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/your-username/RSA-DiscreteMath-Playground.git

2. Navigate to the project directory:

   cd RSA-DiscreteMath-Playground

3. Compile the main program:

   gcc rsa_program.c -o rsa_program

4. Running the Program

   Execute the binary:
   ./rsa_program
   
5. Follow the on-screen prompts to:

   Enter your primes p, q, and exponent e.
   Compute n, φ(n), and the modular inverse d.
   Encrypt/decrypt sample messages.
   Demonstrate repeated squaring and verify theoretical computations like E(D(x)) = x.

## Customization
Modify p, q, and e directly in the source code if you prefer not to prompt for them.
Add additional functions for factorization, computing φ(φ(n)), or verifying Euler’s theorem.
Extend the program to accept larger primes for a more realistic demonstration (though performance and security are not    the primary goals).

## Educational Use
This code and workflow is ideal for students completing discrete math or introductory cryptography assignments. It shows how theory translates into working code and provides a transparent view into each step of the RSA process.

## Contributing
Contributions are welcome! If you have suggestions for improvements, additional features, or educational aids:

##Fork the repository.
Create a new branch with a descriptive name.
Make your changes and submit a pull request.
