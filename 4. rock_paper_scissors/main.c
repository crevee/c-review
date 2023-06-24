#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAME_END -1
#define PLAYER_SCISSORS 0
#define PLAYER_ROCK 1
#define PLAYER_PAPER 2

#define PLAYER_WIN 0
#define PLAYER_LOSE 1

void MyInit(int* count, int* win_count) {
    *count = 0;
    *win_count = 0;
    srand(time(NULL));
}

int ComPlay() {
    return rand() % 3;
}

int PlayerPlay() {
    int temp;

    printf("-1(Exit), 0(Scissors), 1(Rock), 2(Paper)?");
    scanf("%d", &temp);

    return temp;
}

int PlayerCheck(int com, int player) {
    if (PLAYER_SCISSORS == player && PLAYER_PAPER == com) {
        return PLAYER_WIN;
    }
    if (PLAYER_ROCK == player && PLAYER_SCISSORS == com) {
        return PLAYER_WIN;
    }
    if (PLAYER_PAPER == player && PLAYER_ROCK == com) {
        return PLAYER_WIN;
    }
    return PLAYER_LOSE;
}

void ShowRate(int count, int win_count) {
    float win_rate = 0;

    win_rate = (float)win_count / count;

    if (count == 0) {
        printf("0");
        return;
    }

    printf("Win Rate :  %.2f \n", win_rate);
}

int main() {

    int player, com, re, count = 0, win_count = 0;

    MyInit(&count, &win_count);

    while (1) {
        com = ComPlay();
        player = PlayerPlay();

        if (GAME_END == player) {
            break;
        }
        count++;
        re = PlayerCheck(com, player);

        if (PLAYER_WIN == re) {
            win_count++;
            printf("You Win! c:%d y:%d \n", com, player);
        }
        else {
            printf("You Lose! c:%d y:%d \n", com, player);
        }
    }
    ShowRate(count, win_count);
}
