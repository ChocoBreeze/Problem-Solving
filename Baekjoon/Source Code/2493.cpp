/*
��� ž�� ������ �۽ű�� ������ ��ȣ�� ��ǥ��� �����ϰ� ���� ������ ���� �������� �߻��ϰ�, 
ž�� ��� ��ο��� ������ ��ȣ�� �����ϴ� ��ġ�� ��ġ�Ǿ� �ִ�. 
�ϳ��� ž���� �߻�� ������ ��ȣ�� ���� ���� ������ �� �ϳ��� ž������ ������ �����ϴ�.

������ ž���� �߻��� ������ ��ȣ�� ��� ž���� �����ϴ����� �˾Ƴ��� ���α׷��� �ۼ�
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
using pii = pair<int, int>; // index, height
constinit const int INF = 1 << 30;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;
	stack<pii> S;
	S.emplace(0, INF);
	for (int n{1}; n <= N; ++n) {
		int h; cin >> h;
		while (!S.empty()) {
			if (S.top().second > h) break;
			S.pop();
		}
		cout << S.top().first << ' ';
		S.emplace(n, h);
	}

	return 0;
}