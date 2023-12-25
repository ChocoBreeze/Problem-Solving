#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int L{}; cin >> L; // 광고판 크기
	string str; cin >> str; // 현재 광고판에 보이는 문자열

	// 불일치가 발생했을 때 어디로 이동해야 하는지 나타내는 값
	// fail(x) = W의 처음 (x+1)글자 중, 일치하는 접두사/접미사 중 최대 길이
	vector<int> fail(L + 1, 0); 
	for (int i{ 1 }, j{}; i < L; ++i) {
		while (j > 0 && str[i] != str[j]) j = fail[j - 1];
		if (str[i] == str[j]) fail[i] = ++j;
	}

	cout << L - fail[L - 1] << '\n';
	return 0;
}