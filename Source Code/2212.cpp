/*
    간격으로 넣을 생각을 어떻게 했을까..
    https://joodaram.tistory.com/63
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<int> vec(N, 0);
    for (auto& v : vec) {
        cin >> v;
    }
    sort(begin(vec), end(vec));
    vector<int> dist(N - 1, 0);
    for (int i = 1; i < N; ++i) {
        dist[i - 1] = vec[i] - vec[i - 1];
    }
    sort(begin(dist), end(dist));
    int sum = 0;
    for (int i = 0; i < N - K; ++i) {
        sum += dist[i];
    }
    cout << sum << '\n';

    return 0;
}