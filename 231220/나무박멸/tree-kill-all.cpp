#include<iostream>
using namespace std;

#define MAX_N 21
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

struct Node {
	int y;
	int x;
};

int DAT[4][2] = {
	-1,0,
	0,1,
	0,-1,
	1,0
};

int DXT[4][2] = {
	-1,1,
	1,1,
	1,-1,
	-1,-1
};

int n, m, k, c;
int map[MAX_N][MAX_N];		//map
int step[MAX_N][MAX_N];		//성장치 기록
Node toKill;				//제초제 뿌릴 위치
int totalCnt = 0;			//총 박멸 수

void CLEAR() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			step[y][x] = 0;
		}
	}
	return;
}

void GROW() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			
			if (map[y][x] == 0) continue;
			else if (map[y][x] < -1) map[y][x] += 2;
			else if (map[y][x] > 0) {
				int tmpcnt = 0;
				for (int i = 0; i < 4; i++) {
					int ny = y + DAT[i][0];
					int nx = x + DAT[i][1];

					if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
					if (map[ny][nx] <= 0) continue;
					tmpcnt++;
				}
				map[y][x] += tmpcnt;
			}
		}
	}

	return;
}

void MOVE() {
	CLEAR();		//초기화

	// 성장치 기록
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (map[y][x] <= 0) continue;	//나무가 없으면 cont
			
			//주변의 빈칸 확인
			int tmpcnt = 0;
			for (int i = 0; i < 4; i++) {
				int ny = y + DAT[i][0];
				int nx = x + DAT[i][1];

				if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
				if (map[ny][nx] != 0) continue;

				tmpcnt++;
			}

			// 주변에 빈칸이 없으면 cont
			if (tmpcnt == 0) continue;

			// grow만큼 번식
			int grow = map[y][x] / tmpcnt;
			for (int i = 0; i < 4; i++) {
				int ny = y + DAT[i][0];
				int nx = x + DAT[i][1];

				if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
				if (map[ny][nx] != 0) continue;

				step[ny][nx] += grow;
			}
		}
	}

	// map에 기록
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			map[y][x] += step[y][x];
		}
	}

	return;
}

void PICK() {
	//초기화
	toKill.y = -1;
	toKill.x = -1;
	
	int maxi = -1;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (map[y][x] <= 0) continue;
			
			int tmpcnt = map[y][x];
			for (int i = 0; i < 4; i++) {
				for (int t = 1; t <= k; t++) {
					int ny = y + DXT[i][0] * t;
					int nx = x + DXT[i][1] * t;

					if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
					if (map[ny][nx] <= 0) break;
					tmpcnt += map[ny][nx];
				}
			}
			if (maxi < tmpcnt) {
				maxi = tmpcnt;
				toKill.y = y;
				toKill.x = x;
			}
		}
	}
	return;
}

void DEAD() {
	PICK();
	if (toKill.y == -1 && toKill.x == -1) return;

	for (int i = 0; i < 4; i++) {
		for (int t = 1; t <= k; t++) {
			int ny = toKill.y + DXT[i][0] * t;
			int nx = toKill.x + DXT[i][1] * t;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (map[ny][nx] == -1) break;
			if (map[ny][nx] == 0 || map[ny][nx] < -1) {
				map[ny][nx] = -2 * (c + 1);
				break;		//현재 칸까지 뿌리기
			}
			totalCnt += map[ny][nx];
			map[ny][nx] = -2 * (c + 1);
		}
	}
	totalCnt += map[toKill.y][toKill.x];
	map[toKill.y][toKill.x] = -2 * (c + 1);

	return;
}

int main() {
	cin >> n >> m >> k >> c;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
		}
	}

	for (int t = 0; t < m; t++) {
		GROW();
		MOVE();
		DEAD();
	}

	cout << totalCnt;

	return 0;
}