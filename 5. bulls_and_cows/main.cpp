#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitGame(void){
    srand(time(NULL));
    printf("Baseball Game ver 0.1 \n");
}

int IsFind(int com[3], int index){
    
    for(int i = 0 ; i < index; i++){
        if(com[i] == com[index]){
            return 1;
        }
    }
    return 0;
}

void MakeComData(int com[3]){
    
    for(int i = 0 ; i < 3; i++){
        com[i] = rand()%10;
        
        if(IsFind(com, i) == 1){
            i--;
        }
    }
}

void InputPlayer(int player[3]){
    printf("0 ~ 9까지 중복 없이 숫자 3개를 넣어주세요. ex) 4 6 8\n");
    
    for(int i =  0 ; i <3; i++){
        scanf("%d", &player[i]);
    }
}

void CheckScore(int com[3], int player[3], int* s, int* b){
    int strike_score = 0, ball_score = 0;
    
    for(int i = 0; i <3; i++){
        for(int j = 0 ; j <3; j++){
            if(player[i] == com[j]){
                if(i == j){
                    strike_score++;
                }
                else{
                    ball_score++;
                }
                break;
            }
        }
    }
    
    *s = strike_score;
    *b = ball_score;
}

int CheckNextGame(void){
    int go = 0;
    
    printf("Press '-1' : End Game or Press '0'\n");
    scanf("%d", &go);
    
    if(go == -1){
        return -1;
    }
    return 0;
}

int main(void) {

    int com[3], player[3];
    int strike = 0, ball = 0;
    
    InitGame();
    
    while(1){
        MakeComData(com);
        
        for(int i = 0 ; i < 10; i++){
            
            InputPlayer(player);
            CheckScore(com, player, &strike, &ball);
            
            if(strike == 3){
                break;
            }
            else{
                printf("strike : %d ball : %d \n", strike, ball);
            }
        }
        
        if(strike == 3){
            printf("3 STRIKE!!! You Win \n");
        }
        else{
            printf("You Lose... \n");
            printf("COM => %d %d %d\n", com[0], com[1], com[2]);
        }
        
        if(CheckNextGame()){
            printf("Thank yoy!\n");
            break;
        }
    }
    return 0;
}
