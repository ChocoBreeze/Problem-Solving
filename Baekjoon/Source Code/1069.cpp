#include <iostream>
#include <cmath>

using namespace std;
// ���̵��
// https://blog.naver.com/PostView.naver?blogId=kks227&logNo=220610580318
// �Ź��ϳ�..

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int X, Y, D, T; cin >> X >> Y >> D >> T;
	// (X, Y) -> (0, 0)
	// ���� : T�ʿ� D��ŭ �����̱�

	double dist = sqrt(X * X + Y * Y);
	double answer{};
	if (dist < D) {
		// �� �ָ� ���� �� �ȱ� (
		double jumpAndWalk = T + (D - dist);
		// �׳� �ȱ�
		double walk{ dist };
		// �� �� �ٱ�
		double twoJump = 2 * T;
		answer = min({ jumpAndWalk, walk, twoJump });
	}
	else { // dist >= D
		// 2�� �̻� �����ؾ� ��. => ������ �� �°� �� �� ����.
		// �׳� �ȱ�
		double walk{ dist };
		int minJump = static_cast<int>(dist / D);
		// only jump - (minJump + 1)��
		double jump = T * (minJump + 1);
		// jump(minJump) �� ���� �Ÿ� �ȱ�
		double jumpAndWalk = T * minJump + (dist - (D * minJump));
		answer = min({ walk, jump, jumpAndWalk });
	}

	cout << fixed;
	cout.precision(10);
	cout << answer << '\n';
	return 0;
}
