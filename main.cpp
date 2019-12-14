#include<stdio.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

using namespace std;
const int UP = -1, DOWN = 1;
int screenX = 85;
int screenY = 25;
int xPositionPlayer1 = 2;
int xPositionPlayer2 = screenX - 2;

int cursorLen = 3;
struct Player {
    int previousPositionY;
    int currentPositionY;
    int xPos;
    bool canPlay;
    int direction = -10;

} player1[3], player2[3];
struct ballLocation {
    int currentX;
    int currentY;
    int previousX;
    int previousY;
}ball;

void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

int drawScreen() {

    for (int i = 1; i < screenX; i++) {
        gotoxy(i, 0);
        printf("%c", 205);
    }
    gotoxy(screenX, 0);
    printf("%c", 187);
    for (int i = 1; i < screenX; i++) {
        gotoxy(i, screenY);
        printf("%c", 205);
    }
    gotoxy(0, screenY);
    printf("%c", 200);


    for (int i = 1; i < screenY; i++) {
        gotoxy(0, i);
        printf("%c", 186);
    }
    gotoxy(0, 0);
    printf("%c", 201);
    for (int i = 1; i < screenY; i++) {
        gotoxy(screenX, i);
        printf("%c", 186);
    }
    gotoxy(screenX, screenY);
    printf("%c", 188);

    printf("\033[0;31m");
//    gotoxy(screenX/2,0);
    for (int i = 1; i < screenY; i++) {
        gotoxy(screenX / 2, i);
        printf("%c", 186);
    }
    printf("\033[0m");
    gotoxy(0, screenY + 3);

    return (0);
}

int clearScreen() {
    system("cls");
    return (0);
}

int clear(int i, int j) {
    gotoxy(i, j);
    printf(" ");
    return (0);
}


void findLocationBall(){
    clear(ball.previousX,ball.previousY);
    int x = ball.currentX + (ball.currentX - ball.previousX);
    int y = ball.currentY + (ball.currentY - ball.previousY);
    ball.previousX = ball.currentX;
    ball.previousY = ball.currentY;
    if(y<=0 || y >= screenY){
        ball.currentX = x ;
        ball.currentY = y * -1;
    }else {
        ball.currentX = x ;
        ball.currentY = y ;
    }
    gotoxy(ball.currentX,ball.currentY);
    printf("%c",254);
    gotoxy(0,screenY+5);
    printf("ball %d , %d",ball.currentX,ball.currentY);
    sleep(1);
}

void initBall(){
    int randX;
    int randY;
    while(int ran =  rand() % 3){
        if(ran-3 != 0){
            randX = ran-3;
            break;
        }
    }
    while(int ran =  rand() % 3){
        if(ran-3 != 0){
            randY = ran-3;
            break;
        }
    }


    ball.previousX = screenX/2;
    ball.previousY = screenY/2;
    ball.currentY = randY + ball.previousY;
    ball.currentX = randX + ball.previousX;
}

void drawPlayer(Player player[]) {
    //todo implemnet socket here
    for (int i = 0; i < cursorLen; i++) {
//        printf("%d",direction);
        if (player[0].direction!= -10) {
            if (player[0].direction == UP) {
                clear(player[0].xPos, player[i].previousPositionY);
                gotoxy(player[0].xPos, player[i].currentPositionY);
                printf("%c", 186);
            } else if (player[0].direction == DOWN) {
                clear(player[0].xPos, player[cursorLen-1 - i].previousPositionY);
                gotoxy(player[0].xPos, player[cursorLen-1 - i].currentPositionY);
                printf("%c", 186);

            }
        }else {
            gotoxy(player[0].xPos, player[i].currentPositionY);
            printf("%c", 186);
        }


    }
//    sleep(150);
};

int keyPress() {
    if (kbhit()) {
        int key = getch();
        if (key == 27) {
            clearScreen();//<Esc> button
//            score();
            return -1;
        } else if (key == 72) {
            player1[0].direction = UP;
            player1[0].canPlay = true;
//            printf("UP");
            return key;
        } else if (key == 80) {
            player1[0].direction = DOWN;
            player1[0].canPlay = true;
            return key;
        }
        else if(key==119) {
            player2[0].direction = UP;
            player2[0].canPlay = true;
            return key;
        }// w Button

        else if(key==115){
            player2[0].direction = DOWN;
            player2[0].canPlay = true;
            return key;
        }  // s Button

    }
    return -1;
}

void actionPlayer(Player player[]) {
//    printf("direction : %s" , direction);
    if (player[0].canPlay == true) {
        player[0].canPlay = false;
        if (player[0].direction == UP && player[0].currentPositionY > 1) {
            player[0].previousPositionY = player[0].currentPositionY;
            player[0].currentPositionY += player[0].direction;
            for (int i = 1; i < cursorLen; i++) {
                player[i].previousPositionY = player[i].currentPositionY;
                player[i].currentPositionY = player[i - 1].previousPositionY;
            }
            drawPlayer(player);
        } else if (player[0].direction == DOWN && player[cursorLen - 1].currentPositionY < screenY-1) {
            player[cursorLen - 1].previousPositionY = player[cursorLen - 1].currentPositionY;
            player[cursorLen - 1].currentPositionY += player[0].direction;
            for (int i = cursorLen - 2; i >= 0; i--) {
                player[i].previousPositionY = player[i].currentPositionY;
                player[i].currentPositionY = player[i + 1].previousPositionY;
            }
            drawPlayer(player);
        }
        gotoxy(0,screenY+3);
        for (int i = 0; i < cursorLen; i++) {
            printf("previ %d ",player[i].previousPositionY);
            printf("current %d ",player[i].currentPositionY );
            printf("\n");

        }

    }


}

void resetPlayerLocation(Player player[]) {
    for (int i = 0; i < cursorLen; i++) {
        if (player == player2) {
            player[i].xPos = screenX - 2;
        } else {
            player[i].xPos = 2;
        }
//        player[i].xPos = 2;
        player[i].currentPositionY = screenY / 2 +i ;
//        player[i].currentPositionY = i+5 ;
        player[i].previousPositionY = player[i].currentPositionY ;
        player[i].canPlay = false;
    }
}

void init() {
    resetPlayerLocation(player1);
    resetPlayerLocation(player2);
    initBall();
}

void game() {
    drawPlayer(player1);
    drawPlayer(player2);
    while (true) {
        if (keyPress()) {
            actionPlayer(player1);
            actionPlayer(player2);
            findLocationBall();

        }
    }
}




int main(int argc, char const *argv[]) {
//    cout << "Salam Donya!";
    init();
    clearScreen();
    drawScreen();
    game();
    return 0;
}