#include<iostream>
#include<string>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int answer{};
    for(int i{}; i<8;++i) {
        string row;
        cin >> row;
        for(int j{}; j<8;++j) {
            if((i+j)%2==0 && row[j] == 'F') ++answer;
        }
    }
    cout << answer << '\n';
    return 0;
}