#include <iostream>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;

int main()
{
    int N{};
    cin >> N;
    set<string> s;
    s.insert("ChongChong"s);
    for (int n{}; n < N; ++n)
    {
        string str1, str2;
        cin >> str1 >> str2;
        if (s.find(str1) != s.end() || s.find(str2) != s.end())
        {
            s.insert(str1);
            s.insert(str2);
        }
    }
    cout << s.size() << '\n';
    return 0;
}