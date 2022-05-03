#include<iostream>
#include<vector>
#include<deque>
#include<algorithm> // std::distance
int main() {
	int N, M;
	std::cin >> N >> M;
	std::vector<int> find_list(M, 0);
	std::deque<int> Q;
	for (int i = 0; i < M; ++i) {
		std::cin >> find_list[i];
	}
	for (int i = 1; i <= N; ++i) {
		Q.push_back(i);
	}
	int cnt = 0, list_index = 0;
	
	while (list_index != find_list.size()) {
		if (Q.front() == find_list[list_index]) { // pop
			Q.pop_front();
			list_index++;
		}
		else { // rotation
			auto index = std::find(Q.begin(), Q.end(), find_list[list_index]);
			auto r_distance = std::distance(Q.begin(), index);
			auto l_distance = std::distance(index, Q.end());
			if (r_distance > l_distance) {// left-move 
				while (Q.front() != find_list[list_index]) {
					int temp = Q.front();
					Q.pop_front();
					Q.push_back(temp);
				}
				cnt += l_distance;
			}
			else { // right-move
				while (Q.front() != find_list[list_index]) {
					int temp = Q.back();
					Q.pop_back();
					Q.push_front(temp);
				}
				cnt += r_distance;
			}
		}
	}
	std::cout << cnt;
	return 0;
}