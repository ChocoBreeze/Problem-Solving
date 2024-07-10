// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N{}; cin >> N;
    vector<int> nums(N, 0);
    for(int& n : nums) cin >> n;
    int answer{};
    for(auto it = rbegin(nums)+1;it!= rend(nums); ++it) {
        answer += max(0, *it - *(it - 1) + 1);
        *it = min(*it, *(it - 1) - 1);
    }
    cout << answer << '\n';
    return 0;
}

        

        