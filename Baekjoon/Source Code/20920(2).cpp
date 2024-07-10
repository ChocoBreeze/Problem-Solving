// set - 새로운 정렬 기준 사용
// 17544kb, 300ms

#include <iostream>
#include <string>
#include <unordered_map> // string - count
#include <set>

using namespace std;

int main()
{
    int N{}, M{};
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> N >> M;
    unordered_map<string, int> um;
    auto compare = [&um](const string &s1, const string &s2)
    {
        if (um[s1] == um[s2])
        {
            if (s1.length() == s2.length())
            {
                return s1 < s2; // 사전순으로 빠를수록
            }
            return s1.length() > s2.length(); // 길이가 길수록
        }
        return um[s1] > um[s2]; // 자주 나올수록
    };
    set<string, decltype(compare)> s(compare);
    for (int n{}; n < N; ++n)
    {
        string str;
        cin >> str;
        if (str.length() < M)
            continue;
        if (um.find(str) != um.end())
        {
            s.erase(str); // um을 먼저 갱신하면 못 찾음.
            um[str]++;
            s.insert(str);
        }
        else
        {
            um[str] = 1; // insert먼저 해줘야 값 넣을 수 있음.
            s.insert(str);
        }
    }

    for (const string &str : s)
        cout << str << '\n'; // cost 필요

    return 0;
}