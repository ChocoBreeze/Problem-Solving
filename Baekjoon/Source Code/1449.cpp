/*
길이 L인 테이프를 무한 개 가지고 있음.
좌우 0.5만큼의 간격을 줘야 함. 구간 하나 덮는데 적어도 길이 1
필요한 테이프의 개수
개수 N 테이프 L
*/
#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, L;
	cin >> N >> L;
	vector<int> a(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> a[i];
	}
	sort(begin(a), end(a));
	vector<bool> chk(N, false);
	int tape_cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (chk[i]) continue;
		chk[i] = true;
		++tape_cnt;
		int j = i + 1;
		while (j < N && a[j] < a[i] - 0.5 + L) {
			chk[j] = true;
			++j;
		}
	}
	cout << tape_cnt;
	return 0;
}