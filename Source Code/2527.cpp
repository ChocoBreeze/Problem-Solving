#include <iostream>

using namespace std;
struct Square {
    int x, y, p, q; // 왼, 밑, 오, 위
    Square(int x, int y, int p, int q) : x(x), y(y), p(p), q(q) {}
    Square() = default;
};

int main() {
    // 입력받기
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    while (1) {
        Square s1{}, s2{};
        cin >> s1.x >> s1.y >> s1.p >> s1.q >> s2.x >> s2.y >> s2.p >> s2.q;
        if (cin.eof()) break;

        if ((s1.p < s2.x) || (s2.p < s1.x) || (s1.q < s2.y) || (s2.q < s1.y)) cout << "d\n"; // 아무것도 안 겹침
        else if ((s1.p == s2.x && (s1.q == s2.y || s1.y == s2.q)) ||
            (s1.x == s2.p && (s1.q == s2.y || s1.y == s2.q))) cout << "c\n"; // 점
        else if (((s2.y < s1.q || s2.q > s1.y) && (s1.p == s2.x || s1.x == s2.p)) ||
            ((s2.x < s1.p || s1.x < s2.p) && (s1.q == s2.y || s1.y == s2.q))) cout << "b\n"; // 선분
        else cout << "a\n"; // 직사각형
    }
    return 0;
}