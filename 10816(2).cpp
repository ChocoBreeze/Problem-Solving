// unordered_map으로 count
#include<iostream>
#include<unordered_map>

using std::unordered_map;
using std::cin;
using std::cout;
using std::make_pair;

int main()
{
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, tmp;
	unordered_map<int, int> Card;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> tmp;
		if (Card.find(tmp) != Card.end()) // 이미 기존 카드 존재
			Card[tmp]++;
		else 
			Card.insert(make_pair(tmp, 1));
	}
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> tmp;
		if (Card.find(tmp) != Card.end()) cout << Card[tmp] << " "; // 찾은 경우
		else cout << "0 ";
	}
	return 0;
}