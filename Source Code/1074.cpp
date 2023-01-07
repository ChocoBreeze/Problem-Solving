#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, r, c;
	cin >> N >> r >> c;
	// 2^30 = 1,073,741,824
	int length = 1 << N; // 한 변 길이
	
	int answer = 0;
	int start_x = 0, start_y = 0, finish_x = length - 1, finish_y = length - 1;
	while (length > 0) {
		int middle_x = start_x + (length / 2), middle_y = start_y + (length/2);
		length /= 2; // 바로 length == 0 break 걸면 한 번 덜 수행
		int quarter = (length * length);
		if ((r >= start_x && r < middle_x) && (c >= start_y && c < middle_y)) { // 1
			finish_x = middle_x;
			finish_y = middle_y;
		}
		else if ((r >= start_x && r < middle_x) && (c >= middle_y && c <= finish_y)) { // 2
			answer += quarter;
			finish_x = middle_x;
			start_y = middle_y;
		}
		else if ((r >= middle_x && r <= finish_x) && (c >= start_y && c < middle_y)) { // 3
			answer += quarter * 2;
			start_x = middle_x;
			finish_y = middle_y;
		}
		else { // 4 (r >= middle_x && r <= finish_x) && (c >= middle_y && c <= finish_y)
			answer += quarter * 3;
			start_x = middle_x;
			start_y = middle_y;
		}
	}

	cout << answer << '\n';

	return 0;
}