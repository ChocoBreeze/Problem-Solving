#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int a, b, c; // c가 빗변
    cout << fixed;
    cout.precision(3);

    for (int t{ 1 };;++t) {
        cin >> a >> b >> c;
        if (a == 0 && b == 0 && c == 0) break;

        cout << "Triangle #" << t << '\n';
        if (a == -1) {
            if (c * c - b * b > 0) cout << "a = " << sqrt(c * c - b * b);
            else cout << "Impossible.";
        }
        else if (b == -1) {
            if (c * c - a * a > 0) cout << "b = " << sqrt(c * c - a * a);
            else cout << "Impossible.";
        }
        else if (c == -1) {
            // c가 a+b보다 클 일은 없다
            cout << "c = " << sqrt(a * a + b * b);
        }
        cout << "\n\n";
    }

    
    return 0;
}