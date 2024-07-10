#include <iostream>
#include <vector>

using namespace std;

vector<int> isTeam, students, visited;
bool isReach;
int backPoint{ -1 }, answer{};

void DFS(int curr) {
	if (isTeam[curr]) return; // �̹� ���� ������ ģ��
	if (visited[curr] == 1) { // ����Ŭ ����
		backPoint = curr; // �Ųٷ� ���ư� ���� ����
		isReach = true;
		return;
	}
	else if (visited[curr] == 2) {
		// ���� �湮�ߴµ� ����Ŭ�� ���� �� �Ǵ� ģ��
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
		int N{}; cin >> N; // �л� ��

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