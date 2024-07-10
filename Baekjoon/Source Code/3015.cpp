#include <iostream>
#include <stack>

using namespace std;

struct Data
{
    int value;
    int cnt;
    Data(int value, int cnt) : value(value), cnt(cnt) {}
};

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N{};
    cin >> N;
    stack<Data> S;
    long long sum{};
    for (int n{}; n < N; ++n)
    {
        int in;
        cin >> in;

        // �ڽź��� ũ�ų� ���� �ְ� ���� ������ pop
        if (S.empty())
        {
            S.push(Data(in, 1));
        }
        else
        {
            if (S.top().value > in)
            {
                ++sum;
                S.push(Data(in, 1));
            }
            else
            {
                int cnt{}, lastCnt{-1};
                while (!S.empty() && S.top().value <= in)
                {
                    cnt += S.top().cnt;
                    if (S.top().value == in)
                        lastCnt = S.top().cnt;
                    S.pop();
                }
                if (S.empty())
                {
                    sum += cnt;
                    if (lastCnt == -1)
                        S.push(Data(in, 1));
                    else
                        S.push(Data(in, lastCnt + 1));
                }
                else
                {
                    sum += cnt; // �������� ���� ģ���� ���δ�.
                    sum += 1;
                    if (lastCnt == -1)
                        S.push(Data(in, 1));
                    else
                        S.push(Data(in, lastCnt + 1));
                }
            }
        }
    }
    cout << sum << '\n';

    return 0;
}