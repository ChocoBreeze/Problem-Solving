#include<iostream>
#include<string>

int main() {
	std::string str;
	std::getline(std::cin, str);
	int start = str.find_first_not_of(' '); // 영어 시작 위치 찾기
	int last = str.find_last_not_of(' '); // 마지막 위치 찾기
	str.erase(last + 1); // 지울 시작 위치 --> 뒤에 것 부터 지워야 인덱스 맞음.
	str.erase(0, start); // 좌측 공백 제거


	int index = -1, count = 0;
	while (1) {
		index = str.find(' ', index + 1);
		count++;
		if (index == std::string::npos) break; // not found
	}
	if (str.length() == 0) {
		std::cout << 0;
		return 0;
	}
	std::cout << count;
	return 0;
}