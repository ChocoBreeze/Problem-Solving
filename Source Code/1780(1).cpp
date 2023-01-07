#include <iostream>
#include <vector>

using namespace std;

int cnt_m_one, cnt_zero, cnt_one;

void paper_count(vector<vector<int>>& paper, int start_x, int start_y, int length) {
	int one = 0, zero = 0, m_one = 0;
	bool is_same = true;
	for(int i=start_x;i<start_x + length;++i) { // 정해진 길이에 대해 다 같은지 확인
		for (int j = start_y; j < start_y + length; ++j) {
			if (paper[i][j] == 1) ++one;
			else if (paper[i][j] == 0) ++zero;
			else if (paper[i][j] == -1) ++m_one;
			if ((m_one > 0 && zero > 0) || (m_one > 0 && one > 0) || (zero > 0 && one > 0)) {
				is_same = false;
				break;
			}
		}
	}
	if (is_same) { // 답 갱신
		if (zero > 0) ++cnt_zero;
		else if (one > 0) ++cnt_one;
		else ++cnt_m_one;
	}
	else { // 분할
		int one_third_l = length / 3;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				paper_count(paper, start_x + one_third_l * i, start_y + one_third_l * j, one_third_l);
			}
		}
	}
}

int main() {
	int N;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N; // N ~ 3^k

	vector<vector<int>> paper(N, vector<int>(N, 0));
	for (auto& i : paper) {
		for (auto& j : i) {
			cin >> j;
		}
	}

	paper_count(paper, 0, 0, N);
	cout << cnt_m_one << "\n" << cnt_zero << "\n" << cnt_one;

	return 0;
}