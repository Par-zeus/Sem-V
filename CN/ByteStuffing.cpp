#include <bits/stdc++.h>
using namespace std;

string encodingbyte(const string &input) {
    string output = "FLAG"; 
    size_t i = 0;

    while (i < input.size()) {
        if (input.substr(i, 4) == "FLAG" || input.substr(i, 3) == "ESC") {
            output += "ESC";
            output += input.substr(i, input.substr(i, 4) == "FLAG" ? 4 : 3);
            i += (input.substr(i, 4) == "FLAG" ? 4 : 3);
        } else {
            output += input[i];
            i++;
        }
    }

    output += "FLAG"; 
    return output;
}

string decodingbyte(const string &input) {
    string output;
    bool escape = false;

    for (int i = 4; i < input.size() - 4; ++i) { // Skip the FLAG at the start and end
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
    string data = "FLAG A FLAG C FLAG";
    string encoded = encodingbyte(data);
    string decoded = decodingbyte(encoded);

    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
