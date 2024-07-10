#include <iostream>
#include <cmath>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int D, H, W; cin >> D >> H >> W;
	// ���� = H * x, �ʺ� = W * x
	// D * D = {H * x}^2 + {W * x}^2
	// (H^2 + W^2)x^2 = D^2
	// x = sqrt(D^2 / (H^2+W^2)
	double x = sqrt(static_cast<double>(D) * D / (H * H + W * W));
	int h = H * x, w = W * x;
	cout << h << ' ' << w << '\n';
	return 0;
}