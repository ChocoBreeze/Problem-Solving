#include <string>
#include <iostream>

using namespace std;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int num;
    int B;
    cin >> num >> B;

    string ans;

    while (num)
    {
        int remain = num % B;
        string remainStr = "";
        if (remain >= 10)
        {
            remainStr = 'A' + remain - 10;
        }
        else
        {
            remainStr = remain + '0';
        }
        ans += remainStr;
        num /= B;
    }
    for (auto it = rbegin(ans); it != rend(ans); ++it)
    {
        cout << *it;
    }
    cout << '\n';

    return 0;
}