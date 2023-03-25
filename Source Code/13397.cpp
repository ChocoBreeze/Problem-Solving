#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vec;
int N, T; // 사람 수, 팀의 수

bool makeTeam(int score) {
	// score의 값을 최대값으로 구할 수 있는가?
	bool ret{};
	int nowMax{ vec[0] }; // 한 그룹의 최대값
	int nowMin{ vec[0] }; // 한 그룹의 최소값
	int nowTeamCnt{ 1 }; // 만들어지는 team 개수
	for (int s = 1; s < N; ++s) { // start = s
		// 다음 원소에 대해 미리 고려
		int tmpnowMax = max(nowMax, vec[s]);
		int tmpnowMin = min(nowMin, vec[s]);
		if (tmpnowMax - tmpnowMin > score) {
			nowMax = vec[s];
			nowMin = vec[s];
			nowTeamCnt++; // 다음 팀~
		}
		nowMax = max(nowMax, vec[s]);
		nowMin = min(nowMin, vec[s]);
	}
	if (nowTeamCnt <= T) { // 기준보다 팀 수가 작거나 같은 경우
		ret = true;
	}
	return ret;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> T;
	vec = vector<int>(N); // 오..
	for (int& v : vec) cin >> v;

	int left = 0, right = 5000 * 10000;
	while (left < right) {
		int mid = left + (right - left) / 2; // overflow
		auto res = makeTeam(mid);
		if (res == true) { // 팀수 T보다 작거나 같은 경우에는 점수 기준을 낮추기
			right = mid;
		}
		else { // 팀수가 T보다 큰 경우 점수 기준을 올려야 함.
			left = mid + 1;
		}
	}
	cout << right << endl;
	return 0;
}