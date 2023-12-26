#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Coord {
    int x, y;
    Coord(int x, int y) : x(x), y(y) {}
    Coord operator+(const Coord& other);
    Coord() = default;
    void Print() {
        cout << x << ' ' << y << '\n';
    }
};
using Vector = Coord;

Coord Coord::operator+(const Coord& other) { // 앞에 Coord:: 안 붙여서.. ㅋㅋ
    return Coord(x + other.x, y + other.y);
}

Coord Diff(const Coord& c1, const Coord& c2) {
    return Coord(c1.x - c2.x, c1.y - c2.y);
}

double Distance(const Coord& c1, const Coord& c2) {
    Vector d = Diff(c1, c2);
    return sqrt(d.x * d.x + d.y * d.y);
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    Coord A{}, B{}, C{};
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

    cout << fixed;
    cout.precision(15);

    Vector d1 = Diff(A, B), d2 = Diff(A, C);
    // d1.x/d2.x == d1.y/d2.y => 한 직선 위
    if (d1.x * d2.y == d1.y * d2.x) { // 평행사변형 구성 불가능
        cout << "-1\n";
        return 0;
    }

    // B 맞은편에 D => D = B + (A - B) + (C - B)
    Coord D0 = B + Diff(A, B) + Diff(C, B);
    // D0.Print();
    double circumference1 = 2 * (Distance(A, D0) + Distance(C, D0)); // 둘레가 영어로 circumference

    // A 맞은편에 D => D = A + (B - A) + (C - A)
    Coord D1 = A + Diff(B, A) + Diff(C, A);
    // D1.Print();
    double circumference2 = 2 * (Distance(B, D1) + Distance(C, D1));

    // C 맞은편에 D => D = C + (B - C) + (A - C)
    Coord D2 = C + Diff(B, C) + Diff(A, C);
    // D2.Print();
    double circumference3 = 2 * (Distance(A, D2) + Distance(B, D2));

    cout << max({ circumference1, circumference2, circumference3 }) - min({ circumference1, circumference2, circumference3 }) << '\n';
    return 0;
}