#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

struct Data {
	int direction;
	int length;
	Data(int direction, int length) : direction(direction), length(length) {}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int K, direction, length;
	int minus_S = 0, garo = -1, sero = -1;
	cin >> K; // 1m^2 당 참외
	vector<Data> datas;
	for (int i = 0; i < 6; ++i) {
		cin >> direction >> length;
		datas.push_back(Data(direction, length));
		if ((direction == 1 || direction == 2) && garo < length) garo = length;
		if ((direction == 3 || direction == 4) && sero < length) sero = length;
	}
	for (int i = 0; i < 6; ++i) { // i i+1 i+2 i+3 dir1 dir2 dir1 dir2
		if (datas[i].direction == datas[(i + 2) % 6].direction && datas[(i + 1) % 6].direction == datas[(i + 3) % 6].direction) {
			minus_S = datas[(i + 2) % 6].length * datas[(i + 1) % 6].length;
		}
	}
	cout << (garo * sero - minus_S) * K;
	return 0;
}