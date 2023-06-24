#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char g_dic[10][20] = {
    "alphabet",
    "blue",
    "red",
    "home",
    "ground",
    "game",
    "money",
    "google",
    "korea",
    "japan"
};

int g_step = 0;

void InitGame(char* com, char* player) {
    srand(time(NULL));

    int index = rand() % 10, i;

    strcpy(com, g_dic[index]);

    int len = strlen(com);

    for (i = 0; i < len; i++) {
        player[i] = '*';
    }
    player[i] = '\0';
}

int InputChar(char com[20], char player[20]) {
    char temp[5], key;
    int len, check = 0;

    printf("Hint : %s \n", player);
    printf("input char : ");
    scanf("%s", temp);
    key = temp[0];

    len = strlen(player);

    for (int i = 0; i < len; i++) {
        if (com[i] == key && player[i] == '*') {
            player[i] = key;
            check = 1;
        }
    }
    return check;
}

void GoNextStep(void) {
    g_step++;
    printf("hang man step:%d \n", g_step);
}

void ShowHangman(void) {
    switch (g_step) {
    case 0:
        printf("     ┏━━━━━┓\n");
        printf("           ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");

        break;

    case 1:
        printf("     ┏━━━━━┓\n");
        printf("     ●    ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");

        break;

    case 2:
        printf("     ┏━━━━━┓\n");
        printf("     ●    ┃\n");
        printf("    ┏╉┓    ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");

        break;

    case 3:
        printf("     ┏━━━━━┓\n");
        printf("     ●    ┃\n");
        printf("    ┏╉┓    ┃\n");
        printf("     ┃     ┃\n");
        printf("           ┃\n");
        printf("           ┃\n");

        break;

    case 4:
        printf("     ┏━━━━━┓\n");
        printf("     ●    ┃\n");
        printf("    ┏╉┓    ┃\n");
        printf("     ┃     ┃\n");
        printf("    ┏┹┓    ┃\n");
        printf("           ┃\n");

        break;

    default:
        break;
    }
}

int CheckGameOver(char* com, char* player) {
    if (g_step == 4) {
        return 1;
    }
    if (strcmp(com, player) == 0) {
        return 1;
    }
    return 0;
}

int main(void) {
    char com[20];
    char player[20];

    InitGame(com, player);

    while (1) {
        if (InputChar(com, player) == 0) {
            GoNextStep();
            ShowHangman();
        }
        if (CheckGameOver(com, player) == 1) {
            break;
        }
    }
    return 0;
}
