#include <iostream>
#include <memory>

using namespace std;
constinit const int SIZE = 1'000'010;

class Stack {
public:
	int* container;
	int index{};

	Stack() : index(0) {
		container = new int[SIZE];
	}

	void push(int X) {
		container[index++] = X;
	}

	int pop() {
		if (empty()) return -1;
		int ret = container[index - 1];
		index--;
		return ret;
	}

	int size() {
		return index;
	}

	bool empty() {
		if (index == 0) return true;
		else return false;
	}

	int top() {
		if (empty()) return -1;
		else return container[index - 1];
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	//unique_ptr<Stack> S = make_unique<Stack>(new Stack());
	unique_ptr<Stack> S = unique_ptr<Stack>(new Stack());

	for (int n{}; n < N; ++n) {
		int op{}; cin >> op;
		if (op == 1) { // push
			int X{}; cin >> X;
			S->push(X);
		}
		else if (op == 2) { // pop
			cout << S->pop() << '\n';
		}
		else if (op == 3) { // size
			cout << S->size() << '\n';
		}
		else if (op == 4) { // empty
			cout << S->empty() << '\n';
		}
		else if (op == 5) { // top
			cout << S->top() << '\n';
		}
	}

	return 0;
}