#include<iostream>
#include<unordered_set>
#include<string>
using std::string;
using std::unordered_set;
using std::cin;
using std::cout;
int main()
{
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, cnt=0;
	string tmp;
	unordered_set<string> strs;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> tmp;
		strs.insert(tmp);
	}
	for (int i = 0; i < M; ++i) {
		cin >> tmp;
		if (strs.find(tmp) != strs.end()) ++cnt; // 존재하는 경우
	}
	cout << cnt;
	return 0;
}