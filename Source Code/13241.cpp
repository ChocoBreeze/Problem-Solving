#include <concepts>
#include <iostream>
#include <type_traits>

using ll = long long;

template<typename T>
T Gcd(T a, T b) requires std::integral<T> {
    if (b == 0) return a;
    else return Gcd(b, a % b);
}

int main() {
    std::cin.tie(NULL)->sync_with_stdio(false);
    ll a, b;
    std::cin >> a >> b;
    ll gcdAB = Gcd(a, b);
    std::cout << a * b / gcdAB << '\n';
    return 0;
}