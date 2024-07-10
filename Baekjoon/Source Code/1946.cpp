#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
using pii = pair<int, int>;
constinit const int INF = 1 << 30;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T; // ~ 20
	while (T--) {
		int N{}; cin >> N; // ~ 100'000
		// (index, ���)
		vector<pii> score(N, make_pair(0, 0));
		for (auto& s : score) {
			cin >> s.first >> s.second; // ����, ����
		}
		// ���� ������ �켱���ؼ� �������� ����
		sort(begin(score), end(score));

		int lastMeet{ INF }, answer{};
		for (auto& s: score) {
			if (lastMeet > s.second) { // �� ������ ���� ������� ���� ������� �� ���� ��쿡�� ���� ������!
				++answer;
				lastMeet = s.second; // ���� ������ ���� ����� ���� ��� �ݿ�
			}
		}
		
		cout << answer << '\n';
	}

	return 0;
}