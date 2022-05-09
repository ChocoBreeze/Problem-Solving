#include<iostream>
#include<set>
#include<string>
#include<vector>

using std::string;
using std::set;
using std::cin;
using std::cout;

int main()
{
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, cnt = 0;
	string tmp;
	set<string> dd; // 듣
	set<string> bo; // 보
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> tmp;
		dd.insert(tmp);
	}
	for (int i = 0; i < M; ++i) {
		cin >> tmp;
		if (dd.find(tmp) != dd.end()) ++cnt; // 지금 찾으면 사전 순 정렬 x
		bo.insert(tmp);
	}
	cout << cnt << "\n";
	for (auto& i : dd) {
		if (bo.find(i) != bo.end()) cout << i << "\n";
	}
	return 0;
}