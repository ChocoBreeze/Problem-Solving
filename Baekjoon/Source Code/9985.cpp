// Meet In the Middle, Tree(Set, Map)
// https://m.blog.naver.com/kks227/221382873753 ����..

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

// ���� ����, �� ����, Q�� ���� �����Ϳ� ����ü
struct Data { 
	int x, y; // X ��ġ
	vector<int> board; //
	Data(int d) : x(0), y(0), board(d * d, 0) {}
	Data(int x, int y, vector<int> board) : x(x), y(y), board(board) {}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	while (1) {
		string str;
		int D{}, N{}; // D : Dimension, N : # of moves
		cin >> str >> D >> N; // START, D, N;
		if (cin.eof()) break;
		vector<Data> in(2, Data(D));
		for (int i{}; i < 2; ++i) {
			for (int x{}; x < D; ++x) {
				for (int y{}; y < D; ++y) {
					string n;
					cin >> n;
					if (n == "X") {
						in[i].x = x, in[i].y = y;
					}
					else {
						in[i].board[D * x + y] = stoi(n);
					}
				}
			}
		}

		vector<map<vector<int>, int>> visitedMap(2, map<vector<int>, int>());
		// M[0] : in[0](���� ����)���� �� board ���±����� �Ÿ�
		// M[1] : in[1](���� ����)���� �� board ���±����� �Ÿ�
		for (int k{}; k < 2; ++k) {
			queue<Data> q;
			q.emplace(in[k].x, in[k].y, in[k].board);
			visitedMap[k].emplace(in[k].board, 0); // visitedMap[k][in[k].board] = 0;

			// N�� ���ݸ�ŭ, N�� Ȧ����� ������ �ʿ����� �ϳ� �� ���� Ž���ϱ�
			for (int i{}; i < N / 2 + ((N % 2) & k); ++i) { // BFS => �Ÿ����� �ǹ���.
				int qSize = static_cast<int>(q.size());
				for (int s{}; s < qSize; ++s) {
					Data now = q.front(); q.pop();
					auto& [nowX, nowY, nowBoard] = now;

					int emptyNum = nowX * D + nowY; // �� ĭ�� 1���� ��ȣ

					for (int d{}; d < 4; ++d) {
						int nx = nowX + "0211"[d] - '1';
						int ny = nowY + "1102"[d] - '1';

						if (nx < 0 || nx >= D || ny < 0 || ny >= D) continue;
						int nNum = nx * D + ny;

						// ���� ���͸� ����� ���� �ƴ� ���� ����(now)���� �� ĭ�� swap�ؼ� ���.
						swap(nowBoard[emptyNum], nowBoard[nNum]);
						if (visitedMap[k].find(nowBoard) == visitedMap[k].end()) { // ���� �̹湮
							visitedMap[k].emplace(nowBoard, i + 1); // (or visitedMap[k][now.board] + 1)
							q.emplace(nx, ny, nowBoard);
						}
						swap(nowBoard[emptyNum], nowBoard[nNum]); // �ٽ� ����
					}
				}
			}
		}

		// �� ����
		int answer{ N + 1}; // ���� ���� N
		for (auto& key : views::keys(visitedMap[0])) { // const std::vector<int>& key

			/*
			* key �ٲ���� Ȯ�ο�
			for (const int& k : key) cout << k << ' ';
			cout << '\n';
			*/

			auto it = visitedMap[1].find(key); // map<vector<int>, int>::iterator
			if (it != visitedMap[1].end()) { // ������������ ���� ������
				answer = min(answer, visitedMap[0][key] + visitedMap[1][key]);
				// ���� �� �ɸ� ��?
			}
		}
		if (answer <= N) cout << "SOLVABLE WITHIN " << answer << " MOVES\n\n";
		else cout << "NOT SOLVABLE WITHIN " << N << " MOVES\n\n";
		cin >> str; // END
	}
	return 0;
}