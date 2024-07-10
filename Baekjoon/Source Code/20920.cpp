// 13732kb, 256ms
#include <iostream>
#include <unordered_map> // string - count
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int N{}, M{};
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> N >> M;
    unordered_map<string, int> um;
    vector<string> vec;
    for (int n{}; n < N; ++n)
    {
        string str;
        cin >> str;
        if (str.length() < M)
            continue;
        if (um.find(str) != um.end())
            um[str]++;
        else
        {
            um[str] = 1; // insert
            vec.push_back(str);
        }
    }

    sort(begin(vec), end(vec), [&um](const string &s1, const string &s2)
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
         });

    for (string &s : vec)
        cout << s << '\n';

    return 0;
}