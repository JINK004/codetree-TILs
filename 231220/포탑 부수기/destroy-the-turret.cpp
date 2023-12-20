#include<iostream>
#include<unordered_map>
#include<queue>
using namespace std;

#define MAX_N 11

struct Node {
	int y;
	int x;
	int state;	// -1:공격자 / 0:무관 / 1:공격대상 / 2:추가피해
};

int DAT[4][2] = {
	0,1,
	1,0,
	0,-1,
	-1,0
};

int DXT[4][2] = {
	1,1,
	-1,-1,
	1,-1,
	-1,1
};

int n, m, k;
int map[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];		// 공격 
int step[MAX_N][MAX_N];			// BFS 저장
unordered_map<int, int> seq;	// key-포탑 위치(y*n)+(x+1) / value - 최근 공격
Node pp[2];			// 공격자 및 공격 대상
int path[MAX_N][MAX_N];

bool isFinished() {
	int cnt = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] != 0) cnt++;
		}
	}
	if (cnt == 1) return true;
	return false;
}

void CLEAR() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			visited[y][x] = 0;
			step[y][x] = 0;
			path[y][x] = 0;
		}
	}
	return;
}

//공격자 선정
void PICK_FROM() {
	int mini = 5001;
	int miniY = -1;
	int miniX = -1;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] == 0) continue;
			if (mini > map[y][x]) {
				mini = map[y][x];
				miniY = y;
				miniX = x;
			}
			else if (mini == map[y][x]) {
				auto nowSeq = seq.find((y * n) + x + 1);
				auto miniSeq = seq.find((miniY * n) + miniX + 1);
				if (nowSeq->second > miniSeq->second) {
					miniY = y;
					miniX = x;
				}
				if (nowSeq->second == miniSeq->second) {
					if (y + x > miniY + miniX) {
						miniY = y;
						miniX = x;
					}
					else if (y + x == miniY + miniX) {
						if (x > miniX) {
							miniX = x;
						}
					}
				}
			}
		}
	}

	visited[miniY][miniX] = -1;
	map[miniY][miniX] += (n + m);
	pp[0].y = miniY;
	pp[0].x = miniX;
	pp[0].state = mini + n + m;

	return;
}

//공격 대상 선정
void PICK_TO() {
	int maxi = -1;
	int maxiY = -1;
	int maxiX = -1;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] == 0) continue;
			if (y == pp[0].y && x == pp[0].x) continue;
			if (maxi < map[y][x]) {
				maxi = map[y][x];
				maxiY = y;
				maxiX = x;
			}
			else if (maxi == map[y][x]) {
				auto nowSeq = seq.find((y * n) + x + 1);
				auto miniSeq = seq.find((maxiY * n) + maxiX + 1);
				if (nowSeq->second < miniSeq->second) {
					maxiY = y;
					maxiX = x;
				}
				if (nowSeq->second == miniSeq->second) {
					if (y + x < maxiY + maxiX) {
						maxiY = y;
						maxiX = x;
					}
					else if (y + x == maxiY + maxiX) {
						if (x < maxiX) {
							maxiX = x;
						}
					}
				}
			}
		}
	}
	visited[maxiY][maxiX] = 1;
	pp[1].y = maxiY;
	pp[1].x = maxiX;
	pp[1].state = maxi;

	return;
}

void BFS() {
	//공격 대상으로부터 시작
	queue<Node> q;
	q.push(pp[1]);
	step[pp[1].y][pp[1].x] = 0;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + DAT[i][0];
			int nx = now.x + DAT[i][1];

			if (ny >= n) ny -= n;
			if (ny < 0) ny += n;
			if (nx >= m) nx -= m;
			if (nx < 0) nx += m;
			if (map[ny][nx] == 0 || step[ny][nx] != 0) continue;
			if (ny == pp[1].y && nx == pp[1].x) continue;
			step[ny][nx] = step[now.y][now.x] + 1;
			Node next;
			next.y = ny;
			next.x = nx;
			next.state = step[ny][nx];
			q.push(next);
			if (ny == pp[0].y && nx == pp[0].x) break;
		}
	}
	step[pp[1].y][pp[1].x] = -1;
	return;
}

void MOVE() {
	queue<Node> q;
	q.push(pp[0]);

	int mini = 9999;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + DAT[i][0];
			int nx = now.x + DAT[i][1];

			if (ny >= n) ny -= n;
			if (ny < 0) ny += n;
			if (nx >= m) nx -= m;
			if (nx < 0) nx += m;
			if (map[ny][nx] == 0 || step[ny][nx] == 0) continue;
			if (step[ny][nx] >= mini) continue;

			Node next;
			next.y = ny;
			next.x = nx;
			mini = step[ny][nx];
			q.push(next);
			path[ny][nx] = 1;
			if (ny == pp[1].y && nx == pp[1].x) {
				path[pp[1].y][pp[1].x] = 0;
				break;
			}
		}
	}
	return;
}

//포탄공격
void ATTACK2() {
	map[pp[1].y][pp[1].x] -= map[pp[0].y][pp[0].x];
	for (int i = 0; i < 4; i++) {
		int ny = pp[1].y + DAT[i][0];
		int nx = pp[1].x + DAT[i][1];

		if (ny < 0) ny += n;
		else if (ny >= n) ny -= n;
		if (nx < 0) nx += m;
		else if (nx >= m) nx -= m;

		if (ny == pp[0].y && nx == pp[0].x) continue;
		map[ny][nx] -= (map[pp[0].y][pp[0].x] / 2);
		visited[ny][nx] = 1;
	}

	for (int i = 0; i < 4; i++) {
		int ny = pp[1].y + DXT[i][0];
		int nx = pp[1].x + DXT[i][1];

		if (ny < 0) ny += n;
		else if (ny >= n) ny -= n;
		if (nx < 0) nx += m;
		else if (nx >= m) nx -= m;

		if (ny == pp[0].y && nx == pp[0].x) continue;
		map[ny][nx] -= (map[pp[0].y][pp[0].x] / 2);
		visited[ny][nx] = 1;
	}
	return;
}

//레이저공격
void ATTACK1() {
	BFS();
	if (step[pp[0].y][pp[0].x] == 0) ATTACK2();
	else {
		MOVE();
		// 대미지
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++) {
				if (path[y][x] == 1) {
					visited[y][x] = 2;
					map[y][x] -= (pp[0].state / 2);
				}
			}
		}
		map[pp[1].y][pp[1].x] -= map[pp[0].y][pp[0].x];
	}
	return;
}

void DEAD() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] < 0) map[y][x] = 0;
		}
	}
	return;
}

void PLUS() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] != 0 && visited[y][x] == 0) map[y][x]++;
		}
	}
	return;
}

// 공격 순서 처리
void SEQ(int index) {
	int first = (pp[0].y * n) + (pp[0].x + 1);
	seq[first] = index + 1;
	return;
}

int main() {
	cin >> n >> m >> k;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> map[y][x];
			seq[(y * n) + x + 1] = 0;
			Node tmp;
		}
	}

	for (int i = 0; i < k; i++) {
		if (isFinished()) break;
		CLEAR();
		PICK_FROM();
		PICK_TO();
		ATTACK1();
		DEAD();
		PLUS();
		SEQ(i);
	}

	int ans = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (ans < map[y][x]) ans = map[y][x];
		}
	}
	cout << ans;

	return 0;
}