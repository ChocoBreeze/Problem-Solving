// 일반적인 코드 반올림 - IEEE754에 따른 오사오입
// 이 문제 - 사사오입 방식 채점
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=noseoul1&logNo=221592047071

/*
Round-off ( 일명 사사오입, 4까지 버리고, 5는 들인다는 뜻)
그러니 0,1,2,3,4는 버림 해주고 5,6,7,8,9는 올림 해준다.

Round-to-nearest-even (일명 오사 오입)
0,1,2,3,4는 버림하고, 6,7,8,9는 올림 한다. 
그리고 5일 때 5의 앞자리가 짝수 면 버림을 5의 뒷자리가 홀수 면 올림을 해준다. 
즉 끝자리를 짝수로 만들어 주는 방법이다.
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
		if ( 1'000'000 * cnt / N % 10 == 5) { // 해당 위치가 5인 경우에 + 0.000005
			cout << 100 * (static_cast<double>(cnt) / N + 0.000005) << "%\n";
		}
		else {
			cout << 100 * (static_cast<double>(cnt) / N) << "%\n";
		}
		// cout << static_cast<double>(cnt) / N * 100 << "%\n";
	}
	return 0;
}