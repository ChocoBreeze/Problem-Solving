#include<vector>
#include<stack>
#include<iostream>

// 266가지 문제로 정복하는 코딩 인터뷰 in C++
// 문제 17.8
// 이번 입력보다 크거나 같은 모든 height pop하면서 최대 넓이 계산

long long int CalculateLargestRectangle(std::vector<int>& heights) {
	int N = heights.size();
	long long int max_area = -1;
	std::stack<int> stack_height_index;
	for (int i = 0; i <= N; ++i) {
		while (!stack_height_index.empty() && ((i>=N) || heights[i] <= heights[stack_height_index.top()])) {
			long long int height = heights[stack_height_index.top()];
			stack_height_index.pop();
			long long int width = stack_height_index.empty() ? i : i - stack_height_index.top() - 1;// empty인 경우 지금 높이가 최소 높이 --> i가 width
			if (max_area < width * height) max_area = width * height;
		}
		stack_height_index.push(i);
	}
	return max_area;
}

int main() {
	int n;
	while (1) {
		std::cin >> n; // ~100000
		std::vector<int> heights(n, 0); 
		if (n == 0) break;
		for (int i = 0; i < n; ++i) {
			std::cin >> heights[i]; // ~ 1000000000
		}
		std::cout << CalculateLargestRectangle(heights) << "\n";
	}
	return 0;
}