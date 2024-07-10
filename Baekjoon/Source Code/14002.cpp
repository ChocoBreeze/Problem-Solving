#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N + 1, 0);
	
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	vector<int> answer_index(N + 1);
	vector<int> list(N + 1, 1);
	int start = 1, max = 1;
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j < i; ++j) {
			if (list[i] < list[j] + 1 && A[j] < A[i]) {
				list[i] = list[j] + 1;
				answer_index[i] = j;
			}
			if (list[i] > max) {
				max = list[i];
				start = i;
			}
		}
	}
	vector<int> answer;
	while (answer_index[start] != 0) {
		answer.push_back(A[start]);
		start = answer_index[start];
	}
	answer.push_back(A[start]);
	cout << max<<"\n";
	for (auto i = answer.rbegin(); i != answer.rend(); ++i) {
		cout << *i << " ";
	}
	return 0;
}