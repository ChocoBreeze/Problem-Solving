// 중간 값 뽑기
// 중간 값 기준으로 작은 원소들 --> maxheap
// 중간 값 기준으로 큰 원소들 --> min heap
// 즉 2개로 나누어 관리 (처음에 이 생각을 못 함!)
#include<iostream>
#include<queue> 

int main() {
	int N, temp, mid;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::priority_queue<int> max_heap; // top에 가장 큰 원소
	std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap; // top에 가장 작은 원소
	for (int i = 0; i < N; ++i) {
		std::cin >> temp;
		if (i == 0) mid = temp;
		else {
			if (mid <= temp) {
				min_heap.push(temp);
				if (min_heap.size() == max_heap.size() + 2) {
					max_heap.push(mid);
					mid = min_heap.top();
					min_heap.pop();
				}
			}
			else {
				max_heap.push(temp);
				if (max_heap.size() == min_heap.size() + 2) {
					min_heap.push(mid);
					mid = max_heap.top();
					max_heap.pop();
				}
				else if (max_heap.size() == min_heap.size() + 1) {
					if (max_heap.top() < mid) {
						min_heap.push(mid);
						mid = max_heap.top();
						max_heap.pop();
					}
				}
			}
		}
		std::cout << mid << "\n";
	}
	return 0;
}