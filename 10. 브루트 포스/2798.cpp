#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::vector;
int main() {
	int N, M, temp;
	cin >> N >> M;
	vector<int> card;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		card.push_back(temp);
	}
	temp = -1;
	for (int i = 0; i < N - 2; ++i) {
		for (int j = i + 1; j < N - 1; ++j) {
			for (int k = j + 1; k < N; ++k) {
				if (card[i] + card[j] + card[k] > temp && card[i] + card[j] + card[k] <= M)
					temp = card[i] + card[j] + card[k];
			}
		}
	}
	std::cout << temp;
	return 0;
}