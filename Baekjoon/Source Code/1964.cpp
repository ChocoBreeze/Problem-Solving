#include<iostream>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int answer = 5, start = 3;
    int N; cin >> N;
    for(int n{1}; n<N; ++n) {
        answer += start*3 -2;
        answer %= 45678;
        ++start;
    }
    cout << answer;
    return 0;
}