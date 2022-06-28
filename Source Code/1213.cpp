// palindrome
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::distance;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string A;
	cin >> A;
	vector<int> eng(26, 0);
	for (int i = 0; i < A.length(); ++i) {
		eng[A[i] - 'A']++;
	}
	int chk = 0, center_alphabet = -1;
	for (int k = 0; k < size(eng);++k) {
		if (A.length() % 2 == 0 && eng[k] % 2 == 1) chk += 2;
		if (A.length() % 2 == 1 && eng[k] % 2 == 1) {
			chk++;
			center_alphabet = k;
		}
	}
	string answer;
	if(chk<2) { // palindrome 구성 가능
		answer.assign(A);
		int index = 0;
		if (A.length() % 2 == 1) {
			answer[A.length() / 2] = 'A' + center_alphabet;
			eng[center_alphabet]--;
		}
		for (int i = 0; i < size(eng); ++i) {
			while (eng[i] > 0) {
				answer[index] = 'A' + i;
				answer[A.length() - 1 - index] = 'A' + i;
				++index;
				eng[i]-=2;
			}
		}
	}
	else {
		answer = "I'm Sorry Hansoo";
	}
	cout << answer;
	return 0;
}