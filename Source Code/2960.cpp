// K번째 지워지는 수 구하기
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, K;
	cin >> N >> K;
	vector<bool> chk(N + 1, true);

	int count = 0;
	for (int i = 2; i <= N; ++i) {
		if (!chk[i]) continue; // 중복 지우기
		++count; // 자기 자신도 지운다
		if (count == K) {
			cout << i;
			break;
		}
		for (int j = i * i; j <= N; j += i) {
			if (!chk[j]) continue;
			chk[j] = false;
			++count;
			if (count == K) {
				cout << j;
				break;
			}
		}
		if (count == K) break;
	}
	return 0;
}