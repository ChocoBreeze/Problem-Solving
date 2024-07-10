#include <string>
#include <iostream>

using namespace std;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    string str;
    int B;
    cin >> str >> B;

    int ans{};

    for (auto it = begin(str); it != end(str); ++it)
    {
        int num{};
        if ('A' <= *it && *it <= 'Z')
            num = (*it) - 'A' + 10;
        else
            num = (*it) - '0';
        ans *= B;
        ans += num;
    }

    cout << ans << '\n';

    return 0;
}