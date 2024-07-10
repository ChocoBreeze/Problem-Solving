#include<iostream>
#include<sstream>
#include<string>

using namespace std;
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    string str;
    for (int i = 0; i < T; ++i) {
        cin >> str;
        stringstream s(str);
        string buffer;
        int A = 0, B = 0;
        while (getline(s, buffer, ',')) {
            if (A == 0) A = stoi(buffer);
            else B = stoi(buffer);
        }
        cout << A + B << "\n";
    }
    return 0;
}