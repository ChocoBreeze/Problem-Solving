#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    cin >> str;
    for (auto it = begin(str); it != end(str); ++it)
    {
        if ('a' <= (*it | 0x20) && (*it | 0x20) <= 'z')
        {
            *it ^= 0x20;
        }
    }
    cout << str << '\n';
    return 0;
}