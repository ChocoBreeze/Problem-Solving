#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//greater or equal to
vector<int>::iterator l_bound(vector<int>& A, vector<int>::iterator iter0, vector<int>::iterator iter1, int value) {	
	while (distance(iter0, iter1) > 0) {
		auto mid = iter0 + 0.5 * distance(iter0, iter1);
		if (A[*mid] < value) iter0 = mid + 1;
		else iter1 = mid;
	}
	return iter1;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N, 0);
	
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	vector<int> answer = {0}; // index로?
	vector<int> answer_index (N, -1);
	for (int i = 1; i < N; ++i) {
		if (A[i] > A[answer.back()])
		{
			answer_index[i] = answer.back(); // 이전 값 저장
			answer.push_back(i);
		}
		else {
			auto it = l_bound(A, answer.begin(), answer.end(), A[i]);
			int index = distance(begin(answer), it); // 넣을 위치
			if (index == 0) answer_index[i] = -1;
			else answer_index[i] = answer[index - 1];
			answer[index] = i;
		}
	}
	cout << answer.size() << "\n";
	int start = answer.back();
	vector<int> final_answer;
	while (answer_index[start] != -1) {
		final_answer.push_back(A[start]);
		start = answer_index[start];
	}
	final_answer.push_back(A[start]);
	for (auto i = rbegin(final_answer); i!=rend(final_answer); ++i) {
		cout << *i << " ";
	}
	return 0;
}