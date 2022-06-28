#include<iostream>
using std::cin;
using std::cout;
int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int sum = 0, a;
    for(int i=0;i<5;++i) {
        cin >> a;
        if(a< 40) sum += 40;
        else sum += a;
    }
    cout << sum/5;
    return 0;
}