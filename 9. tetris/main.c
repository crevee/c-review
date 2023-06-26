#include <stdio.h>
#include <stdlib.h>

#include "mtg.h"

#define MY_W 10 + 2
#define MY_H 20 + 2
#define MY_WALL 0
#define MY_BLANK 1
#define MY_BLOCK 2

#define MY_PATTERN_SIZE 3
#define MY_LEFT 75
#define MY_RIGHT 77
#define MY_UP 72
#define MY_DOWN 80
#define MY_SPACE 32

typedef struct {
	int x, y;
}S_POINT;

int g_data[MY_H][MY_W];

S_POINT g_type[MY_PATTERN_SIZE][4][4] = {
	{{0, 0, 1, 0, 2, 0, 3, 0}, {1, 0, 1, 1, 1, 2, 1, 3}, {0, 0, 1, 0, 2, 0, 3, 0}, {1, 0, 1, 1, 1, 2, 1, 3}},
	{{1, 1, 2, 1, 1, 2, 2, 2}, {1, 1, 2, 1, 1, 2, 2, 2}, {1, 1, 2, 1, 1, 2, 2, 2}, {1, 1, 2, 1, 1, 2, 2, 2}},
	{{0, 1, 0, 2, 1, 0, 1, 1}, {0, 1, 1, 1, 1, 2, 2, 2}, {1, 1, 1, 2, 2, 0, 2, 1}, {0, 0, 1, 0, 1, 1, 2, 1}},
};

int g_dir = 0, g_pattern_index = 0;
S_POINT g_pos = { 1, 1 };	//beginning block position

void DataInit(void);
void DrawData(void);
void DrawBlock(void);
void DrawHelp(void);

int CheckBlockMove(int dx, int dy, int dir);
int MoveBlockDown(void);

void CopyBlockToData(void);
void GetNewBlock(void);
void MoveToEnd(void);

void DownBlock(int y);
void CheckSameBlock(void);

void DrawHelp(void) {
	_DrawText(32, 10, "Tetries ver 0.0.1");
	_DrawText(32, 12, "Exit : q");
	_DrawText(32, 13, "Move : left, right");
	_DrawText(32, 14, "Rotation : up, down");
	_DrawText(32, 16, "NextBlock");
}

void DrawData(void) {

	int x, y;

	for (y = 0; y < MY_H; y++) {
		for (x = 0; x < MY_W; x++) {
			if (g_data[y][x] == MY_WALL) {
				_DrawText(x * 2, y, "@");
			}
			else if (g_data[y][x] == MY_BLANK) {
				_DrawText(x * 2, y, ".");
			}
			else {
				_DrawText(x * 2, y, "*");
			}
		}
	}
}

void DrawBlock(void) {

	int x, y;

	for (int i = 0; i < 4; i++) {
		x = g_pos.x + g_type[g_pattern_index][g_dir][i].x;
		y = g_pos.y + g_type[g_pattern_index][g_dir][i].y;

		_DrawText(x * 2, y, "*");

	}

	for (int i = 0; i < 4; i++) {
		x = g_type[g_pattern_index][g_dir][i].x;
		y = g_type[g_pattern_index][g_dir][i].y;

		_DrawText(32 + (x * 2), 18 + y, "*");
	}
}

void DataInit(void) {
	
	int x, y;

	for (y = 0; y < MY_H; y++) {
		for (x = 0; x < MY_W; x++) {
			if (x == 0 || y == 0 || MY_W == (x + 1) || MY_H == (y + 1)) {
				g_data[y][x] = MY_WALL;
			}
			else {
				g_data[y][x] = MY_BLANK;
			}
		}
	}
}

void CheckSameBlock(void) {
	int x, y;

	for (y = MY_H - 2; y > 0; y--) {
		int same = 0;

		for (x = 1; x < MY_W - 1; x++) {
			if (MY_BLOCK != g_data[y][x]) {
				same = -1;
				break;
			}
		}

		if (same == 0) {
			DownBlock(y);
			y++;
		}
	}
}

int CheckBlockMove(int dx, int dy, int dir) {
	
	for (int i = 0; i < 4; i++) {
		int x = dx + g_type[g_pattern_index][dir][i].x;
		int y = dy + g_type[g_pattern_index][dir][i].y;

		if (MY_BLANK != g_data[y][x]) {
			return -1;
		}
	}
	return 0;
}

int MoveBlockDown(void) {
	if (CheckBlockMove(g_pos.x, g_pos.y + 1, g_dir) == 0) {
		g_pos.y++;

		return 0;
	}
	return -1;
}

void CopyBlockToData(void) {

	for (int i = 0; i < 4; i++) {
		int x = g_pos.x + g_type[g_pattern_index][g_dir][i].x;
		int y = g_pos.y + g_type[g_pattern_index][g_dir][i].y;

		g_data[y][x] = MY_BLOCK;
	}
}

void GetNewBlock(void) {
	g_pos.x = 1 + rand() % (MY_W - 5);
	g_pos.y = 1;
	g_dir = rand() % 4;
	g_pattern_index = rand() % MY_PATTERN_SIZE;
}

void MoveToEnd(void) {
	while (1) {
		if (MoveBlockDown() == -1) {
			CopyBlockToData();
			CheckSameBlock();

			GetNewBlock();

			break;
		}
	}
}

void DownBlock(int y) {
	for (; y >= 1; y--) {
		for (int x = 1; x < MY_W - 1; x++) {
			if (y == 1) {
				g_data[y][x] = MY_BLANK;
			}
			else {
				g_data[y][x] = g_data[y - 1][x];
			}
		}
	}
}

void Draw(void) {
	DrawData();
	DrawBlock();
	DrawHelp();
}

void RunInit(void) {
	DataInit();
	_Invalidate();
}

int RunKey(void) {
	char k;

	k = _GetKey();

	if (k == -1) {
		return 0;
	}

	if (k == 'q') {
		return -1;
	}
	else {

	}

	if (k == MY_LEFT) {
		if (CheckBlockMove(g_pos.x - 1, g_pos.y, g_dir) == 0) {
			g_pos.x--;
		}
	}
	else if (k == MY_RIGHT) {
		if (CheckBlockMove(g_pos.x + 1, g_pos.y, g_dir) == 0) {
			g_pos.x++;
		}
	}
	else if (k == MY_SPACE) {
		MoveToEnd();
	}
	else if (k == MY_UP) {
		int dir = g_dir;

		dir++;

		if (dir > 3) {
			dir = 0;
		}
		if (CheckBlockMove(g_pos.x, g_pos.y, dir) == 0) {
			g_dir = dir;
			_Invalidate();
		}
	}
	else if (k == MY_DOWN) {
		int dir = g_dir;

		dir--;

		if (dir < 0) {
			dir = 3;
		}
		if (CheckBlockMove(g_pos.x, g_pos.y, dir) == 0) {
			g_dir = dir;
			_Invalidate();
		}
	}
	_Invalidate();

	return 0;
}

void RunTimer() {
	static long old_time = 0;
	long new_time;
	static int kill_timer = 0;

	if (kill_timer == -1) {
		return;
	}

	new_time = _GetTickCount();

	if (abs(new_time - old_time) < 100) {
		return;
	}
	else {
		old_time = new_time;
	}

	if (MoveBlockDown() == -1) {
		CopyBlockToData();
		CheckSameBlock();

		GetNewBlock();

		if (MoveBlockDown() == -1) {
			
			_Invalidate();
			
			kill_timer = -1;

			_MessageBox(40, 10, 20, 10, "Game Over");
		}
	}
	_Invalidate();
}

void GameMain(void) {
	RunInit();

	while (1) {
		RunTimer();

		if (RunKey() == -1) {
			break;
		}
	}
}

int main() {
	_BeginWindow();
	GameMain();
	_EndWindow();

	return 0;
}
