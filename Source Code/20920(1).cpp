// 13664kb, 76ms
#include <iostream>
#include <string>
#include <unordered_map> // string - count
#include <vector>
#include <algorithm>

using namespace std;

using psi = pair<string, int>;

int main()
{
    int N{}, M{};
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> N >> M;
    unordered_map<string, int> um;
    auto compare = [&um](const psi &s1, const psi &s2)
    {
        if (s1.second == s2.second)
        {
            if (s1.first.length() == s2.first.length())
            {
                return s1.first < s2.first; // 사전순으로 빠를수록
            }
            return s1.first.length() > s2.first.length(); // 길이가 길수록
        }
        return s1.second > s2.second; // 자주 나올수록
    };

    for (int n{}; n < N; ++n)
    {
        string str;
        cin >> str;
        if (str.length() < M)
            continue;
        if (um.find(str) != um.end())
            um[str]++;
        else
            um[str] = 1;
    }
    vector<psi> vec(begin(um), end(um));
    sort(begin(vec), end(vec), compare); // 이렇게도 되는구나

    for (auto &v : vec)
        cout << v.first << '\n';

    return 0;
}