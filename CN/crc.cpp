#include <bits/stdc++.h>
using namespace std;
#define N strlen(gen_poly)
char data[28];
char check_value[28];
char gen_poly[10];
int data_len, i, j;

void XOR() {
    for (j = 1; j < N; j++)
        check_value[j] = (check_value[j] == gen_poly[j]) ? '0' : '1';
}

void crc() {
    for (i = 0; i < N; i++)
        check_value[i] = data[i];

    do {
        if (check_value[0] == '1')
            XOR();

        for (j = 0; j < N - 1; j++)
            check_value[j] = check_value[j + 1];

        check_value[j] = data[i++];
    } while (i <= data_len + N - 1);
}

void receiver() {
    cout << "Enter the received data: ";
    cin >> data;

  
    cout << "Data received: " << data;
    crc();

    for (i = 0; (i < N - 1) && (check_value[i] != '1'); i++);

    if (i < N - 1)
        cout << "\nError detected\n\n";
    else
        cout << "\nNo error detected\n\n";
}

int main() {
    cout << "\nEnter data to be transmitted: ";
    cin >> data;

    cout << "\nEnter the Generating polynomial: ";
    cin >> gen_poly;

    data_len = strlen(data);

    for (i = data_len; i < data_len + N - 1; i++)
        data[i] = '0';

    cout << "\nData padded with n-1 zeros: " << data;

    crc();

    cout << "\nCRC : " << check_value;

    for (i = data_len; i < data_len + N - 1; i++)
        data[i] = check_value[i - data_len];

    cout << "\n Data sent: " << data;

    receiver();

    return 0;
}

