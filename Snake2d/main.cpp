#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection sDir;

void Setup()
{
    gameOver = false;
    sDir = STOP;
    x = width/2 - 1;
    y = height/2 - 1;
    srand(time(NULL));
    fruitX = rand()%width;
    fruitY = rand()%height;
    score = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i <= width; i++) cout<<"#";
    cout<<"   Score: "<<score<<endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((j == 0)||(j == (width - 1))) cout <<"#";
            if (i == y && j == x) cout<<"o";
            else if (i == fruitY && j == fruitX)
                cout<<"X";
            else
                cout<<" ";
        }
        cout<<endl;
    }
    for (int i = 0; i <= width; i++) cout<<"#";
    cout<<endl;

}

void Input()
{
    if (_kbhit())
    {
        char symbol = _getch();
        switch (symbol)
        {
            case 'a': sDir = LEFT;
                break;
            case 75: sDir = LEFT;
                break;
            case 'd': sDir = RIGHT;
                break;
            case 77: sDir = RIGHT;
                break;
            case 'w': sDir = UP;
                break;
            case 72: sDir = UP;
                break;
            case 's': sDir = DOWN;
                break;
            case 80: sDir = DOWN;
                break;
            case 'x': gameOver = true;
                break;
        }
    }
}

void eatFruit()
{
    score+=10;
    srand(time(NULL));
    fruitX = rand()%width - 1;
    fruitY = rand()%height - 1;
}

void Logic()
{
        switch (sDir)
        {
            case LEFT: x--;
                break;
            case RIGHT: x++;
                break;
            case UP: y--;
                break;
            case DOWN: y++;
                break;
        }
        if((x>=width)||(y>=height)||(x<=0)||(y<=0)) gameOver = true;
        if (x == fruitX && y == fruitY) eatFruit();

}

int main()
{
    Setup();
    while(!gameOver)
    {
        if(time(NULL)%1 == 0)
        {
            Draw();
            Input();
            Logic();
        }
    }
    return 0;
}
