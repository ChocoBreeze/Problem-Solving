// 2020KB, 0ms
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int people{}, answer{-1};
    for(int i{};i<4;++i) { // 역
        int out{}, in{}; cin >> out >> in;
        people -= out;
        people += in;
        answer = max(answer, people);
    }
    cout << answer << '\n';
}