// 2020KB, 0ms
#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int a{}, b{}; cin >> a >> b;
    --a, --b;
    int xA{a/4}, yA{a%4}, xB{b/4}, yB{b%4};
    int xDiff{xA - xB<0?xB-xA : xA-xB}, yDiff{yA - yB<0?yB-yA : yA-yB};
    cout << xDiff + yDiff << '\n';
    return 0;
}