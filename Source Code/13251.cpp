#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int M, K;
	cin >> M; // 색상 종류
	vector<int> N(M,0); // 각 색상의 조약돌이 몇 개인지
	int sum = 0;
	for (auto& i : N) {
		cin >> i; 
		sum += i; 
	}
	
	cin >> K; // 뽑는 개수
	// 모두 같은 색일 확률 구하기
	double answer = 0;
	for (auto& i : N) {
		double tmp = 1;
		for (int j = 1; j <= K; ++j) {
			tmp *= (static_cast<double>(i) - j + 1) / (sum - j + 1);
		}
		answer += tmp;
	}
	cout << fixed;
	cout.precision(20);
	cout << answer;
	return 0;
}