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
