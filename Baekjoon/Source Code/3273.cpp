// https://ssungkang.tistory.com/entry/Algorithm-Two-Pointers-%ED%88%AC-%ED%8F%AC%EC%9D%B8%ED%84%B0
// https://velog.io/@adorno10/%ED%88%AC-%ED%8F%AC%EC%9D%B8%ED%84%B0-Two-Pointer

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
	int n, answer = 0, x;
	cin >> n;
	vector<int> A(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
	}
	cin >> x;
	sort(A.begin(), A.end());
	auto front = A.begin(), back = A.end() - 1;
	while (std::distance(front, back) > 0) {
		int sum = *front + *back;
		if (sum == x) {
			++answer;
			++front;
			--back;
		}
		else if (sum < x) ++front;
		else --back;
	}
	cout << answer;
	return 0;
}