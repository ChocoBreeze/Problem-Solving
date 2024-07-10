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
                return s1.first < s2.first; // ���������� ��������
            }
            return s1.first.length() > s2.first.length(); // ���̰� �����
        }
        return s1.second > s2.second; // ���� ���ü���
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
    sort(begin(vec), end(vec), compare); // �̷��Ե� �Ǵ±���

    for (auto &v : vec)
        cout << v.first << '\n';

    return 0;
}