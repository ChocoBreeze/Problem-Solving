// 숫자 범위
// https://www.acmicpc.net/problem/10757
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string sum(string str1, string str2) {
	vector<int> result;
	if (str1.length() < str2.length()) { // str1이 더 길게
		swap(str1, str2);
	}
	int num1, num2, carry = 0, sum;
	for (int i = 0; i < str2.length(); ++i) { // 둘이 더해지는 부분
		num1 = str1[str1.length() - (i + 1)] - '0';
		num2 = str2[str2.length() - (i + 1)] - '0';
		sum = num1 + num2 + carry;
		if (sum >= 10) {
			carry = 1;
			result.push_back(sum - 10);
		}
		else {
			carry = 0;
			result.push_back(sum);
		}
	}
	for (int i = 0; i < str1.length() - str2.length(); ++i) { // str1만 남는 부분
		num1 = str1[str1.length() - (i + str2.length() + 1)] - '0';
		sum = num1 + carry;
		if (sum >= 10) {
			carry = 1;
			result.push_back(sum - 10);
		}
		else {
			carry = 0;
			result.push_back(sum);
		}
	}
	if (carry == 1) {
		result.push_back(carry);
	}
	//std::reverse(begin(result), end(result));
	string return_result;
	for (auto i = result.rbegin(); i != result.rend(); ++i) {
		return_result += ((*i) + '0');
	}
	return return_result;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	string f0 = "0", f1 = "1";
	for (int i = 1; i < n; ++i) { // O(N)
		string temp = sum(f0, f1);
		f0 = f1;
		f1 = temp;
	}
	if (n == 0) cout << f0;
	else cout << f1;
	return 0;
}