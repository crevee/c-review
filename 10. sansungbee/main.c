#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mtg.h"

#define MY_KEY_F4 62
#define MY_KEY_ENTER 13
#define MY_KEY_BACKSPACE 8

#define MY_MAX_X 50
#define MY_MAX_Y 20
#define MY_MAX_WORD 100
#define MY_MAX_LEN 15

typedef struct
{
	char word[MY_MAX_LEN];

	int x, y, index;
}S_WORD;

int g_max_words_size = 0;
char g_words[MY_MAX_WORD][MY_MAX_LEN];

S_WORD g_word;
S_WORD g_key;

int g_play = 0, g_score = 0, g_life = 4;

int LoadWords(void);
int GetNextWord(void);

void ShowHelp(void);
void ShowScore(void);
void ShowInput(void);
void ShowWord(void);
void RunTimer(void);

int CheckGameOver(void);


int GetNextWord(void) {
	if (g_max_words_size <= g_word.index) {
		g_word.index = 0;
	}
	else {
		g_word.x = rand() % MY_MAX_X;
		g_word.y = 1;
	}
	strcpy(g_word.word, g_words[g_word.index]);
	g_word.index++;

	return 0;
}

int LoadWords(void) {
	int index;
	char temp[80];
	FILE* fp;
	char* token;

	fp = fopen("words.txt", "r");

	if (fp == NULL) {
		return -1;
	}

	index = 0;

	while (1) {
		if (fgets(temp, sizeof(temp), fp) == NULL) {
			break;
		}
		token = strtok(temp, ",\n");

		while (1) {
			strcpy(g_words[index], token);
			index++;

			token = strtok(NULL, ",\n");

			if (token == NULL) {
				break;

			}
		}
	}
	g_max_words_size = index;
	
	fclose(fp);

	return 0;
}

void ShowScore(void) {
	char temp[20];

	sprintf(temp, "score: %d", g_score);
	_DrawText(0, 0, temp);
}

void ShowHelp(void) {
	_DrawText(MY_MAX_X + 10, 10, "Game ver 0.0.1");
	_DrawText(MY_MAX_X + 10, 11, "F4 : exit");
	_DrawTextColor(MY_MAX_X + 10, 13, "Life", 12);

	for (int i = 0; i < g_life; i++) {
		_DrawTextColor(MY_MAX_X + 15 + i, 13, "O", 12);
	}

	if (g_life == 0) {
		_DrawText(MY_MAX_X / 2 - 5, MY_MAX_Y / 2, "Game Over!");
		_DrawText(MY_MAX_X / 2 - 7, MY_MAX_Y / 2 + 2, "Press any key");
		g_play = -1;
	}
}

void ShowWord(void) {
	_DrawText(g_word.x, g_word.y, g_word.word);
}

void ShowInput(void) {
	_DrawText(g_key.x, g_key.y, g_key.word);
}

void Draw(void) {
	ShowHelp();
	ShowWord();
	ShowInput();
	ShowScore();
}

void RunInit(void) {
	if (LoadWords() == -1) {
		_MessageBox(0, 0, 30, 20, "File Load Error");
	}

	g_word.index = 0;
	GetNextWord();

	g_key.x = 10;
	g_key.y = MY_MAX_Y + 1;
	g_key.word[0] = '\n';

	_Invalidate();
}

int RunKey(void) {
	char k;

	k = _GetKey();

	if (k == -1) {
		return 0;
	}
	if (k == 'q' || MY_KEY_F4 == k) {
		return -1;
	}
	if (k == MY_KEY_ENTER) {
		if (strcmp(g_key.word, g_word.word) == 0) {
			g_score = g_score + 100;

			if (GetNextWord() == -1) {
				g_play = -1;
				return 0;
			}
		}
		else {
			g_life--;
		}
		g_key.index = 0;
		g_key.word[g_key.index] = '\0';
	}
	else if (k == MY_KEY_BACKSPACE) {
		g_key.index--;

		if (g_key.index < 0) {
			g_key.index = 0;
		}
		g_key.word[g_key.index] = '\0';
	}
	else {
		g_key.word[g_key.index++] = k;
		g_key.word[g_key.index] = '\0';
	}
	_Invalidate();

	return 0;
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

void RunTimer(void) {
	static long old_time = 0;
	long new_time;

	if (g_play == -1) {
		return;
	}

	new_time = _GetTickCount();

	if (abs(new_time - old_time) < 1000) {
		return;
	}
	else {
		old_time = new_time;
	}

	if (MY_MAX_Y < (g_word.y + 1)) {
		if (GetNextWord() == -1) {
			g_play = -1;
		}
		g_life--;
	}
	else {
		g_word.y++;
	}
	_Invalidate();
}

int CheckGameOver(void) {
	if (g_play == -1) {
		_Invalidate();
		_MessageBox(0, 0, MY_MAX_X, MY_MAX_Y, " ");

		return -1;
	}
	return 0;
}

void GameMain(void) {
	RunGameTitle();

	RunInit();

	while (1) {
		RunTimer();

		if (CheckGameOver() == -1) {
			break;
		}
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
