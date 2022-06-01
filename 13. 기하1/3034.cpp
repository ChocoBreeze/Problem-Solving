#include<iostream>
using std::cin;
using std::cout;
int main() {
	int N, W, H, temp;
	cin >> N >> W >> H;
	int diagonal = W * W + H * H;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		if (temp * temp <= diagonal) cout << "DA\n";
		else cout << "NE\n";
	}
	return 0;
}