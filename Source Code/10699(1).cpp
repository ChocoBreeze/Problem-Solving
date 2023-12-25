#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <chrono>

int main() {
	auto utcTime = std::chrono::system_clock::now(); // 표준시
	// auto krTime = utcTime + std::chrono::hours(9);
	// std::cout << utcTime << '\n';
	// std::cout << krTime << '\n';

	// std::chrono::time_point를 문자열로 변환하여 출력
	// 굳이 9시간을 안 더해줘도 됨.
	std::time_t time = std::chrono::system_clock::to_time_t(utcTime);
	std::tm timeInfo = *std::localtime(&time);

	// std::cout << "Current time: " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << '\n';
	std::cout << std::put_time(&timeInfo, "%Y-%m-%d") << '\n';
	
	return 0;
}