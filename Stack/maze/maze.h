#pragma once

#include <stdio.h>
#include <stdlib.h>

#define SHOW_NAME printf("\n===================%s=================\n",__FUNCTION__);
#define ROW 6
#define COL 6

typedef int MazeType;
typedef struct Point
{
    MazeType row;
    MazeType col;
}Point;

typedef struct Maze
{
    MazeType map[ROW][COL];
}Maze;

typedef struct SeqStack
{
    Point* data;
    size_t size;
    size_t capacity;
}SeqStack;
