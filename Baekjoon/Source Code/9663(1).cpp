// 다 확인하지말고 가지 치기쓰
// 1차원으로도 충분하다..
// 더 나은 풀이

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int answer, N;

bool chk_possible(vector<int>& Qs, int Q_cnt, int Q_row) {
	bool chk = true;
	for (int i = 0; i < Q_cnt; ++i) {
		if (Qs[i] == -1) continue; // 아직 안 놓음
		if (Qs[i] == Q_row || abs(i - Q_cnt) == abs(Qs[i] - Q_row)) { // 같은 행에 놓았는지 + 같은 대각선 위인지!
			chk = false;
			break;
		}
	}
	return chk;
}

void N_queens(vector<int>& Qs, int Q_cnt) { 
	if (Q_cnt == N) {
		++answer;
		return;
	}
	for (int i = 0; i < N; ++i) { // 놓을 row
		if (chk_possible(Qs, Q_cnt, i)) { // Q_Cnt = column
			Qs[Q_cnt] = i;
			N_queens(Qs, Q_cnt + 1);
			Qs[Q_cnt] = -1;
		}
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N;
	vector<int> Qs(N, -1); // column별로 들어가는 queens의 row 위치 저장
	N_queens(Qs, 0);
	cout << answer;
	return 0;
}