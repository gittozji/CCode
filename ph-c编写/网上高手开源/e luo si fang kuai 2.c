#include <stdio.h>
#include <bios.h>
#include <dos.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#define true         1
#define false         0
#define BoardWidth    12
#define BoardHeight     23
#define _INNER_HELPER /*inner helper method */
/*Scan Codes Define*/
enum KEYCODES
{
    K_ESC                =0x011b,
    K_UP                =0x4800,        /* upward arrow */
    K_LEFT            =0x4b00,
    K_DOWN            =0x5000,
    K_RIGHT            =0x4d00,
    K_SPACE            =0x3920,
    K_P                =0x1970
};

/* the data structure of the block */
typedef struct tagBlock
{
    char c[4][4];    /* cell fill info array, 0-empty, 1-filled */
    int x;                /* block position cx [ 0,BoardWidht -1] */
    int y;                /* block position cy [-4,BoardHeight-1] */
    char color;        /* block color */
    char size;        /* block max size in width or height */
    char name;        /* block name (the block's shape) */
} Block;

/* game's global info */
int FrameTime= 1300;
int CellSize= 18;
int BoardLeft= 30;
int BoardTop=    30;

/* next block grid */
int NBBoardLeft= 300;
int NBBoardTop=    30;
int NBCellSize=  10;

/* score board position */
int ScoreBoardLeft= 300;
int ScoreBoardTop=100;
int ScoreBoardWidth=200;
int ScoreBoardHeight=35;
int ScoreColor=LIGHTCYAN;

/* infor text postion */
int InfoLeft=300;
int InfoTop=200;
int InfoColor=YELLOW;

int BorderColor=DARKGRAY;
int BkGndColor=BLACK;
int GameRunning=true;
int TopLine=BoardHeight-1;    /* top empty line */
int TotalScore=100;
char info_score[20];
char info_help[255];
char info_common[255];

/* our board, Board[x][y][0]-isFilled, Board[x][y][1]-fillColor */
unsigned char Board[BoardWidth][BoardHeight][2];
char BufferCells[4][4];    /* used to judge if can rotate block */
Block curBlock;        /* current moving block */
Block nextBlock;    /* next Block to appear */

/* function list */
int GetKeyCode();
int CanMove(int dx,int dy);
int CanRotate();
int RotateBlock(Block *block);
int MoveBlock(Block *block,int dx,int dy);
void DrawBlock(Block *block,int,int,int);
void EraseBlock(Block *block,int,int,int);
void DisplayScore();
void DisplayInfo(char* text);
void GenerateBlock(Block *block);
void NextBlock();
void InitGame();
int PauseGame();
void QuitGame();

/*Get Key Code */
int _INNER_HELPER GetKeyCode()
{
    int key=0;
    if(bioskey(1))
    {
        key=bioskey(0);
    }
    return key;
}

/* display text! */
void _INNER_HELPER DisplayInfo(char *text)
{
    setcolor(BkGndColor);
    outtextxy(InfoLeft,InfoTop,info_common);
    strcpy(info_common,text);
    setcolor(InfoColor);
    outtextxy(InfoLeft,InfoTop,info_common);
}

/* create a new block by key number,
* the block anchor to the top-left corner of 4*4 cells
*/
void _INNER_HELPER GenerateBlock(Block *block)
{
    int key=(random(13)*random(17)+random(1000)+random(3000))%7;
    block->size=3;/* because most blocks' size=3 */
    memset(block->c,0,16);
    switch(key)
    {
        case 0:
            block->name='T';
            block->color=RED;
            block->c[1][0]=1;
            block->c[1][1]=1, block->c[2][1]=1;
            block->c[1][2]=1;
            break;
        case 1:
            block->name='L';
            block->color=YELLOW;
            block->c[1][0]=1;
            block->c[1][1]=1;
            block->c[1][2]=1, block->c[2][2]=1;
            break;
        case 2:
            block->name='J';
            block->color=LIGHTGRAY;
            block->c[1][0]=1;
            block->c[1][1]=1;
            block->c[1][2]=1, block->c[0][2]=1;
            break;
        case 3:
            block->name='z';
            block->color=CYAN;
            block->c[0][0]=1, block->c[1][0]=1;
            block->c[1][1]=1, block->c[2][1]=1;
            break;
        case 4:
            block->name='5';
            block->color=LIGHTBLUE;
            block->c[1][0]=1, block->c[2][0]=1;
            block->c[0][1]=1, block->c[1][1]=1;
            break;
        case 5:
            block->name='o';
            block->color=BLUE;
            block->size=2;
            block->c[0][0]=1, block->c[1][0]=1;
            block->c[0][1]=1, block->c[1][1]=1;
            break;
        case 6:
            block->name='I';
            block->color=GREEN;
            block->size=4;
            block->c[1][0]=1;
            block->c[1][1]=1;
            block->c[1][2]=1;
            block->c[1][3]=1;
            break;
    }
}

/* get next block! */
void NextBlock()
{
    /* copy the nextBlock to curBlock */
    curBlock.size=nextBlock.size;
    curBlock.color=nextBlock.color;
    curBlock.x=(BoardWidth-4)/2;
    curBlock.y=-curBlock.size;
    memcpy(curBlock.c,nextBlock.c,16);
    /* generate nextBlock and show it */
    EraseBlock(&nextBlock,NBBoardLeft,NBBoardTop,NBCellSize);
    GenerateBlock(&nextBlock);
    nextBlock.x=1,nextBlock.y=0;
    DrawBlock(&nextBlock,NBBoardLeft,NBBoardTop,NBCellSize);
}

/* rotate the block, update the block struct data */
int _INNER_HELPER RotateCells(char c[4][4],char blockSize)
{
    char temp,i,j;
    switch(blockSize)
    {
        case 3:
            temp=c[0][0];
            c[0][0]=c[2][0], c[2][0]=c[2][2],    c[2][2]=c[0][2], c[0][2]=temp;
            temp=c[0][1];
            c[0][1]=c[1][0], c[1][0]=c[2][1],    c[2][1]=c[1][2], c[1][2]=temp;
            break;
        case 4:    /* only 'I' block arived here! */
            c[1][0]=1-c[1][0], c[1][2]=1-c[1][2], c[1][3]=1-c[1][3];
            c[0][1]=1-c[0][1], c[2][1]=1-c[2][1],    c[3][1]=1-c[3][1];
            break;
    }
}

/* judge if the block can move toward the direction */
int CanMove(int dx,int dy)
{
    int i,j,tempX,tempY;
    for(i=0;i<curBlock.size;i++)
    {
        for(j=0;j<curBlock.size;j++)
        {
            if(curBlock.c[i][j])
            {
                /* cannot move leftward or rightward */
                tempX = curBlock.x + i + dx;
                if(tempX<0 || tempX>(BoardWidth-1))    return false; /* make sure x is valid! */
                /* cannot move downward */
                tempY = curBlock.y + j + dy;
                if(tempY>(BoardHeight-1))    return false; /* y is only checked lower bound, maybe negative!!!! */
                /* the cell already filled, we must check Y's upper bound before check cell ! */
                if(tempY>=0 && Board[tempX][tempY][0]) return false;
            }
        }
    }
    return true;
}

/* judge if the block can rotate */
int CanRotate()
{
    int i,j,tempX,tempY;
    /* update buffer */
    memcpy(BufferCells, curBlock.c, 16);
    RotateCells(BufferCells,curBlock.size);
    for(i=0;i<curBlock.size;i++)
    {
        for(j=0;j<curBlock.size;j++)
        {
            if(BufferCells[i][j])
            {
                tempX=curBlock.x+i;
                tempY=curBlock.y+j;
                if(tempX<0 || tempX>(BoardWidth-1))
                    return false;
                if(tempY>(BoardHeight-1))
                    return false;
                if(tempY>=0 && Board[tempX][tempY][0])
                    return false;
            }
        }
    }
    return true;
}

/* draw the block */
void _INNER_HELPER DrawBlock(Block *block,int bdLeft,int bdTop,int cellSize)
{
    int i,j;
    setfillstyle(SOLID_FILL,block->color);
    for(i=0;i<block->size;i++)
    {
        for(j=0;j<block->size;j++)
        {
            if(block->c[i][j] && (block->y+j)>=0)
            {
                floodfill(
                    bdLeft+cellSize*(i+block->x)+cellSize/2,
                    bdTop+cellSize*(j+block->y)+cellSize/2,
                    BorderColor);
            }
        }
    }
}

/* Rotate the block, if success, return true */
int RotateBlock(Block *block)
{
    char temp,i,j;
    int b_success;
    if(block->size==2)
        return true;
    if(( b_success=CanRotate()))
    {
        EraseBlock(block,BoardLeft,BoardTop,CellSize);
        memcpy(curBlock.c,BufferCells,16);
        DrawBlock(block,BoardLeft,BoardTop,CellSize);
    }
    return b_success;
}


/* erase a block, only fill the filled cell with background color */
void _INNER_HELPER EraseBlock(Block *block,int bdLeft,int bdTop,int cellSize)
{
    int i,j;
    setfillstyle(SOLID_FILL,BkGndColor);
    for(i=0;i<block->size;i++)
    {
        for(j=0;j<block->size;j++)
        {
            if(block->c[i][j] && (block->y+j>=0))
            {
                floodfill(
                    bdLeft+cellSize*(i+block->x)+cellSize/2,
                    bdTop+cellSize*(j+block->y)+cellSize/2,
                    BorderColor);
            }
        }
    }
}

/* move by the direction if can, donothing if cannot
* return value: true - success, false - cannot move toward this direction
*/
int MoveBlock(Block *block,int dx,int dy)
{
    int b_canmove=CanMove(dx,dy);
    if(b_canmove)
    {
        EraseBlock(block,BoardLeft,BoardTop,CellSize);
        curBlock.x+=dx;
        curBlock.y+=dy;
        DrawBlock(block,BoardLeft,BoardTop,CellSize);
    }
    return b_canmove;
}

/* drop the block to the bottom! */
int DropBlock(Block *block)
{
    EraseBlock(block,BoardLeft,BoardTop,CellSize);
    while(CanMove(0,1))
    {
        curBlock.y++;
    }
    DrawBlock(block,BoardLeft,BoardTop,CellSize);
    return 0;/* return value is assign to the block's alive */
}


/* init the graphics mode, draw the board grid */
void InitGame()
{
    int i,j,gdriver=DETECT,gmode;
    struct time sysTime;
    /* draw board cells */
    memset(Board,0,BoardWidth*BoardHeight*2);
    memset(nextBlock.c,0,16);
    strcpy(info_help,"P: Pause Game. --by hoodlum1980");
    initgraph(&gdriver,&gmode,"");
    setcolor(BorderColor);
    for(i=0;i<=BoardWidth;i++)
    {
        line(BoardLeft+i*CellSize, BoardTop, BoardLeft+i*CellSize, BoardTop+ BoardHeight*CellSize);
    }
    for(i=0;i<=BoardHeight;i++)
    {
        line(BoardLeft, BoardTop+i*CellSize, BoardLeft+BoardWidth*CellSize, BoardTop+ i*CellSize);
    }
    /* draw board outer border rect */
    rectangle(BoardLeft-CellSize/4, BoardTop-CellSize/4,
        BoardLeft+BoardWidth*CellSize+CellSize/4,
        BoardTop+BoardHeight*CellSize+CellSize/4);

    /* draw next block grids */
    for(i=0;i<=4;i++)
    {
        line(NBBoardLeft+i*NBCellSize, NBBoardTop, NBBoardLeft+i*NBCellSize, NBBoardTop+4*NBCellSize);
        line(NBBoardLeft, NBBoardTop+i*NBCellSize, NBBoardLeft+4*NBCellSize, NBBoardTop+ i*NBCellSize);
    }

    /* draw score rect */
    rectangle(ScoreBoardLeft,ScoreBoardTop,ScoreBoardLeft+ScoreBoardWidth,ScoreBoardTop+ScoreBoardHeight);
    DisplayScore();

    /* set new seed! */
    gettime(&sysTime);
    srand(sysTime.ti_hour*3600+sysTime.ti_min*60+sysTime.ti_sec);

    GenerateBlock(&nextBlock);
    NextBlock();    /* create first block */
    setcolor(DARKGRAY);
    outtextxy(InfoLeft,InfoTop+20,"Up  -rotate  Space-drop");
    outtextxy(InfoLeft,InfoTop+35,"Left-left    Right-right");
    outtextxy(InfoLeft,InfoTop+50,"Esc -exit");
    DisplayInfo(info_help);
}

/* set the isFilled and fillcolor data to the board */
void _INNER_HELPER FillBoardData()
{
    int i,j;
    for(i=0;i<curBlock.size;i++)
    {
        for(j=0;j<curBlock.size;j++)
        {
            if(curBlock.c[i][j] && (curBlock.y+j)>=0)
            {
                Board[curBlock.x+i][curBlock.y+j][0]=1;
                Board[curBlock.x+i][curBlock.y+j][1]=curBlock.color;
            }
        }
    }
}

/* draw one line of the board */
void _INNER_HELPER PaintBoard()
{
    int i,j,fillcolor;
    for(j=max((TopLine-4),0);j<BoardHeight;j++)
    {
        for(i=0;i<BoardWidth;i++)
        {
            fillcolor=Board[i][j][0]? Board[i][j][1]:BkGndColor;
            setfillstyle(SOLID_FILL,fillcolor);
            floodfill(BoardLeft+i*CellSize+CellSize/2,BoardTop+j*CellSize+CellSize/2,BorderColor);
        }
    }
}

/* check if one line if filled full and increase the totalScore! */
void _INNER_HELPER CheckBoard()
{
    int i,j,k,score=10,sum=0,topy,lines=0;
    /* we find the top empty line! */
    j=topy=BoardHeight-1;
    do
    {
        sum=0;
        for(i=0;i< BoardWidth; i++)
        {
            sum+=Board[i][topy][0];
        }
        topy--;
    } while(sum>0 && topy>0);

    /* remove the full filled line (max remove lines count = 4) */
    do
    {
        sum=0;
        for(i=0;i< BoardWidth; i++)
            sum+=Board[i][j][0];

        if(sum==BoardWidth)/* we find this line is full filled, remove it! */
        {
            /* move the cells data down one line */
            for(k=j; k > topy;k--)
            {
                for(i=0;i<BoardWidth;i++)
                {
                    Board[i][k][0]=Board[i][k-1][0];
                    Board[i][k][1]=Board[i][k-1][1];
                }
            }
            /*make the top line empty! */
            for(i=0;i<BoardWidth;i++)
            {
                Board[i][topy][0]=0;
                Board[i][topy][1]=0;
            }
            topy++;        /* move the topline downward one line! */
            lines++;    /* lines <=4 */
            TotalScore+=score;
            score*=2;    /* adding: 10, 30, 70, 150 */
        }
        else
            j--;
    } while(sum>0 && j>topy && lines<4);
    /* speed up the game when score is high, minimum is 400 */
    FrameTime=max(1200-100*(TotalScore/200), 400);
    TopLine=topy;/* update the top line */
    /* if no lines remove, only add 1: */
    if(lines==0)
        TotalScore++;
}

/* display the score */
void _INNER_HELPER DisplayScore()
{
    setcolor(BkGndColor);
    outtextxy(ScoreBoardLeft+5,ScoreBoardTop+5,info_score);
    setcolor(ScoreColor);
    sprintf(info_score,"Score: %d",TotalScore);
    outtextxy(ScoreBoardLeft+5,ScoreBoardTop+5,info_score);
}

/* we call this function when a block is inactive. */
void UpdateBoard()
{
    FillBoardData();
    CheckBoard();
    PaintBoard();
    DisplayScore();
}

/* pause the game, and timer handler stop move down the block! */
int PauseGame()
{
    int key=0;
    DisplayInfo("Press P to Start or Resume!");
    while(key!=K_P && key!=K_ESC)
    {
        while(!(key=GetKeyCode())){}
    }
    DisplayInfo(info_help);
    return key;
}

/* quit the game and do cleaning work. */
void QuitGame()
{
    closegraph();
}

/* the entry point function. */
void main()
{
    int i,flag=1,j,key=0,tick=0;
    InitGame();
    if(PauseGame()==K_ESC)
        goto GameOver;
    /* wait until a key pressed */
    while(key!=K_ESC)
    {
        /* wait until a key pressed */
        while(!(key=GetKeyCode()))
        {
            tick++;
            if(tick>=FrameTime)
            {
                /* our block has dead! (can't move down), we get next block */
                if(!MoveBlock(&curBlock,0,1))
                {
                    UpdateBoard();
                    NextBlock();
                    if(!CanMove(0,1))
                        goto GameOver;
                }
                tick=0;
            }
            delay(100);
        }
        switch(key)
        {
            case K_LEFT:
                MoveBlock(&curBlock,-1,0);
                break;
            case K_RIGHT:
                MoveBlock(&curBlock,1,0);
                break;
            case K_DOWN:
                MoveBlock(&curBlock,0,1);
                break;
            case K_UP:
                RotateBlock(&curBlock);
                break;
            case K_SPACE:
                DropBlock(&curBlock);
                break;
            case K_P:
                PauseGame();
                break;
        }
    }
GameOver:
    DisplayInfo("GAME OVER!  Press any key to exit!");
    getch(); /* wait the user Press any key. */
    QuitGame();
}

