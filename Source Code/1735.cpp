#include<iostream>

using namespace std;

int gcd(int a, int b) {
	if (!b) return a;
	else return gcd(b, a % b);
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n1, d1, n2, d2;
	cin >> n1 >> d1 >> n2 >> d2;
	int num, denum;
	denum = d1 * d2;
	num = n1 * d2 + n2 * d1;
	int G = gcd(denum, num);
	cout << num / G << " " << denum / G;
	return 0;
}