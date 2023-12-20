//1:21

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MAX_N 16
#define MAX_M 31
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

struct Node {
	int y = -1;
	int x = -1;
	int state = -1;
};

int DAT[4][2] = {
	-1,0,
	0,-1,
	0,1,
	1,0
};

int n, m;
int map[MAX_N][MAX_N];
int step[MAX_N][MAX_N];
Node ppl[MAX_M];
Node market[MAX_M];
int cnt = 0;

bool isFinished() {
	for (int i = 0; i < m; i++) {
		if (ppl[i].state != 1) return false;
	}
	return true;
}

void CLEAR() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			step[y][x] = 999;
		}
	}
	return;
}

void BFS(int index) {
	CLEAR();
	Node start = market[index];
	step[start.y][start.x] = 0;
	queue<Node> q;
	q.push(start);

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + DAT[i][0];
			int nx = now.x + DAT[i][1];
			if (ny < 0 || ny >= n || nx < 0 || nx >= n || map[ny][nx] == -1) continue;
			if (step[ny][nx] != 999) continue;
			Node next;
			next.y = ny;
			next.x = nx;
			step[ny][nx] = step[now.y][now.x] + 1;
			q.push(next);
		}
	}
	return;
}

void MOVE() {
	for (int t = 0; t < m; t++) {
		if (ppl[t].state != 0) continue;

		BFS(t);
		int mini = 999;
		int miniY = -1;
		int miniX = -1;
		for (int i = 0; i < 4; i++) {
			int ny = ppl[t].y + DAT[i][0];
			int nx = ppl[t].x + DAT[i][1];
			if (ny < 0 || ny >= n || nx < 0 || nx >= n || map[ny][nx] == -1) continue;
			if (step[ny][nx] < mini) {
				mini = step[ny][nx];
				miniY = ny;
				miniX = nx;
			}
		}
		ppl[t].y = miniY;
		ppl[t].x = miniX;
	}

	for (int i = 0; i < m; i++) {
		if (ppl[i].state != 0) continue;
		if (ppl[i].y == market[i].y && ppl[i].x == market[i].x) {
			ppl[i].state = 1;
			map[ppl[i].y][ppl[i].x] = -1;
		}
	}
	return;
}

void PICK() {
	if (cnt >= m) return;
	BFS(cnt);

	int mini = 999;
	int miniY = -1;
	int miniX = -1;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (map[y][x] == 1 && step[y][x] < mini) {
				mini = step[y][x];
				miniY = y;
				miniX = x;
			}
		}
	}
	ppl[cnt].y = miniY;
	ppl[cnt].x = miniX;
	ppl[cnt].state = 0;
	if (miniY == -1 || miniX == -1) { cout << "Error\n"; return; }
	map[miniY][miniX] = -1;

	return;
}


int main() {
	fastio

	//input
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
		}
	}
	for (int i = 0; i < m; i++) {
		cin >> market[i].y >> market[i].x;
		market[i].y--; market[i].x--;
	}

	while (!isFinished()) {
		MOVE();
		PICK();
		cnt++;
	}

	cout << cnt;

	return 0;
}