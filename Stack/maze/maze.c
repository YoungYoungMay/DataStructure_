#include "maze.h"

void PointInit(Point* entry)
{
    if(entry == NULL)
        return;
    entry->row = 0;
    entry->col = 1;
    return;
}

void MazeInit(Maze* maze)//初始化,建立一个迷宫地图
{
    if(maze == NULL)
        return;
    int map[ROW][COL] = {{0,1,0,0,0,0},\
                         {0,1,1,1,0,0},\
                         {0,1,0,1,1,1},\
                         {1,1,1,0,0,0},\
                         {0,0,1,0,0,0},\
                         {0,0,1,0,0,0}};//1表示路，0表示墙，之后走过的路标记为2
    size_t i = 0;
    for(; i<ROW; ++i)
    {
        size_t j = 0;
        for(; j<COL; ++j)
        {
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}

void MazePrint(Maze* maze, const char* msg)//打印迷宫
{
    printf("[%s]\n",msg);
    if(maze == NULL)
        return;
    size_t i = 0;
    for(; i<ROW; ++i)
    {
        size_t j = 0;
        for(; j<COL; ++j)
        {
            printf("%2d ",maze->map[i][j]);
        }
        printf("\n");
    }
    return;
}

int CanStay(Maze* maze, Point cur)//判断当前点是否能落脚
{
    if(maze == NULL)
        return 0;
    if(cur.row < 0 || cur.row >= ROW || cur.col < 0 || cur.col >= COL)//当前点越界，不在迷宫地图内
        return 0;
    if(maze->map[cur.row][cur.col] == 1)
        return 1;
    return 0;
}

void Mark(Maze* maze, Point cur)//标记当前点，将对应值改为2即可
{
    if(maze == NULL)
        return;
    maze->map[cur.row][cur.col] = 2;
    return;
}

int IsExit(Maze* maze, Point cur, Point entry)//判断当前点是否为出口，注意判断是否为入口
{
    if(maze == NULL)
        return 0;
    if(cur.row == entry.row && cur.col == entry.col)//当前点为入口点
        return 0;
    if(cur.row == 0 || cur.row == ROW-1 || cur.col == 0 || cur.col == COL-1)//迷宫有四条边，每一个边上的点都可作出口
        return 1;
    return 0;
}

///////////////////////////////////////////////////////////////////
////1.利用递归查找简单迷宫的一条路径
///////////////////////////////////////////////////////////////////

void _GetPath(Maze* maze, Point cur, Point entry)//真正实现查找迷宫路径的函数
{
    printf("cur : (%d, %d)\n",cur.row,cur.col);//可看到函数调用的过程
    if(maze == NULL)
        return;
    //1.判断当前点是否能落脚
    if(!CanStay(maze,cur))
        return;
    //2.能落脚就标记
    Mark(maze,cur);
    //3.判断当前点是否为出口(非入口、迷宫最外围),为出口，就找到一条路径
    if(IsExit(maze,cur,entry))
    {
        printf("找到一条路\n");
        return;
    }
    //4.不为出口，顺时针探测四周点，递归调用函数本身，递归时更新cur
    Point up = cur;//上方点
    up.row -= 1;
    _GetPath(maze,up,entry);
    Point right = cur;//右方点
    right.col += 1;
    _GetPath(maze,right,entry);
    Point down = cur;//下方点
    down.row += 1;
    _GetPath(maze,down,entry);
    Point left = cur;//左方点
    left.col -= 1;
    _GetPath(maze,left,entry);
    return;
}

void GetPath(Maze* maze,Point entry)//寻找迷宫路径
{
    if(maze == NULL)
        return;
    _GetPath(maze,entry,entry);//调用寻找函数，第二个参数表示当前位置，第三个参数表示入口点
}

///////////////////////////////////////////////////////////////////
////2.利用非递归(循环)查找简单迷宫的一条路径
///////////////////////////////////////////////////////////////////

void SeqStackInit(SeqStack* stack)
{
    if(stack == NULL)
        return;
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (Point*)malloc(sizeof(Point) * stack->capacity);
    return;
}

void SeqStackPush(SeqStack* stack,Point value)
{
    if(stack == NULL)
        return;
    if(stack->size >= stack->capacity)
        return;
    stack->data[(stack->size)++] = value;
    return;
}

void SeqStackPop(SeqStack* stack)
{
    if(stack == NULL)
        return;
    if(stack->size == 0)
        return;
    --stack->size;
    return;
}

int SeqStackGetTop(SeqStack* stack, Point* value)
{
    if(stack == NULL || value == NULL)
        return 0;
    if(stack->size == 0)
        return 0;
    *value = stack->data[stack->size - 1];
    return 1;
}

void SeqStackPrint(SeqStack* stack, const char* msg)
{
    printf("[%s]\n",msg);
    if(stack == NULL)
        return;
    size_t i = 0;
    for(; i<stack->size; ++i)
    {
        printf("(%d, %d)\n",stack->data[i].row,stack->data[i].col);
    }
    printf("\n");
}

void GetPathByLoop(Maze* maze, Point entry)
{
    if(maze == NULL)
        return;
    //1.创建一个栈，用于保存走过的路径
    SeqStack stack;
    SeqStackInit(&stack);
    //2.判断入口能否落脚(不能说明传入的参数非法)
    if(!CanStay(maze,entry))
        return;
    //3.能落脚就标记并入栈
    Mark(maze,entry);
    SeqStackPush(&stack, entry);
    //4.进入循环，获取当前栈顶元素
    while(1)
    {
        Point top;
        int ret = SeqStackGetTop(&stack, &top);
        if(ret == 0)//栈为空，回溯结束
            return;
        //5.判断是否为出口
        if(IsExit(maze,top,entry))
        {
            printf("找到一条路\n");
            SeqStackPrint(&stack,"找到的路径为");
            return;
        }
        //6.顺时针取四周点，判断是否能落脚。能落脚就标记且入栈，进行下一轮循环
        Point up = top;//上方点
        up.row -= 1;
        if(CanStay(maze,up))
        {
            Mark(maze,up);
            SeqStackPush(&stack,up);
            continue;
        }
        Point right = top;//右方点
        right.col += 1;
        if(CanStay(maze,right))
        {
            Mark(maze,right);
            SeqStackPush(&stack,right);
            continue;
        }       
        Point down = top;//下方点
        down.row += 1;
        if(CanStay(maze,down))
        {
            Mark(maze,down);
            SeqStackPush(&stack,down);
            continue;
        } 
        Point left = top;//左方点
        left.col -= 1;
        if(CanStay(maze,left))
        {
            Mark(maze,left);
            SeqStackPush(&stack,left);
            continue;
        }
        //7.若四周都不能落脚，出栈顶元素(出到栈为空，则说明没路可走)
        SeqStackPop(&stack);
    }
}

///////////////////////////////////////////////////////////////////
////3.查找简单迷宫的最短路径(递归实现)
///////////////////////////////////////////////////////////////////


void SeqStackAssgin(SeqStack* from, SeqStack* to)
{//to的内存用来拷贝from的，有好几种可能性，这里为了保证代码的简洁性，统一先释放内存再重新申请再拷贝数据
    if(from==NULL || to==NULL)
        return;
    //1.释放to的原有内存
    free(to->data);
    to->size = 0;
    to->capacity = 0;
    //2.依据from的大小给to申请内存
    to->size = from->size;
    to->capacity = from->capacity;
    to->data = (Point*)malloc(sizeof(Point) * to->capacity);
    //3.数据拷贝
    size_t i = 0;
    for(; i<from->size; ++i)
    {
        to->data[i] = from->data[i];
    }
    return;
}

void _GetShortPath(Maze* maze, Point cur, Point entry, SeqStack* cur_path, SeqStack* short_path)
{
    //1.判断当前点是否能落脚
    if(!CanStay(maze,cur))
        return;
    //2.能落脚，标记并入cur_path栈
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //3.判断当前点是否为出口点
    if(IsExit(maze,cur,entry))
    {
        printf("找到了一条路\n");
        //1)为出口，找到一条路，此时若cur_path比short_path栈中路径短或short_path为空，用当前路径代替short_path中的路;
        if(cur_path->size < short_path->size || short_path->size==0)
        {
            printf("找到一条较短路径\n");
            SeqStackAssgin(cur_path, short_path);
        }
        //2)为出口，但比short_path中路径长，再回溯去找另外的路径,并出栈顶元素
        //这里不论cur_path中路径比short_path中短还是长，只要是出口，都要回溯，去找是否还有其他路径
        SeqStackPop(cur_path);
        return;
    }
    //4.不是出口，探测周围四个相邻点
    Point up = cur;
    up.row -= 1;
    _GetShortPath(maze,up,entry,cur_path,short_path);
    Point right = cur;
    right.col += 1;
    _GetShortPath(maze,right,entry,cur_path,short_path);
    Point down = cur;
    down.row += 1;
    _GetShortPath(maze,down,entry,cur_path,short_path);
    Point left = cur;
    left.col -= 1;
    _GetShortPath(maze,left,entry,cur_path,short_path);
    //5.四个点都探测过，就出栈回溯
    SeqStackPop(cur_path);
    return;
}

void GetShortPath(Maze* maze, Point entry)
{//先遍历找到所有路径，找到里面最短的即可
    SeqStack cur_path;
    SeqStack short_path;
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    _GetShortPath(maze, entry, entry, &cur_path, &short_path);
    SeqStackPrint(&short_path,"最短路径");
}

///////////////////////////////////////////////////////////////////
////4.复杂迷宫中查找最短路径(递归实现)
//////      复杂迷宫不仅有多个入口，路径上还可能带环      /////////
///////////////////////////////////////////////////////////////////

void ComplexMazeInit(Maze* maze)//初始化复杂迷宫地图
{
    if(maze == NULL)
        return;
    int map[ROW][COL] = {{0,1,0,0,0,0},\
                         {0,1,1,1,0,0},\
                         {0,1,0,1,1,1},\
                         {1,1,1,1,0,0},\
                         {0,0,1,0,0,0},\
                         {0,0,1,0,0,0}};//1表示路，0表示墙
    size_t i = 0;
    for(; i<ROW; ++i)
    {
        size_t j = 0;
        for(; j<COL; ++j)
        {
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}

void PointPreInit(Point* pre)//入口点的前一个点初始化为(-1,-1)非法点
{
    if(pre == NULL)
        return;
    pre->row = -1;
    pre->col = -1;
    return;
}

int CanStayWithCycle(Maze* maze, Point pre, Point cur)
{
    //1.判断当前点是否在地图上
    if(cur.row < 0 || cur.row >= ROW || cur.col < 0 || cur.col >= COL)
        return 0;
    //2.当前点是否为墙(是则不能落脚)
    if(maze->map[cur.row][cur.col] == 0)
        return 0;
    //3.当前点是否为路(是则直接落脚)
    if(maze->map[cur.row][cur.col] == 1)
        return 1;
    //4.若当前点已走过，判断是否值得走
    //若此时走比之前走花的步数更少，就值得去走，若步数相同或多，就没有意义，因为我们要找最短路径
    //这里不用判断pre位置是否非法，因为仅当入口点为当前点时，pre才会非法，而入口点的值非0即1,前面已过滤
    int pre_value = maze->map[pre.row][pre.col];
    int cur_value = maze->map[cur.row][cur.col];
    if(pre_value + 1 < cur_value)
        return 1;
    return 0;
}

void MarkWithCycle(Maze* maze, Point pre, Point cur)
{//将走过的位置标记为入口点到该点的步数，入口点标记为2，实际步数为每个位置的值减去1
    if(pre.row==-1 && pre.col==-1)//当前点为入口点
    {
        maze->map[cur.row][cur.col] = 2;
        return;
    }
    int pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
    return;
}

void _GetShortPathWithCycle(Maze* maze, Point cur, Point pre, Point entry, SeqStack* cur_path, SeqStack* short_path)
{
    //1.判断当前点是否能落脚(与之前判断方法不同)
    if(!CanStayWithCycle(maze,pre,cur))
        return;
    //2.标记并入cur_path栈(与之前标记方法不同)
    MarkWithCycle(maze, pre, cur);
    SeqStackPush(cur_path, cur);
    //3.判断当前点是否为出口
    if(IsExit(maze, cur, entry))
    {
        //1)为出口，且为更短路径，替换short_path中的路径
        printf("找到一条路\n");
        if(cur_path->size < short_path->size || short_path->size == 0)
        {
            printf("找到一条较短路径\n");
            SeqStackAssgin(cur_path, short_path);
        }
        //2)只要当前点为出口，就要回溯去找其他路径
        SeqStackPop(cur_path);
        return;
    }
    //4.当前点不是出口，探测周围四个相邻点
   Point up = cur;
   up.row -= 1;
   _GetShortPathWithCycle(maze,up,cur,entry,cur_path,short_path);
   Point right = cur;
   right.col += 1;
   _GetShortPathWithCycle(maze,right,cur,entry,cur_path,short_path);
   Point down = cur;
   down.row += 1;
   _GetShortPathWithCycle(maze,down,cur,entry,cur_path,short_path);
   Point left = cur;
   left.col -= 1;
   _GetShortPathWithCycle(maze,left,cur,entry,cur_path,short_path);
    //5.四个点都探测完，出栈回溯
   SeqStackPop(cur_path);
   return;
}

void GetShortPathWithCycle(Maze* maze, Point pre, Point entry)
{//先遍历找到所有路径，找到里面最短的即可
    SeqStack cur_path;
    SeqStack short_path;
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    //该方法的标记与之前不同，还要用到前一步点，所以增加一个参数pre
    _GetShortPathWithCycle(maze, entry, pre, entry, &cur_path, &short_path);
    SeqStackPrint(&short_path,"最短路径");
}

///////////////////////////////////////////////////////////////////
////以下为测试代码，test1、2、3、4对应上面四种求解情况
///////////////////////////////////////////////////////////////////

void test1()
{
    SHOW_NAME;
    Maze maze;
    MazeInit(&maze);
    Point entry;
    PointInit(&entry);
    MazePrint(&maze,"初始迷宫地图");
    GetPath(&maze,entry);
    MazePrint(&maze,"寻找出路");
}

void test2()
{
    SHOW_NAME;
    Maze maze;
    MazeInit(&maze);
    Point entry;
    PointInit(&entry);
    MazePrint(&maze,"初始迷宫地图");
    GetPathByLoop(&maze,entry);
    MazePrint(&maze,"寻找出路");
}

void test3()
{
    SHOW_NAME;
    Maze maze;
    MazeInit(&maze);
    Point entry;
    PointInit(&entry);
    MazePrint(&maze,"初始迷宫地图");
    GetShortPath(&maze,entry);
    MazePrint(&maze,"寻找出路");
}

void test4()
{
    SHOW_NAME;
    Maze maze;
    ComplexMazeInit(&maze);
    Point entry;
    Point pre;
    PointInit(&entry);
    PointPreInit(&pre);
    MazePrint(&maze,"初始迷宫地图");
    GetShortPathWithCycle(&maze, pre, entry); 
    MazePrint(&maze,"寻找出路");
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
