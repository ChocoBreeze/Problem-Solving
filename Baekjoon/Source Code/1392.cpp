#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    vector<int> table(10010, 0);

    int t{};
    for(int n{};n<N;++n) {
        int in; cin >> in;
        for(int j{};j<in;++j) {
            table[t] = n + 1;
            ++t;
        }
    }

    for(int q{};q<Q;++q) {
        int in; cin >> in;
        cout << table[in] << '\n';
    }
    return 0;
}