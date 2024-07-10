#include <iostream>
#include <vector>

using namespace std;

int n, m, target;
int up{ 1 }, down{ 1 };
int upused[100001]{}, downused[100001]{};

vector<int> upv[100001];
vector<int> downv[100001];

void updfs(int now) { // 자기보다 앞에 개수 세기
	for(int& next : upv[now]) {
		if (upused[next] == 1) // 이미 개수 셈
			continue;
		++up;
		upused[next] = 1;
		updfs(next);
	}
}

void downdfs(int now) { // 자기보다 뒤에 개수 세기
	for(int& next : downv[now]) {
		if (downused[next] == 1) // 이미 개수 셈
			continue;
		++down;
		downused[next] = 1;
		downdfs(next);
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> n >> m >> target;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		upv[b].push_back(a);
		downv[a].push_back(b);
	}

	updfs(target);
	downdfs(target);
	cout << up << '\n' << n - down + 1 << '\n';
	return 0;
}