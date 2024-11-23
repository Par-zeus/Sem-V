#include <bits/stdc++.h>
using namespace std;

static void receiver(const string& messageSent) {
    int flag = 0;
    bool esc = false;
    char ch;
    int i = 0;
    while (i < messageSent.length()) {
        ch = messageSent[i];
        if (esc) {
            cout << ch;
            esc = false;
        } else if (ch == '$') {
            if (flag == 0) flag = 1; // Start of a frame
            else {
                flag = 0; // End of a frame
                cout << endl;
            }
        } else if (ch == '#') {
            esc = true; // ESC character found, escape the next character
        } else {
            cout << ch; // Normal character, print it
        }
        i++;
    }
}

int main() {
        string messageSent = "";
        cout << "Enter number of frames: ";
        int frames;
        cin >> frames;

        vector<string> s(frames);
        cout << "Enter the frames:\n";
        for (int i = 0; i < frames; i++) {
            cin >> s[i];

            // Perform byte stuffing
            int pos = 0;
            while ((pos = s[i].find("#", pos)) != string::npos) {
                s[i].replace(pos, 1, "##"); // Replace # with ##
                pos += 2;
            }
            pos = 0;
            while ((pos = s[i].find("$", pos)) != string::npos) {
                s[i].replace(pos, 1, "#$"); // Replace $ with #$
                pos += 2;
            }

            // Add start and end flag $
            s[i] = "$" + s[i] + "$";
        }

        for (int i = 0; i < frames; i++) {
            messageSent += s[i];
        }
        cout << "\nEncoded message:\n" << messageSent << endl;

        cout << "\nReceiver output:\n";
        receiver(messageSent);
        return 0;
    }