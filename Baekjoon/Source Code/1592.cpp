// floyd-warshall
// 2020KB, 0ms
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}, L{}; cin >> N >> M >> L; // 사람 수, 게임 종료 횟수, 어디로 던질지
	// L은 N-1보다 작거나 같은 자연수이다
	vector<int> cnt(N, 0); // 공 받은 횟수

	int start{};
	for (int s{};; ++s) { // 던지는 횟수 -> 처음 1번이 받는 것은 던지기 이전
		if ((++cnt[start]) == M) {
			cout << s << '\n';
			break;
		}
		if (cnt[start] & 1) { // 홀
			start = (start + L) % N;
		}
		else {
			if (start - L < 0) start = (start - L + N) % N;
			else start = (start - L) % N;
		}
	}

	return 0;
}