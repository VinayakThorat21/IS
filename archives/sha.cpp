#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <iomanip>

using namespace std;

// SHA-256 Constants
const unsigned int K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Helper functions
unsigned int rightRotate(unsigned int value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}

vector<unsigned char> padMessage(const string &message) {
    vector<unsigned char> padded;
    padded.insert(padded.end(), message.begin(), message.end());
    
    // Append the '1' bit (0x80 in hex)
    padded.push_back(0x80);
    
    // Add padding of '0' bits until length is 64 bits shy of a multiple of 512
    while ((padded.size() * 8) % 512 != 448) {
        padded.push_back(0x00);
    }
    
    // Append original message length in bits as a 64-bit big-endian integer
    unsigned long long bitLength = message.size() * 8;
    for (int i = 7; i >= 0; i--) {
        padded.push_back((bitLength >> (i * 8)) & 0xFF);
    }

    return padded;
}

unsigned int H[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

void processChunk(const unsigned char *chunk) {
    unsigned int w[64];

    // Prepare message schedule w
    for (int i = 0; i < 16; i++) {
        w[i] = (chunk[i * 4] << 24) | (chunk[i * 4 + 1] << 16) | (chunk[i * 4 + 2] << 8) | (chunk[i * 4 + 3]);
    }
    for (int i = 16; i < 64; i++) {
        unsigned int s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
        unsigned int s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // Initialize working variables
    unsigned int a = H[0];
    unsigned int b = H[1];
    unsigned int c = H[2];
    unsigned int d = H[3];
    unsigned int e = H[4];
    unsigned int f = H[5];
    unsigned int g = H[6];
    unsigned int h = H[7];

    // Compression function main loop
    for (int i = 0; i < 64; i++) {
        unsigned int S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
        unsigned int ch = (e & f) ^ ((~e) & g);
        unsigned int temp1 = h + S1 + ch + K[i] + w[i];
        unsigned int S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
        unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
        unsigned int temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // Add the compressed chunk to the current hash value
    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
}

string sha256(const string &message) {
    vector<unsigned char> paddedMessage = padMessage(message);

    // Process each 512-bit chunk
    for (size_t i = 0; i < paddedMessage.size(); i += 64) {
        processChunk(&paddedMessage[i]);
    }

    // Produce the final hash as a hex string
    stringstream hash;
    for (int i = 0; i < 8; i++) {
        hash << hex << setw(8) << setfill('0') << H[i];
    }
    return hash.str();
}

int main() {
    string message = "I am a software developer!", expected = "be2f213e2499c85bd5d0b0cd75dbcbfc1f270ee29e6e8185382ffa2a390956cb";
    string hash = sha256(message);

    if(hash == expected) {
        cout << "Algorithm is successful: " << hash << endl;
    } else {
        cout << "Algorithm needs fixes" << endl;
    }

    return 0;
}