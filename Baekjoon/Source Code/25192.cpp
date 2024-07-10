// unordered_map�� clear�ϴ� ��� �ð� �ʰ���!!
// https://www.acmicpc.net/board/view/90885
/*
std::unordered_set �� std::unordered_map �� clear() �Լ��� ���װ� �ֽ��ϴ�.
������ N ���� �����͸� �߰��� ���� �ִٸ�, clear ������ ȣ���� ������ O(N) �� �ð��� �Ҹ�˴ϴ�.
*/
// 92ms (map�� ��쿡�� swap�ص� ū ���� �ȳ� 88ms)
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