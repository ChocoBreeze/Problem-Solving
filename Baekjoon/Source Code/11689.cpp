// ���μ� ����
// https://www.acmicpc.net/board/view/80616
// https://lovelyunsh.tistory.com/103 : �����佺�׳׽��� ü
// https://m.blog.naver.com/hongjg3229/221795417061 : ���Ϸ� ���� �Լ��� ���Ϸ� ����

// 2020KB, 12ms
// primes �迭�� �� ����� ���� �� ����!
#include <iostream>

// 10^12 = 1'000'000'000'000 = 1��
// 10^6 = 1'000'000 = 100��

using namespace std;
using ll = long long;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    ll N{}, ans;
    cin >> N;
    ans = N;

    for (ll i = 2; i * i <= N; ++i)
    {
        if (N % i == 0)
        {
            ans /= i;
            ans *= (i - 1);
            while (N % i == 0)
            {
                N /= i;
            }
        }
    }

    if (N != 1)
    {
        ans /= N;
        ans *= (N - 1);
    }

    cout << ans << '\n';

    return 0;
}