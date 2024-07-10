#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int>::iterator l_bound(vector<int>::iterator iter0, vector<int>::iterator iter1, int value) {
	while (distance(iter0, iter1) > 0) {
		auto mid = iter0 + 0.5 * distance(iter0, iter1);
		if (*mid > value) iter0 = mid + 1;
		else iter1 = mid;
	}
	return iter1;
}


int main() {
	int N;
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N;
	vector<int> A(N, 0);
	for (auto& i : A) {
		std::cin >> i;
	}
	vector<int> answer;
	answer.push_back(A[0]);
	for (int i = 1; i < N; ++i) {
		if (answer.back() > A[i]) answer.push_back(A[i]);
		else { // lower_bound(해당 값보다 작거나 같은 값이 처음으로 나오는 지점) 찾아서 넣기 - logn
			auto it = l_bound(begin(answer), end(answer), A[i]);
			int place = distance(begin(answer), it); // first -> last 까지 가는 거리
			if (place == answer.size()) answer[place - 1] = A[i];
			else answer[place] = A[i];
		}
	}
	std::cout << answer.size();
	return 0;
}