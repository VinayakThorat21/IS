#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// Function to generate SHA-256 K constants
std::vector<unsigned int> generateKConstants() {
    std::vector<unsigned int> K;
    int count = 0;
    for (int i = 2; count < 64; ++i) {
        bool isPrime = true;
        for (int j = 2; j <= std::sqrt(i); ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            double cubeRootFraction = std::fmod(std::pow(i, 1.0 / 3.0), 1.0);
            unsigned int constant = static_cast<unsigned int>(cubeRootFraction * std::pow(2, 32));
            K.push_back(constant);
            count++;
        }
    }
    return K;
}

// Function to generate SHA-256 H constants
std::vector<unsigned int> generateHConstants() {
    std::vector<unsigned int> H;
    int count = 0;
    for (int i = 2; count < 8; ++i) {
        bool isPrime = true;
        for (int j = 2; j <= std::sqrt(i); ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            double squareRootFraction = std::fmod(std::sqrt(i), 1.0);
            unsigned int constant = static_cast<unsigned int>(squareRootFraction * std::pow(2, 32));
            H.push_back(constant);
            count++;
        }
    }
    return H;
}

int main() {
    // Generate K constants
    std::vector<unsigned int> K = generateKConstants();
    std::cout << "// SHA-256 Constants\n";
    std::cout << "const unsigned int K[64] = {\n    ";
    for (int i = 0; i < 64; ++i) {
        std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << K[i];
        if (i != 63) std::cout << ", ";
        if ((i + 1) % 8 == 0) std::cout << "\n    ";
    }
    std::cout << "\n};\n\n";

    // Generate H constants
    std::vector<unsigned int> H = generateHConstants();
    std::cout << "unsigned int H[8] = {\n    ";
    for (int i = 0; i < 8; ++i) {
        std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << H[i];
        if (i != 7) std::cout << ", ";
    }
    std::cout << "\n};\n";

    return 0;
}
