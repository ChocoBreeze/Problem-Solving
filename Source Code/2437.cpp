#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;
	vector<int> weights(N, 0);
	for (int& w : weights) cin >> w;
	sort(begin(weights), end(weights));
	vector<int> possibleWeights{ 0 };
	possibleWeights.reserve(N * N);
	
	int checkWeight = 1;
	for (int n{}; n < N; ++n) {
		int curSize = static_cast<int>(possibleWeights.size());
		for (int s{}; s < curSize; ++s) {
			if (checkWeight < possibleWeights[s] + weights[n]) {
				cout << checkWeight << '\n';
				return 0;
			}
			else if (checkWeight == possibleWeights[s] + weights[n]) {
				possibleWeights.push_back(possibleWeights[s] + weights[n]);
				++checkWeight;
			}
		}
	}
	cout << checkWeight << '\n'; // 최대무게까지 빠짐없이 만들 수 있는 
	return 0;
}