#include <iostream>
#include <queue>

using namespace std;

int main() {
    cin.tie(NULL)->sync_with_stdio(false);

    int N, temp;
    cin >> N;
    priority_queue<int> maxH; // 작은 값들
    priority_queue<int, vector<int>, greater<int>> minH; // 큰 값들

    for(int n=0;n<N;++n) {
        cin >> temp;
        if (maxH.size() == minH.size()) maxH.push(temp);
        else minH.push(temp);
        if (!maxH.empty() && !minH.empty() && maxH.top() > minH.top()) {
            // 두 heap의 top swap
            int a = maxH.top(), b = minH.top();
            maxH.pop(); minH.pop();
            maxH.push(b); minH.push(a);
        }
        cout << maxH.top() << '\n';
    }
    return 0;
}