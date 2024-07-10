#include <iostream>
#include <vector>
#include <concepts>
#include <type_traits>

// 간격 간의 최대 공약수
// 첫 제출

using namespace std;

template<typename T>
T Gcd(T a, T b) requires integral<T> {
    if (b == 0) return a;
    else return Gcd(b, a % b);
}

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int N, diff{};
    cin >> N;
    vector<int> trees(N, 0);
    cin >> trees[0];
    for (int n = 1; n < N; ++n) {
        cin >> trees[n];
        diff = Gcd(diff, trees[n] - trees[n-1]);
    }
    int answer{}, index{ 1 };
    int start = trees[0];
    while (start != trees.back()) {
        start += diff;
        if (start != trees[index]) ++answer;
        else ++index;
    }

    cout << answer << '\n';

    return 0;
}