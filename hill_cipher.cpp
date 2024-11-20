#include<iostream>
#include<vector>

using namespace std;
vector<vector<int>> key, inverseKey;

string multiplyMatrix(string digram) {
    string cipher = "  ";

    cipher[0] = static_cast<char>((((digram[0] - 'a') * key[0][0] + (digram[1] - 'a') * key[1][0]) % 26) + 'a');
    cipher[1] = static_cast<char>((((digram[0] - 'a') * key[0][1] + (digram[1] - 'a') * key[1][1]) % 26) + 'a');

    return cipher;
}

string multiplyInverseMatrix(string digram) {
    string plain = "  ";

    plain[0] = static_cast<char>((((digram[0] - 'a') * inverseKey[0][0] + (digram[1] - 'a') * inverseKey[1][0]) % 26) + 'a');
    plain[1] = static_cast<char>((((digram[0] - 'a') * inverseKey[0][1] + (digram[1] - 'a') * inverseKey[1][1]) % 26) + 'a');

    return plain;
}

int inverse(int k) {
    int q, a = 26, b = k, r, t1 = 0, t2 = 1, t;

    while(a > b && b) {
        r = a % b;
        q = a / b;
        t = t1 - t2 * q;

        // Shift
        a = b;
        b = r;
        t1 = t2;
        t2 = t;
    }

    return t1;
}

void buildInverseKey() {
    int k = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    k = inverse(k);
    if(k < 0) k += 26;
    
    inverseKey[0][1] = (-1) * key[0][1];
    inverseKey[1][0] = (-1) * key[1][0];
    inverseKey[0][0] = key[1][1];
    inverseKey[1][1] = key[0][0];


    inverseKey[0][0] = inverseKey[0][0] * k % 26;
    inverseKey[0][1] = (inverseKey[0][1] * k % 26) + 26;
    inverseKey[1][0] = (inverseKey[1][0] * k % 26) + 26;
    inverseKey[1][1] = inverseKey[1][1] * k % 26;
}

string encrypt(string plaintext) {
    string ciphertext;

    if(plaintext.size() % 2) plaintext += 'x';
    for(int i = 0; i < plaintext.size(); i += 2) {
        string digram;
        digram += plaintext[i];
        digram += plaintext[i + 1];
        ciphertext += multiplyMatrix(digram);
    }

    return ciphertext;
}

string decrypt(string ciphertext) {
    string plaintext;

    for(int i = 0; i < ciphertext.size(); i += 2) {
        string digram;
        digram += ciphertext[i];
        digram += ciphertext[i + 1];
        plaintext += multiplyInverseMatrix(digram);
    }

    return plaintext;
}

int main() {
    cout << "Key matrix: " << endl;
    key = vector<vector<int>>(2, vector<int>(2));

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cin >> key[i][j];
        }
    }

    inverseKey = vector<vector<int>>(2, vector<int>(2));
    buildInverseKey();
    cout << "Inverse matrix: " << endl;
    for(vector<int> i : inverseKey) {
        for(int j : i) {
            cout << j << "\t";
        }
        cout << endl;
    }

    string plaintext, ciphertext;

    plaintext = "iamincredible";
    ciphertext = encrypt(plaintext);
    plaintext = decrypt(ciphertext);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}