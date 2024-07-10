#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int n;
	const long long M = 1234567891;	
	const long long r = 31;
	long long answer = 0, r_s = 1;
	string str;
	cin >> n >> str;
	for (auto& s : str) {
		long long a = s - 'a' + 1;
		answer += (a * r_s) % M;
		r_s *= r;
		r_s %= M;
	}
	cout << answer%M;
	return 0;
}