#include <iostream>
#include <set> 

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int N, temp;
	cin >> N;
	set<int> S;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		S.insert(temp);
	}
	for (auto& i : S) {
		cout << i << " ";
	}
	return 0;
}