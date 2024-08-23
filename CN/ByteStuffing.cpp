#include <bits/stdc++.h>
using namespace std;
string encodingbyte(const string &input) {
    string output = "FLAG"; 
    for (char c : input) {
        if (c == 'FLAG' || c == 'ESC') {
            output += "ESC";
        }
        output += c;
    }
    output += "FLAG"; 
    return output;
}

string decodingbyte(const string &input) {
    string output;
    bool escape = false;
    for (size_t i = 4; i < input.size() - 4; ++i) { // Skip the FLAG at the start and end
        if (escape) {
            output += input[i];
            escape = false;
        } else if (input.substr(i, 3) == "ESC") {
            escape = true;
            i += 2; 
        } else {
            output += input[i];
        }
    }
    return output;
}

int main() {
    string data = "HELLO";
    string encoded = encodingbyte(data);
    string decoded = decodingbyte(encoded);

    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
