#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int RevStr(string& str) {
    bool notZero{};
    int ret{};
    for(auto it = rbegin(str);it!=rend(str);++it) {
        if(!notZero && *it == '0') {
            continue;
        }
        else {
            notZero = true;
            ret *= 10;
            ret += *it - '0';
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    string X, Y;
    cin >> X >> Y;
    int xy = RevStr(X) + RevStr(Y);
    string XY = to_string(xy);
    cout << RevStr(XY) << '\n';
    return 0;
}