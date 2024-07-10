#include<iostream>
using std::cin;
using std::cout;

int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int N;
    cin >> N;
    for(int i=0;i<N;++i) {
        for(int j=i;j<N;++j) {
            cout << "*";
        }
        cout<<"\n";
    }
    return 0;
}