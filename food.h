#pragma once
#include<iostream>
#include"wall.h"
using namespace std;


class Food
{
public:
    Food(Wall & tempwall);
    int foodX;
    int foodY;
    void setfood();
    Wall &wall;
};


