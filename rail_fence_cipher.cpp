#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> charCount(string text, int depth) {
    vector<int> count(depth, 0);
    int i(0), len(text.length());
    bool up(false);

    while(len--) {
        if(i == 0) {
            up = false;
        } else if(i == depth - 1) {
            up = true;
        }

        count[i]++;
        i += (up ? -1 : 1);
    }

    return count;
}

string encryption(string plaintext, int depth) {
    string ciphertext;
    int i = 0;
    bool up = false;

    vector<string> layers(depth);
    for(char c : plaintext) {
        if(i == 0) {
            up = false;
        } else if(i == depth - 1) {
            up = true;
        }

        layers[i] += c;
        i += (up ? -1 : 1);
    }

    for(string layer : layers) {
        ciphertext += layer;
    }

    return ciphertext;
}

string decryption(string ciphertext, int depth) {
    string plaintext;
    vector<int> count = charCount(ciphertext, depth);
    vector<string> layers;
    int len = ciphertext.length(), k = 0;
    bool up = false;

    // Get slices
    for(int i = 0, j = 0; i < len && j < depth; i += count[j++]) {
        string layer = ciphertext.substr(i, count[i]);
        reverse(layer.begin(), layer.end());
        layers.push_back(layer);
    }

    // Regenerate plaintext
    while(len--) {
        if(k == 0) {
            up = false;
        } else if(k == depth - 1) {
            up = true;
        }

        plaintext += layers[k].back();
        layers[k].pop_back();

        k += (up ? -1 : 1);
    }

    return plaintext;
}

int main() {
    string plaintext = "vinayakthorat", ciphertext;
    ciphertext = encryption(plaintext, 3);
    plaintext = decryption(ciphertext, 3);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    return 0;
}