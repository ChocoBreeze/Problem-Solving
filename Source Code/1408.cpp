#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void Print(int t) {
    if(t==0) cout << "00";
    else if(t < 10) cout << '0'<<t;
    else cout << t;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    string now, start, temp;
    cin >> now >> start;
    int nowT{}, startT{};
    nowT += 3600 * stoi(now.substr(0,2));
    nowT += 60 * stoi(now.substr(3,2));
    nowT += stoi(now.substr(6,2));
    
    startT += 3600 * stoi(start.substr(0,2));
    startT += 60 * stoi(start.substr(3,2));
    startT += stoi(start.substr(6,2));

    if(nowT < startT) {
        int h,m,s;
        h = (startT - nowT) / 3600;
        m = (startT - nowT) % 3600 / 60;
        s = (startT - nowT) % 60;
        Print(h);
        cout << ":";
        Print(m);
        cout << ":";
        Print(s);
    }
    else {
        int h,m,s;
        h = (startT + 86400 - nowT) / 3600;
        m = (startT + 86400 - nowT) % 3600 / 60;
        s = (startT + 86400 - nowT) % 60;
        Print(h);
        cout << ":";
        Print(m);
        cout << ":";
        Print(s);
    }
    return 0;
}