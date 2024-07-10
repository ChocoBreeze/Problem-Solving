#include<iostream> // std::cin, std::cout
#include<vector> // std::vector
#include<utility> // std::pair;
#include<algorithm>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	pair<long long, long long> pinary_cnt(0,1);
	for (int i = 0; i < N - 1; ++i) {
		long long cnt_0 = pinary_cnt.first;
		long long cnt_1 = pinary_cnt.second;
		pinary_cnt.first = cnt_0 + cnt_1;
		pinary_cnt.second = cnt_0;
	}
	cout << pinary_cnt.first + pinary_cnt.second;
	return 0;
}