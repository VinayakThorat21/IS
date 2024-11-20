#include <iostream>
using namespace std;

// GCD
int gcd(int a, int b) {
    while(b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Modular exponentiation
int modExp(int base, int exp, int mod) {
    int res = 1;
    base %= mod;

    while(exp) {
        if(exp & 1) {
            res = (res * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }

    return res;
}

// Inverse modular exponentiation
int modInv(int e, int phi) {
    int q, a = phi, b = e, r, t1 = 0, t2 = 1, t;

    while(a > b && b) {
        q = a / b;
        r = a % b;
        t = t1 - t2 * q;

        a = b; b = r;
        t1 = t2; t2 = t;
    }

    if(t1 < 0) t1 += phi;
    return t1;
}

int main() {
    // Prime numbers
    int p, q;
    cout << "Prime numbers (p and q): ";
    cin >> p >> q;

    int n = p * q, phi = (p - 1) * (q - 1);

    // Public key exponent
    int e = 2;
    while(gcd(e, phi) != 1) e++;

    // Private key exponent
    int d = modInv(e, phi);

    // Encryption
    int msg;
    cout << "Message: "; 
    cin >> msg;

    int cipher = modExp(msg, e, n);
    cout << "Cipher: " << cipher << endl;

    // Decryption
    msg = modExp(cipher, d, n);
    cout << "Message: " << msg << endl;

    return 0;
}