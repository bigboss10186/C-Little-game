#define _CRT_SECURE_NO_WARINGS
#include<iostream>

#include<string.h>
#include "wall.h"
#include"snake.h"
#include"food.h"
#include<ctime>
#include<conio.h>
#include<windows.h>
using namespace std;
void gotoxy(HANDLE hOut,int x,int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut,pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
int main()
{
    srand((unsigned int)time(NULL));
    //是否死亡标示
    bool isDead = false;
    char preKey = NULL;
    Wall wall;
    wall.initWall();
    wall.drawWall();
    Food food(wall);
    food.setfood();
    Snake snake(wall,food);
    snake.initSnake();
    // snake.delPoint();
    gotoxy(hOut,0,Wall::ROW);
    // gotoxy(hOut,10,5);
    while(!isDead)
    {
        char key = _getch();
        //判断上一次的移动方向
        if(preKey == NULL && key==snake.LEFT)
        {
            continue;
        }
        do{
            if(key == snake.UP||key == snake.DOWN||key== snake.LEFT||key== snake.RIGHT)
            {
                //判断本次按键是否和上次冲突
                if((key==snake.LEFT && preKey==snake.RIGHT)||(key==snake.RIGHT && preKey==snake.LEFT)||(key==snake.UP && preKey==snake.DOWN)||(key==snake.DOWN && preKey==snake.UP))
                {
                    key = preKey;
                }
                else
                {
                    preKey = key;
                    if(snake.move(key) ==true)
                    {
                    //移动成功代码
                    // system("cls");
                    // wall.drawWall();
                    gotoxy(hOut,0,Wall::ROW);
                    cout<<"score:"<<snake.getScore()<<endl;
                    Sleep(snake.getSleepTime());
                    }
                    else
                    {
                    isDead = true;
                    cout<<"score:"<<snake.getScore()<<endl;
                    break;
                    }
                }
            }
            else
            {
                key = preKey;//强制将错误按键换成之前的按键
            }
        }while(!_kbhit());

    }


    system("pause");
    return EXIT_SUCCESS;
}