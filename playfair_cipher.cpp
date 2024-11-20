#include<iostream>
#include<map>
#include<vector>

using namespace std;

vector<vector<char>> matrix;
map<char, pair<int, int>> inverseMatrix;

void buildMatrix(string key) {
    matrix = vector<vector<char>>(5, vector<char>(5));
    int k = 0, len = key.length();
    int nextAlpha = 'a';

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            bool valueSet = false;

            if(k < len) {
                while(k < len && !valueSet) {
                    if(inverseMatrix.find(key[k]) == inverseMatrix.end()) {
                        matrix[i][j] = key[k];
                        inverseMatrix[key[k]] = make_pair(i, j);
                        valueSet = true;

                        if(key[k] == 'i') {
                            inverseMatrix['j'] = make_pair(i, j);
                        }
                        else if(key[k] == 'j') {
                            inverseMatrix['k'] = make_pair(i, j);
                        }
                    }
                    k++;
                }
            }
            
            while(nextAlpha <= 'z' && !valueSet) {
                if(inverseMatrix.find(nextAlpha) == inverseMatrix.end()) {
                    matrix[i][j] = nextAlpha;
                    inverseMatrix[nextAlpha] = make_pair(i, j);
                    valueSet = true;

                    if(nextAlpha == 'i') {
                        inverseMatrix['j'] = make_pair(i, j);
                    }
                    else if(nextAlpha == 'j') {
                        inverseMatrix['k'] = make_pair(i, j);
                    }
                }
                nextAlpha++;
            }
        }
    }
}

string replaceForEncryption(string digram) {
    string newDigram;
    pair<int, int> first = inverseMatrix[digram[0]], second = inverseMatrix[digram[1]];
    
    // Same row
    if(first.first == second.first) {
        newDigram += matrix[first.first][(first.second + 1) % 5];
        newDigram += matrix[second.first][(second.second + 1) % 5];
    }
    // Same column
    else if(first.second == second.second) {
        newDigram += matrix[(first.first + 1) % 5][first.second];
        newDigram += matrix[(second.first + 1) % 5][second.second];
    }
    // Rectangle
    else {
        newDigram += matrix[first.first][second.second];
        newDigram += matrix[second.first][first.second];
    }

    return newDigram;
}

string replaceForDecryption(string digram) {
    string newDigram;
    pair<int, int> first = inverseMatrix[digram[0]], second = inverseMatrix[digram[1]];
    
    // Same row
    if(first.first == second.first) {
        newDigram += matrix[first.first][(first.second + 4) % 5];
        newDigram += matrix[second.first][(second.second + 4) % 5];
    }
    // Same column
    else if(first.second == second.second) {
        newDigram += matrix[(first.first + 4) % 5][first.second];
        newDigram += matrix[(second.first + 4) % 5][second.second];
    }
    // Rectangle
    else {
        newDigram += matrix[first.first][second.second];
        newDigram += matrix[second.first][first.second];
    }

    return newDigram;
}

string encryption(string plaintext) {
    string ciphertext, digram;
    
    for(char p : plaintext) {
        if(digram.size() == 0) {
            digram += p;
        }
        else if(digram.size() == 1) {
            if(digram[0] == p) {
                digram += 'x';
            }
            else {
                digram += p;
            }

            ciphertext += replaceForEncryption(digram);
            if(digram[0] == p) digram = p;
            else digram = "";
        }
    }

    if(digram.size() == 1) {
        digram += 'x';
        ciphertext += replaceForEncryption(digram);
    }

    return ciphertext;
}

string decryption(string ciphertext) {
    string plaintext, digram;
    
    for(char c : ciphertext) {
        if(digram.size() == 0) {
            digram += c;
        }
        else if(digram.size() == 1) {
            if(digram[0] == c) {
                digram += 'x';
            }
            else {
                digram += c;
            }

            plaintext += replaceForDecryption(digram);
            if(digram[0] == c) digram = c;
            else digram = "";
        }
    }

    if(digram.size() == 1) {
        digram += 'x';
        plaintext += replaceForDecryption(digram);
    }

    return plaintext;
}

int main() {
    string key = "vinayakthorat";
    string plaintext = "korea", ciphertext;
    buildMatrix(key);

    ciphertext = encryption(plaintext);
    cout << "Ciphertext: " << ciphertext << endl;

    plaintext = decryption(ciphertext);
    cout << "Plaintext: " << plaintext << endl;

    return 0;
}