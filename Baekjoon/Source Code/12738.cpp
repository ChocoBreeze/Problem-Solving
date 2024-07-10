#include<iostream>
#include<vector>
#include<algorithm>
int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> A(N, 0);
	for (auto& i : A) {
		std::cin >> i;
	}
	std::vector<int> answer;
	answer.push_back(A[0]);
	for (int i = 1; i < N; ++i) {
		if (answer[answer.size() - 1] < A[i]) answer.push_back(A[i]);
		else { // lower_bound(해당 값보다 크거나 같은 값이 처음으로 나오는 지점) 찾아서 넣기 - logn
			auto it = std::lower_bound(answer.begin(), answer.end(), A[i]);
			int place = std::distance(answer.begin(), it); // first -> last 까지 가는 거리
			answer[place] = A[i];
		}
	}
	std::cout << answer.size();
	return 0;
}