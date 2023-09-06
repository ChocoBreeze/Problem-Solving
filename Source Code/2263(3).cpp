// 4788KB, 32ms

#include <iostream>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::move;
using std::stack;
using std::vector;

struct Range
{
    int start, end;
    Range(int start, int end) : start(start), end(end) {}
    Range(Range &r) : start(r.start), end(r.end) {} // Ref만 가능
    Range(Range &&r) : start(move(r.start)), end(move(r.end)) {}
};

struct SS
{
    Range iRange;
    Range pRange;
    SS(Range &r1, Range &r2) : iRange(r1), pRange(r2) {}
    SS(Range &&r1, Range &&r2) : iRange(r1), pRange(r2) {}
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;

    vector<int> inOrder(n, 0), postOrder(n, 0);
    vector<int> inOrderDAT(n + 1, 0); // 1 ~ n
    for (int i{}; i < n; ++i)
    {
        cin >> inOrder[i];
        inOrderDAT[inOrder[i]] = i;
    }
    for (int &v : postOrder)
        cin >> v;

    stack<SS> S;
    Range r1(0, n - 1), r2(0, n - 1);
    S.push(SS(r1, r2));

    vector<int> result;
    while (!S.empty())
    {
        SS nowTop = S.top();
        S.pop();
        if (nowTop.pRange.start > nowTop.pRange.end || nowTop.iRange.start > nowTop.iRange.end)
            continue;
        int rootValue = postOrder[nowTop.pRange.end];
        result.push_back(rootValue);

        if (nowTop.pRange.start == nowTop.pRange.end)
            continue; // or nowTop.iRange.start == nowTop.iRange.end
        int rootIndex{inOrderDAT[rootValue]};

        int leftCnt = rootIndex - nowTop.iRange.start;
        S.push(SS(Range(rootIndex + 1, nowTop.iRange.end), Range(nowTop.pRange.start + leftCnt, nowTop.pRange.end - 1)));     // R
        S.push(SS(Range(nowTop.iRange.start, rootIndex - 1), Range(nowTop.pRange.start, nowTop.pRange.start + leftCnt - 1))); // L
    }

    for (int &v : result)
        cout << v << ' ';
    cout << '\n';

    return 0;
}