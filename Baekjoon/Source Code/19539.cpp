// https://young1403.tistory.com/58
// 총합이 3의 배수인가(O)
// 각각을 2로 나눈 몫이 총합을 3으로 나눈 몫보다 크거나 같은가(생각 X)
#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N{}, h{};
	cin >> N;

	int divby2{}, sum{};
	for (int n = 0; n < N; ++n) {
		cin >> h;
		sum += h;
		divby2 += (h / 2);
	}
	if (sum % 3) {
		cout << "NO\n";
	}
	else {
		if (divby2 < sum / 3) cout << "NO\n";
		else cout << "YES\n";
	}
	
	return 0;
}