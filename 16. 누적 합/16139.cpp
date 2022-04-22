// 시간 단축
#include<string>
#include<iostream>
#include<vector>
const int alphabet_NUM = 26;
int main() {
	std::string str;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> str;
	int length = str.length(), q, l, r;
	char a;
	std::vector<std::vector<int>> accum(length, std::vector<int>(alphabet_NUM, 0));
	// [알파벳][길이] 아닌 [길이][알파벳]로.. 2번 째 for 시간 단축
	accum[0][str[0] - 'a']++;
	for (int i = 1; i < length; ++i) {
		int index = str[i] - 'a';
		accum[i][index]++;
		for (int j = 0; j < alphabet_NUM; ++j) {
			accum[i][j] += accum[i - 1][j];
		}
	}
	std::cin >> q;
	for (int i = 0; i < q; ++i) {
		std::cin >> a >> l >> r;
		int index = a - 'a';
		if (l > 0) std::cout << accum[r][index] - accum[l - 1][index] << "\n";
		else std::cout << accum[r][index] << "\n";
	}
	return 0;
}