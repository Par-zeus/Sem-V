#include <bits/stdc++.h>
using namespace std;

string encodechar(const vector<string> &frames) {
    string output;
    for (const auto &frame : frames) {
        output += to_string(frame.size() + 1); 
        output += frame;
    }
    return output;
}

vector<string> decodingchar(const string &input) {
    vector<string> frames;
    int i = 0;
    
    while (i < input.size()) {
        int length = input[i] - '0'; 
        frames.push_back(input.substr(i + 1, length - 1)); 
        i += length; 
    }
    
    return frames;
}

int main() {
    vector<string> dataFrames = {"123", "WORLD", "TEST"};
    
    
    string encoded = encodechar(dataFrames);
    cout << "Encoded: " << encoded << endl;
    
    vector<string> decodedFrames = decodingchar(encoded);
    cout << "Decoded Frames:" << endl;
    for (const auto &frame : decodedFrames) {
        cout << frame << endl;
    }
    
    return 0;
}
