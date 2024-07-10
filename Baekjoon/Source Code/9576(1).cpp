#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SE {
	int s, e;
	SE(int s, int e) : s(s), e(e) {}
};
vector<SE> in;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M; // å�� N��, �кλ��� M��
		in = vector<SE>(M, SE(0,0)); // 0 ~ N - 1

		for (SE& se : in) { // 0 ~ M - 1
			cin >> se.s >> se.e;
			se.s--, se.e--;
		}
		vector<int> bookChk(N, 0);

		sort(begin(in), end(in), [](const SE& se1, const SE& se2) {
			return se1.e < se2.e;
		}); // �ڿ��� ���� ���� (�� �� �ִ� å�� �ִٸ� �տ������� Ȯ�� �� �ֱ�)
		
		int answer{};
		for (SE& se : in) {
			for (int i{ se.s }; i <= se.e; ++i) {
				if (!bookChk[i]) {
					bookChk[i] = 1;
					++answer;
					break;
				}
			}
		}
		cout << answer << '\n';
	}

	return 0;
}