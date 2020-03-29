#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>

using namespace std;

bool gameOver;
bool buttonHitted = false;
const int width = 20;
const int height = 20;
int score;
const int scoreInSpeed = 200;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum fruitSize {SMALL, BIG};

//Map Build
char wall = char(219);

class Snake
{
    public:
//Default Constructor
        Snake()
        {
            Length = 1;
            Direction = STOP;
            Speed = 1;
            x = width/2 - 1;
            y = height/2 - 1;
        }
//Constructor with 2 parametres
        Snake(int startX, int startY)
        {
            Length = 1;
            Direction = STOP;
            Speed = 1;
            x = startX;
            y = startY;
        }
//------------------------------------------------------------------
        void EatenFruit(fruitSize fS)
        {
            if (fS == SMALL) Length += 1 ;
                else Length += 2;
        };
//------------------------------------------------------------------

//---------------------------------------------------------------------
        void SpeedUp(int scr)
        {
            if (scr != 0 && scr%scoreInSpeed == 0) Speed++;
        };
//----------------------------------------------------------------------
        void moveTo(int newX, int newY)
        {
            x = newX;
            y = newY;
        }
        int getX()
        {
            return x;
        };
        int getY()
        {
            return y;
        };
        int getSpeed()
        {
            return Speed;
        };
        int getLength()
        {
            return Length;
        };
    private:
        int Length;
        eDirection Direction;
        int Speed;
        int x;
        int y;
};
Snake playerSnake;

struct fruitStruct {int x; int y;  fruitSize Size;};
fruitStruct fruit;

void fruitSpawn()
{
    srand(time(NULL));
    fruit.x = rand()%width;
    fruit.y = rand()%height;
    fruit.Size = SMALL;
}

void Setup()
{
    gameOver = false;
    fruitSpawn();
    score = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i <= width + 1; i++) cout<<wall;
    cout<<"   Score: "<<_kbhit()<<endl;
    for (int i = 1; i < height; i++)
    {

        for (int j = 0; j <= width; j++)
        {
            if ((j == 0)||(j == width)) cout <<wall;
//SNAKE DRAWING
            if (i == playerSnake.getY() && j == playerSnake.getX()) cout<<"o";

            else if (i == fruit.y && j == fruit.x)
                cout<<"X";
            else
                cout<<" ";
        }

        if (i == 1) cout<<"   Snake Length: "<<playerSnake.getLength();
        if (i == 1) cout<<"   Snake Speed: "<<playerSnake.getSpeed();

        cout<<endl;
    }
    for (int i = 0; i <= width + 1; i++) cout<<wall;
    cout<<endl;

}

void Input()
{
    if (_kbhit()) buttonHitted = true;
    if (buttonHitted)
    {
        char symbol = _getch();
        cout<< symbol;
        int x = playerSnake.getX();
        int y = playerSnake.getY();
        if (symbol == 'x') gameOver = true;
        switch (symbol)
            {
                case 'a': playerSnake.moveTo(x-1,y);
                    break;
                case 75: playerSnake.moveTo(x-1,y);
                    break;
                case 'd': playerSnake.moveTo(x+1,y);
                    break;
                case 77: playerSnake.moveTo(x+1,y);
                    break;
                case 'w': playerSnake.moveTo(x,y-1);
                    break;
                case 72: playerSnake.moveTo(x,y-1);
                    break;
                case 's': playerSnake.moveTo(x,y+1);
                    break;
                case 80: playerSnake.moveTo(x,y+1);
                    break;
            }
    }
}

void eatFruit()
{
    score+=10;
    fruitSpawn();
}

void Logic()
{
    if (playerSnake.getX() == fruit.x && playerSnake.getY() == fruit.y)
    {
        playerSnake.EatenFruit(fruit.Size);
        eatFruit();
    }
}

int main()
{
    Setup();
    while(!gameOver)
    {
       // if(time(NULL)%1 == 0)
        {
            Draw();
            Input();
            Logic();
        }
    }
    return 0;
}
