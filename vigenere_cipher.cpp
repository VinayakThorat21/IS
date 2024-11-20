#include <iostream>
using namespace std;

string vigenereCipher(string msg, string key, bool encrypt = true) {
    int len = msg.length();

    for(int i = 0; i < len; i++) {
        int ch = msg[i];
        if(ch >= 'a' && ch <= 'z') {
            // Bring down character
            ch -= 'a';

            // Step up or down based on encryption/decryption
            if(encrypt) {
                ch += key[i % key.length()];
            } else {
                ch -= key[i % key.length()];
            }
            ch %= 26;

            // Check for negative modulo
            ch += (ch < 0 ? 26 : 0);

            // Uplift character
            ch += 'a';
        }

        msg[i] = static_cast<char>(ch);
    }

    return msg;
}

int main() {
    string message = "i am living in kalvade, with my family and friends. now i will be sowrking as a software developer at pune!", key = "infotech";
    string ciphertext = vigenereCipher(message, key);
    string plaintext = vigenereCipher(ciphertext, key, false);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}