#include<iostream>
#include<set>
using std::set;
using std::cin;
using std::cout;
int main()
{
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, tmp;
	set<int> Card;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> tmp;
		Card.insert(tmp);
	}
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> tmp;
		if (Card.find(tmp) != Card.end()) cout << "1 "; // 찾은 경우
		else cout << "0 ";
	}
	return 0;
}