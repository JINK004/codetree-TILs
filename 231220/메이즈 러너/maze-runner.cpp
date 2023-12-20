#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define MAX_N 10

struct Node {
	int y;
	int x;
	int state;	// 0:이동중, 1:이동완료
};

// U D R L
int DAT[4][2] = {
	-1,0,
	1,0,
	0,1,
	0,-1
};

int n, m, k;
int map[MAX_N][MAX_N];	//map
vector<Node> ppl;		//참가자
Node END;				//출구
int cnt = 0;			//이동 거리 합
int path[MAX_N];		//정사각형 범위에 포함되는 참가자

// 참가자가 모두 탈출했는지 확인
bool isFinished() {
	for (int i = 0; i < m; i++) {
		if (ppl[i].state == 0) return false;
	}
	return true;
}

// 1. 참가자 이동
void MOVE() {
	for (int t = 0; t < m; t++) {
		if (ppl[t].state == 1) continue;	//이미 도착했으면 cont

		Node now = ppl[t];
		int nowDis = abs(now.y - END.y) + abs(now.x - END.x);

		for (int i = 0; i < 4; i++) {
			int ny = now.y + DAT[i][0];
			int nx = now.x + DAT[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (map[ny][nx] != 0) continue;

			int nextDis = abs(ny - END.y) + abs(nx - END.x);
			if (nextDis >= nowDis) continue;

			ppl[t].y = ny;
			ppl[t].x = nx;
			cnt++;
			if (ny == END.y && nx == END.x) ppl[t].state = 1;
			break;
		}
	}

	return;
}

// 2. 맵 회전

// (dy,dx)를 시작점으로 하는 dydxNum 크기의 정사각형 안에
// 출구와 참가자가 한 명 이상 존재하는지 확인
bool CHECK(int dy, int dx, int dydxNum) {
	int flagEND = 0;
	int flagPPL = 0;

	for (int y = dy; y < dy + dydxNum; y++) {
		for (int x = dx; x < dx + dydxNum; x++) {
			if (y == END.y && x == END.x) flagEND = 1;

			for (int i = 0; i < m; i++) {
				if (ppl[i].state != 0) continue;
				if (y == ppl[i].y && x == ppl[i].x) flagPPL = 1;
				if (flagEND == 1 && flagPPL == 1) return true;
			}
			if (flagEND == 1 && flagPPL == 1) return true;
		}
	}
	if (flagEND == 1 && flagPPL == 1) return true;
	else return false;
}

void isInside(Node start, int num) {
	//초기화
	for (int i = 0; i < m; i++) {
		path[i] = 0;
	}

	for (int i = 0; i < m; i++) {
		if (ppl[i].state != 0) continue;
		for (int y = start.y; y < start.y + num; y++) {
			for (int x = start.x; x < start.x + num; x++) {
				if (y == ppl[i].y && x == ppl[i].x) {
					path[i] = 1;
					break;
				}
			}
			if (path[i] == 1) break;
		}
	}

	return;
}

void TURN() {
	Node start;					// 정사각형 시작점
	int dydxNum = -1;			// 정사각형 크기
	int turnMap[MAX_N][MAX_N];	// 회전한 미로 저장용 임시 map

	for (int i = 2; i <= 10; i++) {
		for (int y = 0; y <= n - i; y++) {
			for (int x = 0; x <= n - i; x++) {
				if (!CHECK(y, x, i)) continue;
				dydxNum = i;
				start.y = y;
				start.x = x;
				break;
			}
			if (dydxNum != -1) break;
		}
		if (dydxNum != -1) break;
	}

	if (dydxNum == -1) return;	//남은 참가자가 없다면 main으로 return

	for (int y = 0; y < dydxNum; y++) {
		for (int x = 0; x < dydxNum; x++) {
			turnMap[y][x] = map[start.y + dydxNum -1 - x][start.x + y];
		}
	}
	for (int y = 0; y < dydxNum; y++) {
		for (int x = 0; x < dydxNum; x++) {
			map[y + start.y][x + start.x] = turnMap[y][x];
			if (map[y + start.y][x + start.x] != 0) map[y + start.y][x + start.x]--;
		}
	}

	// 출구 회전
	int tmpY1 = END.y - start.y;
	int tmpX1 = END.x - start.x;

	int tmpY2 = tmpX1;
	int tmpX2 = dydxNum - 1 - tmpY1;

	END.y = tmpY2 + start.y;
	END.x = tmpX2 + start.x;


	// 참가자 회전
	isInside(start, dydxNum);
	for (int i = 0; i < m; i++) {
		if (path[i] == 0) continue;
		if (ppl[i].state == 1) continue;

		int tmpPY1 = ppl[i].y - start.y;
		int tmpPX1 = ppl[i].x - start.x;

		int tmpPY2 = tmpPX1;
		int tmpPX2 = dydxNum - 1 - tmpPY1;

		ppl[i].y = tmpPY2 + start.y;
		ppl[i].x = tmpPX2 + start.x;
	}

	return;
}


int main() {
	fastio;

	//input
	cin >> n >> m >> k;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
		}
	}
	for (int i = 0; i < m; i++) {
		Node tmp;
		cin >> tmp.y >> tmp.x;
		tmp.y--; tmp.x--;
		tmp.state = 0;
		ppl.push_back(tmp);
	}
	cin >> END.y >> END.x;
	END.y--; END.x--;

	for (int K = 0; K < k; K++) {
		MOVE();
		TURN();
		if (isFinished()) break;
	}

	cout << cnt << "\n";
	cout << END.y + 1 << " " << END.x + 1;
	return 0;
}