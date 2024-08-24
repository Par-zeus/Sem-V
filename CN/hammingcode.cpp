#include <iostream>
#include <vector>

using namespace std;

// Function to encode 4-bit data into 7-bit Hamming code
void encodeHamming74(const vector<bool>& data, vector<bool>& encoded) {
    // Data bits
    encoded[2] = data[0];
    encoded[4] = data[1];
    encoded[5] = data[2];
    encoded[6] = data[3];

    // Calculate parity bits
    encoded[0] = encoded[2] ^ encoded[4] ^ encoded[6]; // P1
    encoded[1] = encoded[2] ^ encoded[5] ^ encoded[6]; // P2
    encoded[3] = encoded[4] ^ encoded[5] ^ encoded[6]; // P3
}

// Function to decode 7-bit Hamming code and detect errors
int detectErrorHamming74(const vector<bool>& encoded) {
    bool s1 = encoded[0] ^ encoded[2] ^ encoded[4] ^ encoded[6]; // P1
    bool s2 = encoded[1] ^ encoded[2] ^ encoded[5] ^ encoded[6]; // P2
    bool s3 = encoded[3] ^ encoded[4] ^ encoded[5] ^ encoded[6]; // P3

    int errorPos = s1 * 1 + s2 * 2 + s3 * 4;

    return errorPos;
}

// Function to print an array of bits
void printArray(const vector<bool>& arr) {
    for (bool bit : arr) {
        cout << bit;
    }
    cout << endl;
}

// Function to read 4-bit data from the user
void readData(vector<bool>& data) {
    cout << "Enter a 4-bit binary sequence (4 bits separated by space): ";
    for (int i = 0; i < 4; i++) {
        int bit;
        cin >> bit;
        if (bit != 0 && bit != 1) {
            cout << "Invalid input. Please enter binary digits (0 or 1)." << endl;
            exit(1);
        }
        data[i] = static_cast<bool>(bit);
    }
}

// Function to read 7-bit data from the user
void readEncodedData(vector<bool>& encoded) {
    cout << "Enter the received 7-bit binary sequence (7 bits separated by space): ";
    for (int i = 0; i < 7; i++) {
        int bit;
        cin >> bit;
        if (bit != 0 && bit != 1) {
            cout << "Invalid input. Please enter binary digits (0 or 1)." << endl;
            exit(1);
        }
        encoded[i] = static_cast<bool>(bit);
    }
}

int main() {
    vector<bool> data(4);
    vector<bool> encoded(7);
    vector<bool> received(7);

    // Read data from user
    readData(data);

    // Encoding
    encodeHamming74(data, encoded);
    cout << "Encoded: ";
    printArray(encoded);

    // Read received data from user
    readEncodedData(received);

    // Detect errors
    int errorPos = detectErrorHamming74(received);

    if (errorPos == 0) {
        cout << "No error detected." << endl;
    } else {
        cout << "Error detected at position: " << errorPos << endl;
    }

    return 0;
}

