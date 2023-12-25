// 좋은 친구는 등수의 차이가 K보다 작거나 같으면서 이름의 길이가 같은 친구이다.
// 이름은 알파벳 대문자로 이루어져 있고, 2글자 ~ 20글자
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;
	vector<string> names(N);
	for (auto& name : names) cin >> name;

	long long answer{};
	vector<int> DAT(21, 0); // MAX : 20글자

	for (int k{}; k < K; ++k) {
		DAT[names[k].length()]++;
	}

	for (int k{}; k < N; ++k) {
		if(k + K < N) DAT[names[k + K].length()]++; // K번째 친구 추가
		DAT[names[k].length()]--; // 자기 자신 제외
		answer += static_cast<long long>(DAT[names[k].length()]);
	}
	cout << answer << '\n';
	return 0;
}