#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;

	vector<int> levels(N, 0), answer;
	for (int& l : levels) cin >> l;
	
	for (int& l : levels) {
		if (l == 300) answer.push_back(1);
		else if (l >= 275) answer.push_back(2);
		else if (l >= 250) answer.push_back(3);
		else answer.push_back(4);
	}

	for (int& a : answer) cout << a << ' ';
	cout << '\n';

	return 0;
}