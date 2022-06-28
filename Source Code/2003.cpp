// https://ssungkang.tistory.com/entry/Algorithm-Two-Pointers-%ED%88%AC-%ED%8F%AC%EC%9D%B8%ED%84%B0
// https://velog.io/@adorno10/%ED%88%AC-%ED%8F%AC%EC%9D%B8%ED%84%B0-Two-Pointer

#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	// 정렬할 필요 없음
	int N, M, answer = 0, cur_sum = 0;
	cin >> N >> M;
	vector<int> A(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	auto front = A.begin(), back = A.begin();
	cur_sum = A[0];
	while (front!=A.end()) {
		if (cur_sum <= M) {
			if (cur_sum == M) ++answer;
			++back;
			if (back == A.end()) break; // 더 볼 필요 없음
			cur_sum += *back;
		}
		else if (cur_sum > M) {
			cur_sum -= *front;
			++front;
		}
	}
	cout << answer;
	return 0;
}