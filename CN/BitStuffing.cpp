#include <bits/stdc++.h>
using namespace std;
string encodingbit(const string &input) {
    string output;
    int count = 0;
    for (char bit : input) {
        output += bit;
        if (bit == '1') {
            count++;
            if (count == 5) {
                output += '0'; // Stuff a '0' after five consecutive '1's
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    return "01111110" + output + "01111110"; 
}

string decodingbit(const string &input) {
    string output;
    int count = 0;
    for (int i = 8; i < input.size() - 8; ++i) { // Skip the FLAG at the start and end
        if (input[i] == '1') {
            count++;
            output += input[i];
            if (count == 5) {
                if (input[i + 1] == '0') {
                    i++; 
                }
                count = 0;
            }
        } else {
            output += input[i];
            count = 0;
        }
    }
    return output;
}

int main() {
    string data = "011111110111111001111";
    string encoded = encodingbit(data);
    string decoded = decodingbit(encoded);

    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
