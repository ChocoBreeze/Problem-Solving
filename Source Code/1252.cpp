#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string A, B;
	cin >> A >> B;
	reverse(begin(A), end(A));
	reverse(begin(B), end(B));
	string answer;
	int aLen = static_cast<int>(A.length()), bLen = static_cast<int>(B.length());
	int carry{};
	for (int i{}; i < max(aLen, bLen); ++i) {
		int a{}, b{};
		if (i < aLen) {
			if (A[i] == '1') a = 1;
		}
		if (i < bLen) {
			if (B[i] == '1') b = 1;
		}
		int sum = a + b + carry;
		if (sum & 1) answer.push_back('1');
		else answer.push_back('0');
		
		if (sum & 2) carry = 1;
		else carry = 0;
	}

	if (carry) answer.push_back('1');
	while (!answer.empty() && answer.back() == '0') answer.pop_back();

	reverse(begin(answer), end(answer));
	if (answer.empty()) cout << "0\n";
	else cout << answer << '\n';

	return 0;
}