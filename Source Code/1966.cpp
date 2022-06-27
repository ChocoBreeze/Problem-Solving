#include<iostream>
#include<queue> 
int main() {
	int T, N, M;
	std::cin >> T; // 테스트 케이스
	for (int i = 0; i < T; ++i) {
		std::cin >> N >> M; // 문서의 수, 순서를 알고 싶은 문서의 번호
		std::priority_queue<int> doc_list;
		std::queue<std::pair<int,int>> doc; // priority, index
		int temp;
		for (int j = 0; j < N; ++j) {
			std::cin >> temp;
			doc.emplace(temp, j);
			doc_list.push(temp);
		}
		int cnt = 1;
		while (1) {
			if (doc.front().first == doc_list.top()) { // 가장 우선순위 높은 원소
				if (doc.front().second == M) {
					std::cout << cnt << "\n";
					break;
				}
				doc_list.pop();
				doc.pop();
				cnt++; // 인쇄순서만 카운트
			}
			else { // 제일 뒤로 이동
				int priority = doc.front().first;
				int index = doc.front().second;
				doc.pop();
				doc.push(std::make_pair(priority, index));
			}
		}
	}
	return 0;
}