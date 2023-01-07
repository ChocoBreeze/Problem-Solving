// Stack을 쓴다는 접근이 힘들다.
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, max = -1;
	cin >> N;
	vector<int> vec(N, 0);
	for (auto& v : vec) {
		cin >> v;
	}
	stack<int> S;
	vector<int> answer(N, -1);
	max = vec[N - 1];
	for (int i = N - 2; i >= 0; --i) {
		if (vec[i] < vec[i + 1]) {
			answer[i] = vec[i + 1];
			S.push(vec[i + 1]);
		}
		else {
			if (max < vec[i]) { // 처음 초기화를 -1로 설정했기 때문에 -1로 설정할 필요 없음
				max = vec[i];
				S.push(vec[i]);
			}
			else {
				while (!S.empty()) {
					if (vec[i] < S.top()) {
						answer[i] = S.top();
						break;
					}
					S.pop();
				}
			}
		}
	}

	for (auto& ans : answer) {
		cout << ans << " ";
	}

	return 0;
}