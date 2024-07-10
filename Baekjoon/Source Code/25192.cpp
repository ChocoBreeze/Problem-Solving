// unordered_map을 clear하는 경우 시간 초과남!!
// https://www.acmicpc.net/board/view/90885
/*
std::unordered_set 와 std::unordered_map 의 clear() 함수에 버그가 있습니다.
이전에 N 개의 데이터를 추가한 적이 있다면, clear 연산을 호출할 때마다 O(N) 의 시간이 소모됩니다.
*/
// 92ms (map의 경우에는 swap해도 큰 차이 안남 88ms)
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N{};
    cin >> N;
    map<string, int> m;
    int ans{};
    for (int n{}; n < N; ++n)
    {
        string str;
        cin >> str;
        if (str == "ENTER")
        {
            m.clear();
            continue;
        }
        if (m.find(str) == m.end())
            ++ans;
        m[str] = 1;
    }
    cout << ans << '\n';
    return 0;
}