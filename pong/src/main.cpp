//#include <iostream>
//#include <time.h>
//#include <stdlib.h>
#include <ncurses.h>

//using namespace std;

enum eDir {
    STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6
};

class cBall {
private:
    int x, y;
    int originalX, originalY;
    eDir direction;
public:
    cBall(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }

    void Reset() {
        x = originalX;
        y = originalY;
        direction = STOP;
    }

    void changeDirection(eDir d) {
        direction = d;
    }

    void randomDirection() {
        direction = (eDir) ((12 % 6) + 1);
    }

    inline int getX() { return x; }

    inline int getY() { return y; }

    inline eDir getDirection() { return direction; }

    void Move() {
        switch (direction) {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case UPLEFT:
                x--;
                y--;
                break;
            case DOWNLEFT:
                x--;
                y++;
                break;
            case RIGHT:
                x++;
                break;
            case UPRIGHT:
                x++;
                y--;
                break;
            case DOWNRIGHT:
                x++;
                y++;
                break;
            default:
                break;
        }
    }

//    friend ostream &operator<<(ostream &o, cBall c) {
//        o << "Ball[" << c.x << "," << c.y << "][" << c.direction << "]";
//        return o;
//    }
};

class cPaddle {
private:
    int x, y;
    int originalX, originalY;
public:
    cPaddle() {
        x = y = 0;
    }

    cPaddle(int posX, int posY) : cPaddle() {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    inline void Reset() {
        x = originalX;
        y = originalY;
    }

    inline int getX() { return x; }

    inline int getY() { return y; }

    inline void moveUp() { y--; }

    inline void moveDown() { y++; }

//    friend ostream &operator<<(ostream &o, cPaddle c) {
//        o << "Paddle[" << c.x << "," << c.y << "]";
//        return o;
//    }
};

class cGameManager {
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;
public:
    cGameManager(int w, int h) {
        //srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }

    ~cGameManager() {
        delete ball, player1, player2;
    }

    void ScoreUp(cPaddle *player) {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Draw() {
        //system("clear");

        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();

        for (int i = 0; i < width + 2; i++)
            printw("#");
        printw("\n");

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    printw("#");

                if (ballX == j && ballY == i)
                    printw("O");
                else if (player1X == j && player1Y == i)
                    printw("#");
                else if (player2X == j && player2Y == i)
                    printw("#");
                else if (player1X == j && player1Y + 1 == i)
                    printw("#");
                else if (player1X == j && player1Y + 2 == i)
                    printw("#");
                else if (player1X == j && player1Y + 3 == i)
                    printw("#");
                else if (player2X == j && player2Y + 1 == i)
                    printw("#");
                else if (player2X == j && player2Y + 2 == i)
                    printw("#");
                else if (player2X == j && player2Y + 3 == i)
                    printw("#");
                else
                    printw(" ");

                if (j == width - 1)
                    printw("#");
            }
            printw("\n");
        }

        for (int i = 0; i < width + 2; i++)
            printw("#");
        printw("\n");
    }

    void Input() {
        ball->Move();

        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();

        char current = getch();
        if (current == up1)
            if (player1Y > 0)
                player1->moveUp();
        if (current == up2)
            if (player2Y > 0)
                player2->moveUp();
        if (current == down1)
            if (player1Y + 4 < height)
                player1->moveDown();
        if (current == down2)
            if (player2Y + 4 < height)
                player2->moveDown();
        if (ball->getDirection() == STOP)
            ball->randomDirection();
        if (current == 'q')
            quit = true;
    }
    void Logic() {
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();
    }
    bool IsQuit() {
        return  quit;
    }
};

int main() {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    cGameManager m(40, 20);
    while (getch() != 'q') {
        m.Input();
        m.Draw();
        napms(40);
    }

    return 0;
}
