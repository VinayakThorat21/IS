#include <iostream>
#include <vector>
using namespace std;

string encryption(string plaintext, int m, int n, vector<int> order) {
    string ciphertext;
    int k = 0, len = plaintext.length();
    
    // Fill Matrix
    vector<vector<char>> matrix(m, vector<char>(n, '\0'));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(k == len) break;
            matrix[i][j] = plaintext[k++];
        }
        if(k == len) break;
    }

    // Create ciphertext
    for(int i : order) {
        for(int j = 0; j < m; j++) {
            ciphertext += matrix[j][i];
        }
    }

    return ciphertext;
}

string decryption(string ciphertext, int m, int n, vector<int> order) {
    string plaintext;
    int k = 0, len = ciphertext.length();

    // Fill Matrix
    vector<vector<char>> matrix(m, vector<char>(n, '\0'));

    for(int i : order) {
        for(int j = 0; j < m; j++) {
            matrix[j][i] = ciphertext[k++];
        }
    }

    // Regenerate plaintext
    for(auto mat : matrix) {
        for(char c : mat) {
            plaintext += c;
        }
    }

    return plaintext;
}

int main() {
    string plaintext = "He is out of this world!!", ciphertext;
    vector<vector<int>> orders = {{2, 4, 0, 3, 1}, {2, 0, 3, 4, 1}, {3, 0, 2, 1, 4}};

    for(auto order : orders) {
        ciphertext = encryption(plaintext, 5, 5, order);
        plaintext = ciphertext;
    }
    cout << "Ciphertext: " << ciphertext << endl;

    for(int i = orders.size() - 1; i >= 0; i--) {
        plaintext = decryption(ciphertext, 5, 5, orders[i]);
        ciphertext = plaintext;
    }
    cout << "Plaintext: " << plaintext << endl;

    return 0;
}