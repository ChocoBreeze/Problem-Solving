// set - ���ο� ���� ���� ���
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
                return s1 < s2; // ���������� ��������
            }
            return s1.length() > s2.length(); // ���̰� �����
        }
        return um[s1] > um[s2]; // ���� ���ü���
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
            s.erase(str); // um�� ���� �����ϸ� �� ã��.
            um[str]++;
            s.insert(str);
        }
        else
        {
            um[str] = 1; // insert���� ����� �� ���� �� ����.
            s.insert(str);
        }
    }

    for (const string &str : s)
        cout << str << '\n'; // cost �ʿ�

    return 0;
}