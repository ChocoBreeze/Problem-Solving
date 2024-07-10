#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;
using ll = long long;
bool chk = true;

struct Data
{
    int i; // 2^i
    int cnt;
    Data(int i, int cnt) : i(i), cnt(cnt) {}
};
vector<Data> cnts;
int N;

ll DivideAndConquer(int l, int w, int h)
{
    if (l == 0 || w == 0 || h == 0)
    {
        return 0;
    }

    ll ret{};
    int idx{N - 1}, side{};

    for (; idx >= 0; --idx)
    {
        if (cnts[idx].cnt > 0)
        {
            side = 1 << cnts[idx].i; // 한 변의 길이
            if (l >= side && w >= side && h >= side)
            {
                // possibleMaxBlocks = (l / side) * (w / side) * (h / side);
                break;
            }
        }
    }

    if (idx < 0)
    {
        chk = false;
        return 0;
    }

    // int blocks = min(possibleMaxBlocks, cnts[idx].cnt); // block 개수
    // cnts[idx].cnt -= blocks;
    cnts[idx].cnt--;

    ret += 1;
    ret += DivideAndConquer(l, w, h - side);       // 위
    ret += DivideAndConquer(l, w - side, side);    // 뒤
    ret += DivideAndConquer(l - side, side, side); // 옆

    return ret;
}

int main()
{
    int length, width, height;
    cin >> length >> width >> height;

    cin >> N;
    cnts = vector<Data>(N, Data(0, 0));
    for (Data &v : cnts)
    {
        cin >> v.i >> v.cnt;
    }

    ll ans = DivideAndConquer(length, width, height);
    if (!chk)
        cout << "-1\n";
    else
        cout << ans << '\n';

    return 0;
}