// ���� ģ���� ����� ���̰� K���� �۰ų� �����鼭 �̸��� ���̰� ���� ģ���̴�.
// �̸��� ���ĺ� �빮�ڷ� �̷���� �ְ�, 2���� ~ 20����
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
	vector<int> DAT(21, 0); // MAX : 20����

	for (int k{}; k < K; ++k) {
		DAT[names[k].length()]++;
	}

	for (int k{}; k < N; ++k) {
		if(k + K < N) DAT[names[k + K].length()]++; // K��° ģ�� �߰�
		DAT[names[k].length()]--; // �ڱ� �ڽ� ����
		answer += static_cast<long long>(DAT[names[k].length()]);
	}
	cout << answer << '\n';
	return 0;
}