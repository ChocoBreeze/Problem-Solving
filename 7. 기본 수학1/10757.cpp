#include<string>
#include<iostream>
#include<algorithm>
#include<vector>

int main() {
	std::string str1, str2;
	std::cin >> str1 >> str2;
	std::vector<int> result;
	if (str1.length() < str2.length()) { // str1이 더 길게
		std::swap(str1, str2);
	}
	int num1, num2, carry = 0, sum;
	for (int i = 0; i < str2.length(); ++i) {
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
	for (int i = 0; i < str1.length() - str2.length(); ++i) {
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
	for (auto i = result.rbegin(); i != result.rend(); ++i) {
		std::cout << *i;
	}
	return 0;
}