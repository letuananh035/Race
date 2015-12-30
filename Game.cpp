#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <string.h>
#include <stdio_ext.h>
#define ROW 19
#define COL 10
int Map[ROW][COL] = { 0 };
char Tile[ROW][20];
int Player[4][3] = {{0,1,0},
                    {1,1,1},
                    {0,1,0},
                    {1,1,1},
                   };
int Enemy[4][3]  = {{2,2,2},
                    {0,2,0},
                    {2,2,2},
                    {0,2,0},
                   };
long long  Speed = 50000;
int Time = 0;
int x_e = 1;
int y_e = 3;
int x = 10;
int y = 2;
int KeyPress = 0;
bool Lose = false;
int Score = 0;
int Lv = 1;
void SetUp(){
    
    strcpy(Tile[0],"*  *  *  *  *  *  *");
    strcpy(Tile[1],"* Score:   0      *");
    strcpy(Tile[2],"* Lv: 1           *");
    strcpy(Tile[3],"*  *  *  *  *  *  *");
    for(int i = 4;i < ROW; ++i)
    {
        strcpy(Tile[i], "                   ");
    }
}
void KeyBoard(){
    if(kbhit())
    {
        char ch = getch();
        switch(ch){
            case 'w':
            {
                if (x - 1 >= 1)
                    {
                    x--;
                    }
                KeyPress = 1;
            }
            break;
            case 's':
            {
                if (x + 1 < ROW - 1 - 3)
                {
                    x++;
                }
                KeyPress = 1;
            }
            break;
            case 'a':
            {
                if (y - 1 >= 0)
                {
                    y--;
                }
                KeyPress = 1;
            }
            break;
            case 'd':
            {
                if (y + 1 < COL - 2)
                {
                    y++;
                }
                KeyPress = 1;
            }
            break;
        };
    }
}
void Draw_Map(){
    printf("\nTime: %d\n",Time);
    for(int i = 0; i < ROW; ++i)
    {
        if(i != 1 && i != 2)
        {
            printf("%s",Tile[i]);
        }
        else
        {
            if(i == 1)
            {    
                printf("* Score: %4d     *",Score);
            }
            else
            {
                printf("* Lv: %2d          *",Lv);
            }
        }
        for(int j = 0; j < COL; ++j)
        {
            if (j == 0 || j == COL - 1 || i == 0 || i == ROW - 1)
            {
                printf(" * ");
            }
            else
            {
                if (Map[i][j] == 0)
                {       
                    printf("   ");
                }
                else
                {
                    printf(" * ");
                }
            }
        }
        printf("\n\n");
    }
}
void Reset_Map_Player(){
    for(int i = 0;i < ROW; ++i)
    {
        for(int j = 0; j < COL; j++)
        {
            if (Map[i][j] == 1)
            {
               Map[i][j] = 0;
            }
        }
    }
}
void Reset_Map_Enemy(){
    for(int i = 0;i < ROW; ++i)
    {
        for(int j = 0; j < COL; j++)
        {
            if (Map[i][j] == 2)
            {
               Map[i][j] = 0;
            }
        }
    }
}
void SetPlayer(){
    int i_ = 0;
    int j_ = 0;
    for(int i = x; i < x + 4;++i)
    {
        for(int j = y; j < y + 3;++j)
        {
            if (Map[i][j] == 2)
            {
                Lose = true;
            }
            Map[i][j] = Player[i_][j_];
            j_ = (j_+ 1) % 3;
        }
        i_ = (i_ + 1) % 4;
    }
}
void SetEnemy(){
    int i_ = 0;
    int j_ = 0;
    for(int i = x_e; i < x_e + 4; ++i)
    {
        for(int j = y_e; j < y_e + 3; ++j)
        {
            if(i >= 0 && i < ROW && j > 0 && j < COL)
            {
                if (Map[i][j] == 1)
                {
                    Lose = true;
                }
                Map[i][j] = Enemy[i_][j_];
            }
            j_ = (j_ + 1) % 3;
        }
        i_ = (i_ + 1) % 4;
    } 
}
int main(){  
    SetUp();
    SetEnemy();
    SetPlayer();
    Draw_Map();
    while(true)
    {
        Time++;    
        if (Time >= Speed)
        {
            Time = 0;
            Reset_Map_Enemy();
            x_e++;
            SetEnemy();
            if (x_e >= ROW + 4)
            {
                x_e = -4;
                y_e = rand() % (COL - 5) + 1;
                Score+=10;
            }
            Draw_Map();
        }
        KeyBoard();
        if (KeyPress == 1)
        {
        Reset_Map_Player();
        SetPlayer();
        Draw_Map();
        KeyPress = 0;
        }
        if (Lose == true)
        {
            printf("Lose!!!\n");
            break;
        }
    }
    return 0;
}

