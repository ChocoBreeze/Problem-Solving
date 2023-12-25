#include <iostream>
#include <vector>

using namespace std;

vector<int> isTeam, students, visited;
bool isReach;
int backPoint{ -1 }, answer{};

void DFS(int curr) {
	if (isTeam[curr]) return; // 이미 팀이 구성된 친구
	if (visited[curr] == 1) { // 사이클 형성
		backPoint = curr; // 거꾸로 돌아갈 최종 도착
		isReach = true;
		return;
	}
	else if (visited[curr] == 2) {
		// 전에 방문했는데 사이클이 형성 안 되는 친구
		return;
	}
	visited[curr] = 1;
	DFS(students[curr]);
	if (isReach) {
		isTeam[curr] = 1;
		++answer;
		if (curr == backPoint) isReach = false;
	}
	else visited[curr] = 2;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int N{}; cin >> N; // 학생 수

		students = vector<int>(N, 0);
		isTeam = vector<int>(N, 0);
		visited = vector<int>(N, 0);
		answer = 0;

		for (int& s : students) {
			cin >> s; --s;
		}

		for (int n{}; n < N; ++n) {
			isReach = false;
			if (isTeam[n] == 0) {
				visited[n] = 1;
				DFS(students[n]);
				if (isReach) {
					isTeam[n] = 1;
					++answer;
				}
				else visited[n] = 2;
			}
		}

		cout << N - answer << '\n';
	}

	return 0;
}