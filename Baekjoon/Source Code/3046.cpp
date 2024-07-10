#include<iostream>
using std::cin;
using std::cout;
int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int R1, S;
    cin >> R1 >> S;
    cout << S*2-R1;
    return 0;
}