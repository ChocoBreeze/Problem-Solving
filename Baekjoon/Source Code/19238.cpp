// 최단경로로만 이동.
// 현재 위치에서 최단거리가 가장 짧은 승객을 고름.
// 그런 승객이 여러 명이면 그 중 행 번호가 가장 작은 승객을,
// 그런 승객도 여러 명이면 그 중 열 번호가 가장 작은 승객을 고름.
// 같은 칸이면 연료 = 0
// 한 칸 이동할 때마다 연료 1 소모
// 목적지로 성공적으로 이동시키면 소모한 연료의 2배를 충전

// 매 턴 flood fill

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 상좌우하
int dx[]{ -1,0,0,1 };
int dy[]{ 0,-1,1,0 };
int N, M, fuel; // 칸 크기, 승객 수, 연료 양

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
	bool operator<(const coord& other) const { // pq는 반대로
		if (this->x == other.x) return this->y > other.y;
		return this->x > other.x;
	}
};

struct Info {
	coord customer;
	coord goal;
	Info(coord c, coord g) : customer(c), goal(g) {}
};

coord taxi(0,0);

int findCloseCustomer(vector<vector<int>>& Map, vector<int>& customerVisited) {
	priority_queue<coord> pq;
	pq.push(taxi);

	int usefuels{};
	vector<vector<int>> visited(N, vector<int>(N, 0));
	while (!pq.empty()) {
		// int cursize{ pq.size() }; 
		// pq.size()가 unsigned __int64구나
		int cursize = static_cast<int>(pq.size());
		priority_queue<coord> tempPQ;
		for (int si{}; si < cursize; ++si) {
			coord now = pq.top();
			pq.pop();

			if (Map[now.x][now.y] > 1 && !customerVisited[Map[now.x][now.y] - 2]) {
				customerVisited[Map[now.x][now.y] - 2] = 1;
				taxi = now;
				fuel -= usefuels;
				return Map[now.x][now.y] - 2; // 승객 인덱스
			}

			for (int di = 0; di < 4; ++di) {
				int nx = now.x + dx[di];
				int ny = now.y + dy[di];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (visited[nx][ny]) continue;
				if (Map[nx][ny] == 1) continue;
				visited[nx][ny] = 1;
				// pq.push(coord(nx, ny));
				tempPQ.push(coord(nx, ny));
			}
		}
		usefuels++;
		if (usefuels > fuel) { // 넘 멀어
			return -1;
		}
		pq = move(tempPQ);
	}
	return -1; // 도달 x
}

bool possibleToReach(vector<vector<int>>& Map, Info& info) {
	priority_queue<coord> pq;
	pq.push(taxi);

	int usefuels{};
	vector<vector<int>> visited(N, vector<int>(N, 0));
	while (!pq.empty()) {
		// int cursize{ pq.size() };
		int cursize = static_cast<int>(pq.size());
		priority_queue<coord> tempPQ;
		for (int si{}; si < cursize; ++si) {
			coord now = pq.top();
			pq.pop();

			if (now.x == info.goal.x && now.y == info.goal.y) {
				taxi = now;
				fuel += usefuels;
				return true;
			}

			for (int di = 0; di < 4; ++di) {
				int nx = now.x + dx[di];
				int ny = now.y + dy[di];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (visited[nx][ny]) continue;
				if (Map[nx][ny] == 1) continue;
				visited[nx][ny] = 1;
				// pq.push(coord(nx, ny));
				tempPQ.push(coord(nx, ny));
			}
		}
		usefuels++;
		if (usefuels > fuel) { // 넘 멀어
			return false;
		}
		pq = move(tempPQ);
	}
	return false; // 도달 x
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	
	cin >> N >> M >> fuel;

	vector<vector<int>> Map(N, vector<int>(N, 0));

	for (auto& row : Map) {
		for (int& m : row) {
			cin >> m;
		}
	}
	cin >> taxi.x >> taxi.y;
	taxi.x--; taxi.y--;

	vector<Info> infos(M, Info(coord(0, 0), coord(0, 0)));
	vector<int> customerVisited(M, 0);
	for (int m{}; m < M; ++m) {
		cin >> infos[m].customer.x >> infos[m].customer.y >>
			infos[m].goal.x >> infos[m].goal.y;
		infos[m].customer.x--; infos[m].customer.y--;
		infos[m].goal.x--; infos[m].goal.y--;
		Map[infos[m].customer.x][infos[m].customer.y] = 2 + m; // 승객 번호 2부터 시작
	}

	int count{}; // 태운 승객 수
	while (1) {
		if (count == M) break; // 모든 승객 도착

		// flood fill - 가장 가까운 승객 찾기
		// 현재 연료로 도달 가능한가?
		int nextCustomerIndex = findCloseCustomer(Map, customerVisited);
		if (nextCustomerIndex == -1) {
			fuel = -1;
			break;
		}

		// flood fill - 승객이 원하는 지점까지 가기
		// 현재 연료로 도달 가능한가?
		if (!possibleToReach(Map, infos[nextCustomerIndex])) {
			fuel = -1;
			break;
		}
		++count;
	}
	cout << fuel << '\n';

	return 0;
}