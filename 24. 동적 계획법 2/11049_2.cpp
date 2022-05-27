// 행렬 2개로 분할해서 solve하면 안 될까?
// N x M 인 행렬과 M x K인 행렬 곱 --> N x M x K
/*
* 5 3
* 3 2
* 2 6
*/
#include<iostream>
#include<vector>
#include<climits> // INT_MAX
#include<algorithm> // std::min
#include<utility> // pair

struct matrix {
	int row;
	int column;
	matrix(int r, int c) : row(r), column(c) {}
};

using std::vector;
using std::cin;
using std::cout;
using std::min;
using std::pair;
using std::make_pair;

pair<matrix,int> DP(vector<matrix>& matrices, vector<vector<pair<matrix, int>>>& costs, int start, int end) { // return type
	if (start == end) return costs[start][start];
	int& temp1 = costs[start][end].second;
	matrix& temp2 = costs[start][end].first;
	if (temp1 != INT_MAX) return costs[start][end];
	for (int i = start; i < end; ++i) {
		auto mat1 = DP(matrices, costs, start, i);
		auto mat2 = DP(matrices, costs, i + 1, end);
		int costs = mat1.first.row * mat1.first.column * mat2.first.column + mat1.second + mat2.second;
		if (temp1 > costs) {
			temp1 = costs;
			temp2 = matrix(mat1.first.row, mat2.first.column);
		}
	}
	return make_pair(temp2, temp1);
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, r, c;
	cin >> N;
	vector<matrix> matrices;
	vector<vector<pair<matrix, int>>> costs(N, vector<pair<matrix, int>>(N, make_pair(matrix(-1, -1), INT_MAX)));
	for (int i = 0; i < N; ++i) {
		cin >> r >> c;
		matrices.push_back(matrix(r, c));
		costs[i][i].first.row = r;
		costs[i][i].first.column = c;
		costs[i][i].second = 0;
	}
	
	// 2개로 분할하는 방식으로 가면 될 것 같음.
	int answer = INT_MAX;
	for (int i = 0; i < N - 1; ++i) {
		auto mat1 = DP(matrices, costs, 0, i);
		auto mat2 = DP(matrices, costs, i + 1, N - 1);
		int costs = mat1.first.row * mat1.first.column * mat2.first.column + mat1.second + mat2.second;
		answer = min(answer, costs);
	}
	cout << answer;
	return 0;
}