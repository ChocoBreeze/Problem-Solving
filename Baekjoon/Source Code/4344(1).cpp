// �Ϲ����� �ڵ� �ݿø� - IEEE754�� ���� �������
// �� ���� - ������ ��� ä��
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=noseoul1&logNo=221592047071

/*
Round-off ( �ϸ� ������, 4���� ������, 5�� ���δٴ� ��)
�׷��� 0,1,2,3,4�� ���� ���ְ� 5,6,7,8,9�� �ø� ���ش�.

Round-to-nearest-even (�ϸ� ���� ����)
0,1,2,3,4�� �����ϰ�, 6,7,8,9�� �ø� �Ѵ�. 
�׸��� 5�� �� 5�� ���ڸ��� ¦�� �� ������ 5�� ���ڸ��� Ȧ�� �� �ø��� ���ش�. 
�� ���ڸ��� ¦���� ����� �ִ� ����̴�.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int C{}; cin >> C;
	while (C--) {
		int N{}, cnt{}; cin >> N;
		double sum{};
		vector<int> grades(N, 0);
		for (int& g : grades) {
			cin >> g;
			sum += g;
		}
		sum /= N;
		for (int& g : grades) {
			if (sum < g) ++cnt;
		}
		cout << fixed;
		cout.precision(3);
		// 0.000004 -> 0.000
		// 0.000005 -> 0.001
		if ( 1'000'000 * cnt / N % 10 == 5) { // �ش� ��ġ�� 5�� ��쿡 + 0.000005
			cout << 100 * (static_cast<double>(cnt) / N + 0.000005) << "%\n";
		}
		else {
			cout << 100 * (static_cast<double>(cnt) / N) << "%\n";
		}
		// cout << static_cast<double>(cnt) / N * 100 << "%\n";
	}
	return 0;
}