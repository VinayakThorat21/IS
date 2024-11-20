#include <iostream>
using namespace std;

string caesarCipher(string msg, int key, bool encrypt = true) {
    int len = msg.length();
    key %= 26;

    for(int i = 0; i < len; i++) {
        int ch = msg[i];
        if(msg[i] >= 'a' && msg[i] <= 'z') {
            // Bring down the character
            ch -= 'a';

            // Step based on technique encryption/decryption
            if(encrypt) ch += key;
            else ch -= key;
            ch %= 26;

            // Handle negative modulo
            ch += (ch < 0 ? 26 : 0);

            // Lift up character
            ch += 'a';
        }

        msg[i] = static_cast<char>(ch);
    }

    return msg;
}

int main() {
    string message = "i am living in kalvade, with my family and friends. now i will be working as a software developer at pune!";
    int key = 21;

    string ciphertext = caesarCipher(message, key);
    string plaintext = caesarCipher(ciphertext, key, false);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}