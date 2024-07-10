#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
	string str;
	vector<Node*> childs;
	Node() = default;
	Node(string& str, vector<Node*>& vec) : str(str), childs(vec) {}
	~Node() = default;
};

void Print(Node* curr, int level) {
	for (int l{}; l < level; ++l) {
		cout << "--";
	}
	cout << curr->str << '\n';
	sort(curr->childs.begin(), curr->childs.end(), [](const Node* n1, const Node* n2) {
		return n1->str < n2->str; // string 사전 순 정렬
	});
	for (auto& nodeP : curr->childs) {
		Print(nodeP, level + 1);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	Node* root = new Node;
	for (int n{}; n < N; ++n) {
		int K{}; cin >> K;
		Node* p = root;
		for (int k{}; k < K; ++k) {
			string str; cin >> str;
			vector<Node*> emptyVec;
			Node* newNode = new Node(str, emptyVec);

			bool findNode{};
			for (auto& nodeP : p->childs) {
				if (nodeP->str == str) { // find
					findNode = true;
					p = nodeP;
					break;
				}
			}
			if (!findNode) { // insert
				p->childs.push_back(newNode);
				p = p->childs.back(); // 마지막에 넣은 위치로 이동.
			}
		}
	}

	// 예쁘게 출력
	Node* p = root;
	sort(p->childs.begin(), p->childs.end(), [](const Node* n1, const Node* n2) {
		return n1->str < n2->str; // string 사전 순 정렬
		});
	
	for (auto& nodeP : p->childs) {
		Print(nodeP, 0);
	}
	
	delete root;

	return 0;
}