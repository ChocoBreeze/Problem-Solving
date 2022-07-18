// indexed tree
#include <iostream>
#include <vector>

using namespace std;
// 사탕의 레벨 : 1 ~ 1000000 (level이 leaf node 구성) -> 2^20
const int BASE = 1 << 20; // leaf node 개수
const int TSIZE = 1 << 21; // Tree를 구성하는 총 node
// internal node : 1 ~ BASE - 1

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, A, B, C = 0;
	cin >> N;
	vector<int> iTree(TSIZE, 0); // indexed tree
	
	for (int n = 0; n < N; ++n) {
		cin >> A >> B;
		if (A == 2) cin >> C;

		if (A == 1) {
			// 사탕 상자 안에서 B번째로 맛있는 사탕을 한 개 꺼낸 후 레벨 출력
			int index = 1;
			while (index < TSIZE) {
				if (B > iTree[index]) { // 이 개수안에 못 들음
					B -= iTree[index];
					index++; // 옆 노드로 이동
				}
				index *= 2;
			}
			index /= 2; // TREE를 벗어남
			B = index - BASE; // 시작점이 BASE
			cout << B << "\n";
			C = -1; // 밑에 단계 = 사탕 추가(C=-1이면 사탕을 빼는 것)
		}
		B += BASE;
		while (B) {
			iTree[B] += C;
			B /= 2; // 부모 노드로 이동
		}
	}
	return 0;
}