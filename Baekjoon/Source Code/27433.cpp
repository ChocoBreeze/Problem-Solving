#include <iostream>

using namespace std;
using ll = long long;

ll recursiveFact(ll n)
{
    if (n == 0)
        return 1;
    return n * recursiveFact(n - 1);
}

int main()
{
    ll N{};
    cin >> N;
    cout << recursiveFact(N) << '\n';

    return 0;
}