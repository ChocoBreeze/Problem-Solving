// 직접 구현해보려다가 실패..
#include <iostream>
#include <vector>
#include <algorithm>

int kth(std::vector<int>&a, int k) {
	std::nth_element(begin(a), begin(a) + k - 1, end(a));
	int ans = a[k - 1]; // 0번 기준
	return ans;
}

// https://modoocode.com/287
// https://www.acmicpc.net/source/56186197
// quickSelect ..