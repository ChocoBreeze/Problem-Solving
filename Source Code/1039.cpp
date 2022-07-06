// 왜 bfs인거지 - 숫자를 정점으로 생각해서
// 다음 갈 수 있는 정점을 bfs로 탐색
// 다음 정점 만든 후 중복 제거
// 중복 제거 없다면 시간 초과 (15^10)
// 최대한 그리디로 해보려 했으나 최대 31%.. 실패..

#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>

using namespace std;

string bfs(string& N, int K) {
	queue<string> Q;
	set<string> S;
	Q.push(N);
	int L = N.length();
	for (int k = 0; k < K; ++k) {
		S.clear();
		while (!Q.empty()) {
			string now = Q.front();
			Q.pop();
			for (int i = 0; i < L; ++i) {
				for (int j = i + 1; j < L; ++j) {
					string temp = now;
					swap(temp[i], temp[j]);
					// set에 삽입함으로써 중복 제거 N=6인 경우 최대 6!의 case로
					// 매 재귀 횟수 감소 가능
					S.insert(temp);
				}
			}
		}
		for (auto& i : S) {
			Q.push(i);
		}
	}
	string answer = *(S.rbegin());
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string N;
	int K;
	cin >> N >> K;
	if (N.length() == 1 || (N.length() == 2 && N.back() == '0')) cout << -1;
	else cout << bfs(N, K);
	return 0;
}