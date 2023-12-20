//2:16
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_N 21
#define MAX_M 31
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

struct Node {
	int y;
	int x;
	int dir;
	int state;
	int gun;
	int point;
};

int DAT[4][2] = {
	-1,0,
	0,1,
	1,0,
	0,-1
};

int n, m, k;
int map[MAX_N][MAX_N];					//이동
vector<Node> ppl;						//참가자
vector<int> gunList[MAX_N][MAX_N];		//무기

bool comp(int a, int b) {
	return a > b;
}

void changeGUN(int ny, int nx, int index) {
	int nowGun = ppl[index].gun;

	if (gunList[ny][nx].size() != 0) {
		if (gunList[ny][nx][0] > nowGun) {
			ppl[index].gun = gunList[ny][nx][0];
			gunList[ny][nx][0] = nowGun;
			sort(gunList[ny][nx].begin(), gunList[ny][nx].end(), comp);
		}
	}

	return;
}

void loserMOVE(int dy, int dx, int index) {
	Node now = ppl[index];	
	
	for (int i = 0; i < 4; i++) {
		int ny = dy + DAT[(now.dir + i) % 4][0];
		int nx = dx + DAT[(now.dir + i) % 4][1];
	
		if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
		if (map[ny][nx] != 0) continue;
		
		ppl[index].dir = (now.dir + i) % 4;
		ppl[index].y = ny;
		ppl[index].x = nx;
		map[ny][nx] = index + 1;
		changeGUN(ny, nx, index);
		break;
	}
	return;
}

void FIGHT(int ny, int nx, int index, int indexSec) {
	Node fir = ppl[index];
	Node sec = ppl[indexSec];

	int firScore = fir.state + fir.gun;
	int secScore = sec.state + sec.gun;

	int winner = -1;
	int loser = -1;
	int pp = 0;

	//승자 결정
	if (firScore > secScore) {
		winner = index;
		loser = indexSec;
		pp = firScore - secScore;
	}
	else if (secScore > firScore) {
		winner = indexSec;
		loser = index;
		pp = secScore - firScore;
	}
	else if (firScore == secScore) {
		if (fir.state >= sec.state) {
			winner = index;
			loser = indexSec;
		}
		else if (fir.state < sec.state) {
			winner = indexSec;
			loser = index;
		}
	}
	
	//패자처리
	if (ppl[loser].gun != 0) {
		gunList[ny][nx].push_back(ppl[loser].gun);
		sort(gunList[ny][nx].begin(), gunList[ny][nx].end(), comp);
	}
	ppl[loser].gun = 0;
	loserMOVE(ny, nx,loser);

	//승자처리
	ppl[winner].y = ny;
	ppl[winner].x = nx;
	ppl[winner].point += pp;
	map[ny][nx] = winner + 1;
	changeGUN(ny, nx, winner);

	return;
}

void MOVE() {
	for (int i = 0; i < m; i++) {
		Node now = ppl[i];
		map[now.y][now.x] = 0;			//이동 전 map 처리
		
		for (int j = 0; j < 2; j++) {
			int ny = now.y + DAT[(now.dir + (j * 2)) % 4][0];
			int nx = now.x + DAT[(now.dir + (j * 2)) % 4][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			// 이동 위치에 사람이 없다면
			if (map[ny][nx] == 0) {
				changeGUN(ny, nx, i);
				ppl[i].y = ny;
				ppl[i].x = nx;
				ppl[i].dir = (now.dir + (j * 2)) % 4;
				map[ny][nx] = i + 1;
				break;
			}

			else if (map[ny][nx] != 0) {
				int tmpN = map[ny][nx] - 1;
				ppl[i].dir = (now.dir + (j * 2)) % 4;
				map[ny][nx] = 0;
				FIGHT(ny, nx, i, tmpN);
				break;
			}
		}
	}
	return;
}


int main() {
	fastio;

	//input
	cin >> n >> m >> k;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			int tmpGun;
			cin >> tmpGun;
			if (tmpGun == 0) continue;
			gunList[y][x].push_back(tmpGun);
		}
	}
	for (int i = 0; i < m; i++) {
		Node tmpPPL;
		cin >> tmpPPL.y >> tmpPPL.x >> tmpPPL.dir >> tmpPPL.state;
		tmpPPL.y--; tmpPPL.x--;
		tmpPPL.gun = 0;
		tmpPPL.point = 0;
		ppl.push_back(tmpPPL);
		map[tmpPPL.y][tmpPPL.x] = i + 1;
	}

	for (int t = 0; t < k; t++) {
		MOVE();
	}
	
	//output
	for (int i = 0; i < m; i++) {
		cout << ppl[i].point << " ";
	}

	return 0;
}