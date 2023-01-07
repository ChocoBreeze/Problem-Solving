#include <iostream>
#include <list>
#include <utility>

using namespace std;
using p = pair<int,int>;

int main() {
	int N, a;
	cin >> N;
	list<p> L;
	for (int n = 1; n <= N; ++n) {
		cin >> a;
		L.push_back(make_pair(n,a));
	}
	auto it = L.begin();
	while (1) {
		// auto tmp_it = next(it, it->second);
		auto tmp_it = it;
		// 한 칸 이동
		int tmp_move = it->second;
		if (tmp_move > 0) {
			if ((++tmp_it) == L.end()) tmp_it = L.begin();
			--tmp_move;
		}
		else { // tmo_move < 0
			if (tmp_it == L.begin()) tmp_it = --L.end();
			else tmp_it--;
			++tmp_move;
		}

		// 터뜨리기
		cout << it->first << " ";
		L.erase(it);
		if (L.empty()) break;

		// 남은 이동
		if (tmp_move < 0) {			
			for (; tmp_move < 0; ++tmp_move) {
				if (tmp_it == L.begin()) tmp_it = --L.end();
				else tmp_it--;
			}
		}
		else if(tmp_move>0) {
			for (; tmp_move > 0; --tmp_move) {
				if ((++tmp_it) == L.end()) tmp_it = L.begin();
				// else tmp_it++;
			}
		}
		it = tmp_it;
	}

	return 0;

}