/*
끊어진 기타줄 N / 기타줄 브랜드 M
M개만큼 6개 가격 / 1개 가격
적어도 N개를 사기 위해 필요한 돈의 수
*/
// 다 6개로 사거나 6개로 최대한 사고 나머지 채우기 다 낱개로 사기.
#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::vector;
using std::cout;
using std::min;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	int min_p6 = 1001, min_p = 1001;
	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		min_p6 = min(min_p6, a);
		min_p = min(min_p, b);
	}
	int answer = 0;
	if (min_p * 6 <= min_p6) {
		// 무조건 낱개가 이득
		answer = N * min_p;
	}
	else {
		int quotient = N / 6;
		int remainder = N % 6;
		answer = min(quotient * min_p6 + remainder * min_p, (quotient + 1) * min_p6);
	}
	cout << answer;
	return 0;
}