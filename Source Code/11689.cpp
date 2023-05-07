// 서로소 개수
// https://www.acmicpc.net/board/view/80616
// https://lovelyunsh.tistory.com/103 : 에라토스테네스의 체
// https://m.blog.naver.com/hongjg3229/221795417061 : 오일러 파이 함수와 오일러 정리

// 2020KB, 12ms
// primes 배열을 안 만들고도 구할 수 있음!
#include <iostream>

// 10^12 = 1'000'000'000'000 = 1조
// 10^6 = 1'000'000 = 100만

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