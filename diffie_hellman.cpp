#include <iostream>
#include <set>
using namespace std;

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

int primitiveRoot(int p) {
    int g = 2;
    set<int> ans;

    while(g < p) {
        for(int i = 1; i < p; i++) {
            ans.insert(modExp(g, i, p));
        }
        if(ans.size() == p - 1) break;
        ans.clear();
        g++;
    }

    cout << "Primitive root found: " << g << endl;
    return g;
}

int main() {
    // Public parameters
    int p, g;
    cout << "Prime number: ";
    cin >> p;

    // Primitive root of p
    g = primitiveRoot(p);

    // Private keys
    int a, b;
    cout << "Alice's private key: "; cin >> a;
    cout << "Bob's private key: "; cin >> b;

    // Public keys
    int A = modExp(g, a, p), B = modExp(g, b, p);

    // Shared secret generation
    int Sa = modExp(B, a, p), Sb = modExp(A, b, p);

    // Check if keys shared with security
    if(Sa == Sb) {
        cout << "Key " << Sa << " shared securely" << endl;
    } else {
        cout << "Error occured!" << endl;
    }

    return 0;
}