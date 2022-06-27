#include<iostream>
#include<vector>
#include<deque>
#include<string>
int main() {
	int T, n, chk, reverse_cnt;
	std::string func, list_str;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> T;
	for (int i = 0; i < T; ++i) {
		std::cin >> func;		// Rd...
		std::cin >> n;			// element 개수
		std::cin >> list_str;	// [원소,원소,...]
		std::deque<int> list_;	// 원소를 넣을 곳
		std::string::size_type start = 1;
		chk = 0;
		reverse_cnt = 0; // std::reverse -> 시간초과 
		while (1) { // deque에 원소 채우기
			auto place = list_str.find(',', start);
			if (place != std::string::npos) {
				list_.push_back(stoi(list_str.substr(start, place - start)));
				start = place + 1;
			}
			if (list_.size() == n - 1) { // 마지막 원소 처리
				auto place = list_str.find(']', start);
				list_.push_back(stoi(list_str.substr(start, place - start)));
			}
			if (place == std::string::npos) break;
		}
		for (int j = 0; j < func.length(); ++j) {
			if (func[j] == 'R') { // reverse
				reverse_cnt++;
			}
			else if (func[j] == 'D') { // drop
				if (list_.empty()) {
					std::cout << "error" << "\n";
					chk = 1;
					break;
				}
				else {
					if (reverse_cnt % 2 == 0) list_.pop_front(); // 원본
					else list_.pop_back(); // 뒤집힘
				}
			}
		}
		if(chk==0) {
			std::cout << "[";
			if (!list_.empty()) {
				if (reverse_cnt % 2 == 0) { // 원본
					for (auto j = list_.begin(); j != list_.end() - 1; ++j) {
						std::cout << *j << ",";
					}
					std::cout << *(list_.end() - 1);
				}
				else { // 거꾸로
					for (auto j = list_.rbegin(); j != list_.rend() - 1; ++j) {
						std::cout << *j << ",";
					}
					std::cout << *(list_.rend() - 1);
				}
			}
			std::cout << "]\n";
		}
	}
	return 0;
}