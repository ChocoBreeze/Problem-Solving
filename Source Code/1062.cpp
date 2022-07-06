//vector<bool> chk -> vector<bool>& chk
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
int N, K, answer = 0;

void backtracking(vector<int>& bit_masks, vector<bool>& chk, int bitmask, int count, int start_index) {
	if (count == K) { // answer 갱신
		int answer_temp = 0;
		for (int i = 0; i < N; ++i) {
			if ((bit_masks[i] & bitmask) == bit_masks[i]) ++answer_temp;
		}
		answer = max(answer, answer_temp);
		return;
	}
	if (start_index == 26) return;
	int new_bitmask = bitmask | (1 << start_index);
	backtracking(bit_masks, chk, new_bitmask, count + 1, start_index + 1);
	backtracking(bit_masks, chk, bitmask, count, start_index + 1);
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> K; // N : 1 ~ 50 | K : 0 ~ 26
	// start = antic -< anta + tica
	// 2^26 = 67,108,864
	vector<bool> chk(26, false);
	vector<int> bit_masks(N);
	for (int i = 0; i < N; ++i) {
		string str;
		cin >> str;
		for (auto& j : str) {
			bit_masks[i] = (bit_masks[i] | (1 << (j - 'a')));
		}
	}
	if (K >= 5) {
		int bitmask = 0;
		backtracking(bit_masks, chk, bitmask, 0, 0);
	}
	cout << answer;
	return 0;
}