/*
* 저는 이렇게 풉니다.
(1) 함수를 만들어 봅니다.
(2) 이것이 항상 증가, 혹은 항상 감소하는 것인지 따져봅니다.
(3) 만약 그렇다면 반씩 쪼개서 풀어봅니다.
*/
// 최적화 문제 --> 판정 문제
#include<vector>
#include<iostream>
int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	long long int N, k;
	std::cin >> N >> k;
	long long int start = 1, end = k; // k번째 수보다 작은 수가 k보다 작거나 같으므로 k로 해도 무관함
	while (start < end) {
		long long int mid = start + (end - start) / 2;
		// mid보다 작거나 같은 숫자의 개수 세기
		long long int cnt = 0;
		for (int i = 1; i <= N; ++i) {
			cnt += std::min(mid / i, N);
		}
		if (cnt < k) start = mid + 1;
		else end = mid;
	}
	std::cout << start;
	return 0;
}