#include <stdio.h>
#include <stdlib.h>

#include "mtg.h"

#define MAX_STAGE 4
#define MAX_X 35
#define MAX_Y 6

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 80
#define KEY_DOWN 72

int g_map_index = 0;
int g_x, g_y;

char g_play[MAX_Y][MAX_X];
char g_map[MAX_STAGE][MAX_Y][MAX_X] = {
{
	"==============================",
	"==                          ==",
	"==    @     o          =======",
	"==    o  ===               .==",
	"==                         .==",
	"==============================",
},
{
	"==============================",
	"==     =                    ==",
	"==    @==== o    o          ==",
	"==        =     ====        ==",
	"==                ..        ==",
	"==============================",
},
{
	"==============================",
	"==                          ==",
	"==   @     o     =======    ==",
	"==      o          ..       ==",
	"==============================",
},
{
	"==============================",
	"==                        . ==",
	"==   @ ====  .  o =======   ==",
	"==   o                      ==",
	"==============================",
}
};

void GetNextMap() {
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (g_map[g_map_index][y][x] == '@') {
				g_x = x;
				g_y = y;
				g_play[y][x] = ' ';
			}
			else {
				g_play[y][x] = g_map[g_map_index][y][x];
			}
		}
	}
}

void DrawMap(void) {
	for (int y = 0; y < MAX_Y; y++) {
		_DrawText(0, y, g_play[y]);
	}
}

void Draw(void) {
	DrawMap();
	_DrawText(g_x, g_y, "@");
	_DrawText(40, 10, "Game Ver 0.0.1");
}


void RunInit(void) {
	GetNextMap();

	_Invalidate();
}

int Move(int nx, int ny, int nx_plus_one, int ny_plus_one) {
	if (g_play[ny][nx] != '=') {
		if (g_play[ny][nx] == 'o') {
			if (g_play[ny_plus_one][nx_plus_one] == ' ' ||
				g_play[ny_plus_one][nx_plus_one] == '.') {
				
				g_play[ny_plus_one][nx_plus_one] = 'o';
				g_play[ny][nx] = ' ';

				g_x = nx;
				g_y = ny;

				return 0;
			}
		}
		else {
			g_x = nx;
			g_y = ny;
		}
	}
	return -1;
}

int GameOver(void) {
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (g_map[g_map_index][y][x] == '.' && g_play[y][x] != 'o') {
				return -1;
			}
		}
	}
	return 0;
}

int RunKey(void) {
	char k;
	int nx, ny;
	int nx_plus_one, ny_plus_one;

	k = _GetKey();

	if (k == -1) {
		return 0;
	}

	if (k == 'q') {
		return -1;
	}
	else {

	}

	nx = g_x;
	ny = g_y;
	nx_plus_one = nx;
	ny_plus_one = ny;

	if (k == KEY_LEFT) {
		nx = g_x - 1;
		nx_plus_one = nx - 1;
	}
	else if (k == KEY_RIGHT) {
		nx = g_x + 1;
		nx_plus_one = nx + 1;
	}
	else if (k == KEY_UP) {
		ny = g_y + 1;
		ny_plus_one = ny + 1;
	}
	else if (k == KEY_DOWN) {
		ny = g_y - 1;
		ny_plus_one = ny - 1;
	}

	if (Move(nx, ny, nx_plus_one, ny_plus_one) == 0) {
		if (GameOver() == 0) {
			_Invalidate();

			if (g_map_index + 1 == MAX_STAGE) {
				_MessageBox(20, 5, 40, 5, "Game Over!");
			}
			else{
				g_map_index++;
				GetNextMap();
			}
		}
	}
	_Invalidate();

	return 0;
}

void GameMain(void) {
	RunInit();

	while (1) {
		if (RunKey() == -1) {
			break;
		}
	}
}

int main(void) {
	_BeginWindow();

	GameMain();

	_EndWindow();

	return 0;
}
