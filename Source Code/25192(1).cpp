// clear ´ë½Å ºó unordereD_mapÀÌ¶û swap
#include <iostream>
#include <unordered_map>
#include <string>

#define FASTIO cin.tie(NULL)->sync_with_stdio(false)

using namespace std;

int main()
{
    FASTIO;
    int N{};
    cin >> N;
    unordered_map<string, int> um;
    int ans{};
    for (int n{}; n < N; ++n)
    {
        string str;
        cin >> str;
        if (str == "ENTER")
        {
            unordered_map<string, int> emptyUM;
            um.swap(emptyUM);
            continue;
        }
        if (um.find(str) == um.end())
            ++ans;
        um[str] = 1;
    }
    cout << ans << '\n';
    return 0;
}