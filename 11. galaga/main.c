#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "mtg.h"

#define MY_KEY_F4		62
#define MY_KEY_LEFT		75
#define MY_KEY_RIGHT	77
#define MY_KEY_GUN		32

#define ENEMY_COUNT		4
#define ENEMY_TYPE_COUNT	4

#define MAX_BULLET_COUNT	50
#define MAX_BOMB_COUNT		50

#define PLAYER_Y_POS		24

struct S_OBJECT
{
	int x, y, life, type, dir;
};

int g_game = 0, g_enemy_count = 4;

struct S_OBJECT g_Enemy[ENEMY_COUNT];
struct S_OBJECT g_player;

struct S_OBJECT g_bullet[MAX_BULLET_COUNT];
struct S_OBJECT g_bomb[MAX_BOMB_COUNT];

char* g_Enemy_type[] = { "O-v-O", "OoloO", "IIoII", "vOOOv" };

void ShowHelp(void);
void ShowPlayer(void);
void ShowEnemy(void);
void InitEnemy(void);
void InitPlayer(void);
void MovePlayer(char k);
void MoveEnemy(void);

void InitBullet(void);
void ShowBullet(void);
void Fire(char k);
void RunBulletTimer(void);
void MoveBullet(void);

void CheckBulletCollision(void);

void InitBomb(void);
void ShowBomb(void);
void DownBomb(int x, int y);
void MoveBomb(void);
void RunBombTimer(void);

void CheckBombCollision(void);

int CheckGameOver(void);

void ShowHelp(void) {
	_DrawText(60, 20, "Galaga ver 0.1");
	_DrawText(60, 22, "F4 : Exit");
}

void ShowPlayer(void) {
	char temp[80];

	_DrawText(g_player.x, g_player.y, "wwTww");
	sprintf(temp, "Life : %d", g_player.life);
	_DrawText(0, 0, temp);
}

void ShowEnemy(void) {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (g_Enemy[i].life <= 0) {
			continue;
		}
		_DrawText(g_Enemy[i].x, g_Enemy[i].y, g_Enemy_type[g_Enemy[i].type]);
	}
}

void ShowBullet(void) {
	for (int i = 0; i < MAX_BULLET_COUNT; i++) {
		if (g_bullet[i].life <= 0) {
			continue;
		}
		_DrawText(g_bullet[i].x, g_bullet[i].y, "@");
	}
}

void ShowBomb(void) {
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (g_bomb[i].life <= 0) {
			continue;
		}
		_DrawText(g_bomb[i].x, g_bomb[i].y, "*");
	}
}

void Draw(void) {
	ShowHelp();
	ShowPlayer();
	ShowEnemy();
	ShowBullet();
	ShowBomb();
}

void InitPlayer(void) {
	g_player.x = 40;
	g_player.y = 23;
	g_player.life = 3;
}

void InitEnemy(void) {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		g_Enemy[i].x = rand() % 55;
		g_Enemy[i].y = rand() % 5;
		g_Enemy[i].life = 10;
		g_Enemy[i].type = rand() % ENEMY_TYPE_COUNT;
		g_Enemy[i].dir = 1;
	}
}

void InitBullet(void) {
	for (int i = 0; i < MAX_BULLET_COUNT; i++) {
		g_bullet[i].life = 0;
	}
}

void InitBomb(void) {
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		g_bomb[i].life = 0;
		g_bomb[i].dir = 1;
	}
}

void RunInit(void) {
	srand(time(NULL));

	InitPlayer();
	InitEnemy();
	InitBullet();
	InitBomb();

	_Invalidate();
}

void MovePlayer(char k) {
	switch (k) {
	case MY_KEY_LEFT:
		g_player.x = g_player.x - 1;

		if (g_player.x < 0) {
			g_player.x = 0;
		}
		break;
	case MY_KEY_RIGHT:
		g_player.x = g_player.x + 1;

		if (g_player.x > 53) {
			g_player.x = 53;
		}
		break;
	default:
		break;
	}
}

void Fire(char k) {
	if (MY_KEY_GUN == k) {
		for (int i = 0; i < MAX_BULLET_COUNT; i++) {
			if (g_bullet[i].life > 0) {
				continue;
			}
			g_bullet[i].x = g_player.x + 2;
			g_bullet[i].y = g_player.y - 1;
			g_bullet[i].life = 23;
			break;
		}
	}
}

int RunKey(void) {
	char k;

	k = _GetKey();

	if (k == -1) {
		return 0;
	}
	if (k == 'q' || k == MY_KEY_F4) {
		return -1;
	}

	MovePlayer(k);
	Fire(k);

	_Invalidate();

	return 0;
}

void DownBomb(int x, int y) {
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (g_bomb[i].life <= 0) {
			g_bomb[i].life = 1;
			g_bomb[i].x = x;
			g_bomb[i].y = y;
			break;
		}
	}
}

void MoveEnemy(void) {
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (g_Enemy[i].life <= 0) {
			continue;
		}
		g_Enemy[i].y = g_Enemy[i].y + g_Enemy[i].dir;

		if (0 >= g_Enemy[i].y || g_Enemy[i].y >= 15) {
			g_Enemy[i].dir = g_Enemy[i].dir * -1;
		}

		if (g_Enemy[i].y <= 15 && g_Enemy[i].y >= 5) {
			DownBomb(g_Enemy[i].x + 2, g_Enemy[i].y);
		}
	}
}

void RunEnemyTimer(void) {
	static long old_enemy_time = 0;
	long new_enemy_time;

	new_enemy_time = _GetTickCount();

	if (abs(new_enemy_time - old_enemy_time) < 1000) {
		return;
	}
	else {
		old_enemy_time = new_enemy_time;
	}
	MoveEnemy();

	_Invalidate();
}

void Title(void) {
	int dx = 50, dy = 20, sx = 0, sy = 0, x, y;

	while (1) {
		y = sy;

		for (x = sx; x < dx; x++) {
			_DrawTextOrg(x, y, "*");
			_Delay(10);
		}

		for (y = sy; y < dy; y++) {
			_DrawTextOrg(x, y, "*");
			_Delay(10);
		}

		for (x = x; sx <= x; x--) {
			_DrawTextOrg(x, y, "*");
			_Delay(10);
		}

		x = sx;

		for (y = y; sy <= y; y--) {
			_DrawTextOrg(x, y, "*");
			_Delay(10);
		}
		sx++, sy++;
		dx--, dy--;

		if (sy == dy) {
			break;
		}
		_DrawTextColorOrg(10, 10, " ", 10);
		_DrawTextColorOrg(11, 10, "G", 10);
		_DrawTextColorOrg(12, 10, "A", 10);
		_DrawTextColorOrg(13, 10, "M", 10);
		_DrawTextColorOrg(14, 10, "E", 10);
		_DrawTextColorOrg(15, 10, " ", 10);
		_DrawTextColorOrg(16, 10, "P", 10);
		_DrawTextColorOrg(17, 10, "l", 10);
		_DrawTextColorOrg(18, 10, "a", 10);
		_DrawTextColorOrg(19, 10, "y", 10);
		_DrawTextColorOrg(20, 10, " ", 10);
		_DrawTextColorOrg(21, 10, "C", 10);
		_DrawTextColorOrg(22, 10, "o", 10);
		_DrawTextColorOrg(23, 10, "p", 10);
		_DrawTextColorOrg(24, 10, "y", 10);
		_DrawTextColorOrg(25, 10, "r", 10);
		_DrawTextColorOrg(26, 10, "i", 10);
		_DrawTextColorOrg(27, 10, "g", 10);
		_DrawTextColorOrg(28, 10, "h", 10);
		_DrawTextColorOrg(29, 10, "t", 10);
		_DrawTextColorOrg(30, 10, "<", 10);
		_DrawTextColorOrg(31, 10, "R", 10);
		_DrawTextColorOrg(32, 10, ">", 10);
		_DrawTextColorOrg(33, 10, " ", 10);
		_DrawTextColorOrg(34, 10, "2", 10);
		_DrawTextColorOrg(35, 10, "0", 10);
		_DrawTextColorOrg(36, 10, "2", 10);
		_DrawTextColorOrg(37, 10, "3", 10);

		_Delay(100 * 3);
	}
}

void RunGameTitle(void) {
	Title();
}

void CheckBulletCollision(void) {
	for (int i = 0; i < MAX_BULLET_COUNT; i++) {
		if (g_bullet[i].life <= 0) {
			continue;
		}
		for (int j = 0; j < ENEMY_COUNT; j++) {
			if (g_Enemy[j].life <= 0) {
				continue;
			}
			if (g_Enemy[j].y == g_bullet[i].y) {
				if (g_Enemy[j].x <= g_bullet[i].x &&
					g_Enemy[j].x + 4 >= g_bullet[i].x) {
					g_bullet[i].life = 0;
					g_Enemy[j].life--;
					if (g_Enemy[j].life == 0) {
						g_enemy_count--;
					}
					break;
				}
			}
		}
	}
}

void MoveBullet(void) {
	for (int i = 0; i < MAX_BULLET_COUNT; i++) {
		if (g_bullet[i].life <= 0) {
			continue;
		}
		g_bullet[i].life = g_bullet[i].life - 1;
		g_bullet[i].y = g_bullet[i].y - 1;
	}
}

void RunBulletTimer(void) {
	static long old_bullet_time = 0;
	long new_bullet_time;

	new_bullet_time = _GetTickCount();

	if (abs(new_bullet_time - old_bullet_time) < 50) {
		return;
	}
	else {
		old_bullet_time = new_bullet_time;
	}
	MoveBullet();
	CheckBulletCollision();

	_Invalidate();
}

void MoveBomb(void) {
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (g_bomb[i].life <= 0) {
			continue;
		}
		g_bomb[i].y++;

		if (g_player.y < g_bomb[i].y) {
			g_bomb[i].life = 0;
		}
	}
}

int CheckGameOver(void) {
	if (g_player.life <= 0) {
		_MessageBox(0, 0, 55, 20, "GAME OVER");
		_Invalidate();
		return -1;
	}

	if (g_enemy_count == 0) {
		_MessageBox(0, 0, 55, 20, "GAME END");
		_Invalidate();
		return -1;
	}
	return 0;
}

void CheckBombCollision(void) {
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (g_bomb[i].life <= 0) {
			continue;
		}

		if (g_bomb[i].y == g_player.y &&
			g_player.x <= g_bomb[i].x && g_bomb[i].x <= g_player.x + 2) {
			g_player.life--;
			g_bomb[i].life = 0;
		}
	}
}

void RunBombTimer(void) {
	static long old_bomb_time = 0;
	long new_bomb_time;

	new_bomb_time = _GetTickCount();

	if (abs(new_bomb_time - old_bomb_time) < 100) {
		return;
	}
	else {
		old_bomb_time = new_bomb_time;
	}
	MoveBomb();
	CheckBombCollision();

	_Invalidate();
}

void GameMain(void) {
	RunGameTitle();

	RunInit();

	while (1) {
		RunEnemyTimer();
		RunBulletTimer();
		RunBombTimer();

		if (RunKey() == -1) {
			break;
		}

		if (CheckGameOver()) {
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
