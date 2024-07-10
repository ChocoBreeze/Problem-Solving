// 좀 틀림.
#include<iostream>
#include<vector>
#include<utility> // pair
#include<climits>

// 0~9까지 숫자와
// + : +1 / - : -1 / 0에서 -누르면 0임. 채널 수 = 무한대
// 채널 N으로 이동하기 위한 버튼을 눌러야 하는 최소 횟수

using namespace std;
pair<int, bool> possible(vector<bool>& work, int c) { // 숫자로 이동 가능한지
	bool chk = true;
	int count = 0;
	if (c == 0) {
		++count; // 자리수 확인
		if(!work[c]) chk = false; // 버튼 확인
	}
	while (c != 0) {
		if (!work[c % 10]) {
			chk = false;
			break;
		}
		c /= 10;
		++count;
	}
	return make_pair(count, chk); // 자리수, 
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, temp;
	cin >> N >> M;
	vector<bool> work(10, true); // 0 ~ 9
	for (int i = 0; i < M; ++i) {
		cin >> temp;
		work[temp] = false;
	}
	int min;
	if (N >= 100) min = N - 100;
	else if (N < 100) min = 100 - N;
	if (min != 0) {
		for (int i = 0; i<=1000000; ++i) {
			auto a = possible(work, N + i);
			if (a.second) {
				if (min > a.first + i) min = a.first + i;
			}
			if (N - i >= 0) {
				auto b = possible(work, N - i);
				if (b.second) {
					if (min > b.first + i) min = b.first + i;
				}
			}
		}
	}
	cout << min;
	return 0;
}