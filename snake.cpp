#include"snake.h"
#include<windows.h>

void gotoxy1(HANDLE hOut1,int x,int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut1,pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);


Snake::Snake(Wall & tempWall,Food &temfood) : wall(tempWall),food(temfood)
{
    pHead=NULL;
    isRool = false;
}
void Snake::initSnake()
{
    destoryPoint();
    addPoint(5,3);
    addPoint(5,4);
    addPoint(5,5);
}

//销毁所有节点
void Snake::destoryPoint()
{
    Point *pCur = pHead;
    while (pHead!= NULL)
    {
        pCur=pHead->next;
        delete pHead;
        pHead =pCur;
    }
    

}
void Snake::addPoint(int x,int y)
{
    Point *newPoint = new Point;
    newPoint->x=x;
    newPoint->y=y;
    newPoint->next=NULL;
    //如果原来头不是空 改为身子
    if (pHead!=NULL)
    {
        wall.setWall(pHead->x,pHead->y,'=');
        gotoxy1(hOut1,pHead->y*2,pHead->x);
        cout<<"=";
    }
    newPoint->next = pHead;
    pHead = newPoint;//更新头部
    wall.setWall(pHead->x,pHead->y,'@');
    gotoxy1(hOut1,pHead->y*2,pHead->x);
    cout<<"@";
}

void Snake::delPoint()
{
    //两个节点以上才去做删除节点的操作
    if(pHead == NULL|| pHead->next == NULL)
    {
        return;
    }
    Point *pCur = pHead->next;
    Point *pPre = pHead;
    while(pCur->next !=NULL){
        pPre = pPre->next;
        pCur = pCur->next;

    }
    //删除尾节点
    wall.setWall(pCur->x,pCur->y,' ');
    gotoxy1(hOut1,pCur->y*2,pCur->x);
    cout<<" ";
    delete pCur;
    pCur = NULL;
    pPre->next = NULL;
}

bool Snake::move(char key)
{
    int x = pHead->x;
    int y = pHead->y;
    switch (key)
    {
    case UP:
        x--;
        break;
    case DOWN:
        x++;
        break;
    case RIGHT:
        y++;
        break;
    case LEFT:
        y--;
        break;
    default:
        break;
    }
    //判断如果下一步碰到的是尾巴，不应该死亡
    Point *pCur = pHead->next;
    Point *pPre = pHead;
    while(pCur->next !=NULL){
        pPre = pPre->next;
        pCur = pCur->next;

    }
    if (pCur->x==x&&pCur->y==y)
    {
        //碰到尾巴循环
        isRool = true;
    }
    else
    {
        //判断用户到达位置是否成功
        if (wall.getWall(x,y)=='*')
        {
            addPoint(x,y);
            delPoint();
            system("cls");
            wall.drawWall();
            cout<<"GAME OVER!!!"<<endl;
            return false;
        }
        else if (wall.getWall(x,y)=='=')
        {         
            addPoint(x,y);
            system("cls");
            wall.drawWall();
            cout<<"GAME OVER!!!"<<endl;
            return false;
        }
        

    }


    //移动成功两种：吃到食物，未吃到食物
    if(wall.getWall(x,y)=='#')
    {
        addPoint(x,y);
        food.setfood();
    }
    else
    {
        addPoint(x,y);
        delPoint();
        if (isRool == true)
        {
            wall.setWall(x,y,'@');
            gotoxy1(hOut1,2*y,x);
            cout<<"@";
        }
        
    }
    return true;

    
}

int Snake::getSleepTime()
{
    int sleepTime = 0;
    int size = countList();
    if(size<5)
    {
        sleepTime = 300;
    }
    else if (size >=5 && size <=8)
    {
        sleepTime = 200;
    }
    else
    {
        sleepTime = 100;
    }
    return sleepTime;
}

int Snake::countList()
{
    int size = 0;
    Point *curPoint = pHead;
    while(curPoint !=NULL)
    {
        size++;
        curPoint = curPoint->next;
    }
    return size;
}

int Snake::getScore()
{
    int size = countList();
    int score = (size-3)*100;
    return score;
}