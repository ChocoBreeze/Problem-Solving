// Q : 연산 수
// D : 삭제 (empty -> 무시)
// D 1 : 최대값 삭제, D -1 : 최소값 삭제
// l : 삽입
// 처음 아이디어 : 벡터를 그냥 힙으로 만들어서 삭제나 삽입마다 자료 순서 정리 -> 시간 초과
// 2. idea : deque + make_heap (삭제 때만 힙으로 만들어서 삭제) -> 시간 초과
// 일반적인 구현 max_heap + min_heap + map(개수 관리)

#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<utility> // pair

using std::make_pair;
using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::unordered_map;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, Q;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> Q; // query 수
		priority_queue<int> max_heap; // default
		priority_queue<int, vector<int>, std::greater<int>> min_heap; 
		unordered_map<int, int> map_cnt;		
		char query;
		int d;
		for (int q = 0; q < Q; ++q) {
			cin >> query;
			if (query == 'D') { // 삭제
				cin >> d;
				if (max_heap.empty() && min_heap.empty()) continue;
				if (d == 1) { // 최대값
					map_cnt[max_heap.top()]--;
					max_heap.pop();
				}					
				else if (d == -1) {
					map_cnt[min_heap.top()]--;
					min_heap.pop();
				}
			}
			else if (query == 'I') {
				cin >> d;
				max_heap.push(d);
				min_heap.push(d);
				if (map_cnt.find(d) == map_cnt.end()) map_cnt.insert(make_pair(d, 1));
				else map_cnt[d]++;
			}
			// 두 힙 간에 개수 맞춰주기
			while (!max_heap.empty() && map_cnt[max_heap.top()] == 0) {
				max_heap.pop();
			}
			while (!min_heap.empty() && map_cnt[min_heap.top()] == 0) {
				min_heap.pop();
			}
		}
		if (max_heap.empty() && min_heap.empty()) cout << "EMPTY\n";
		else {
			cout << max_heap.top() << " " << min_heap.top() << "\n";
		}
	}
	return 0;
}