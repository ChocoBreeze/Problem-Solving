#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main()
{
    int N{};
    cin >> N;
    unordered_set<string> us;
    us.insert("ChongChong"s);
    for (int n{}; n < N; ++n)
    {
        string str1, str2;
        cin >> str1 >> str2;
        if (us.find(str1) != us.end() || us.find(str2) != us.end())
        {
            us.insert(str1);
            us.insert(str2);
        }
    }
    cout << us.size() << '\n';
    return 0;
}