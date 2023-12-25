#include <iostream>
#include <cstring>

using namespace std;
constinit const int SIZE = 2'000'010;
constinit const int BEGIN = 999'999;

class Deque {
public:
	Deque() : frontIdx(BEGIN), backIdx(BEGIN + 1) {
		memset(arr, 0, sizeof(arr));
	}

	void push_front(int X) {
		arr[frontIdx--] = X;
	}
	void push_back(int X) {
		arr[backIdx++] = X;
	}
	int pop_front() {
		if (empty()) return -1;
		else return arr[++frontIdx];
	}
	int pop_back() {
		if (empty()) return -1;
		else return arr[--backIdx];
	}
	int size() {
		return backIdx - frontIdx - 1;
	}
	bool empty() {
		if (frontIdx + 1 == backIdx) return true;
		else return false;
	}
	int front() {
		if (empty()) return -1;
		else return arr[frontIdx + 1];
	}
	int back() {
		if (empty()) return -1;
		else return arr[backIdx - 1];
	}

private:
	int frontIdx, backIdx;
	int arr[SIZE];
};
Deque dq;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	for (int n{}; n < N; ++n) {
		int op{}; cin >> op;
		if (op == 1) { // push_front
			int X; cin >> X;
			dq.push_front(X);
		}
		else if (op == 2) { // push_back
			int X; cin >> X;
			dq.push_back(X);
		}
		else if (op == 3) { // pop_front
			cout << dq.pop_front() << '\n';
		}
		else if (op == 4) { // pop_back
			cout << dq.pop_back() << '\n';
		}
		else if (op == 5) { // size
			cout << dq.size() << '\n';
		}
		else if (op == 6) { // empty
			cout << dq.empty() << '\n';
		}
		else if (op == 7) { // front
			cout << dq.front() << '\n';
		}
		else if (op == 8) { // back
			cout << dq.back() << '\n';
		}
	}

	return 0;
}