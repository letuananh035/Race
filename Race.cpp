#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <string.h>
#include <stdio_ext.h>
#include <time.h>
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
int Time_1 = 0;
int Time_2 = 0;
int x_e = 1;
int y_e = rand() % (ROW - 5) + 1;
int x_e_1 = -5;
int y_e_1 = rand() % (ROW - 5) + 1;
bool Enemy_1_Exit = false;
int x = 14;
int y = 2;
int KeyPress = 0;
bool Lose = false;
int Score = 0;
int Lv = 1;
int Menu = 1;
void SetUp(){
    
    strcpy(Tile[0],"*  *  *  *  *  *  *");
    strcpy(Tile[1],"* Score:   0      *");
    strcpy(Tile[2],"* Lv: 1           *");
    strcpy(Tile[3],"*  *  *  *  *  *  *");
    for(int i = 4;i < ROW; ++i)
    {
        strcpy(Tile[i], "                   ");
    }
    Speed = 50000;
    Time = 0;
    Time_1 = 0;
    Time_2 = 0;
    x_e = 1;    
    y_e = rand() % (ROW - 5) + 1;
    x_e_1 = -5;
    y_e_1 = rand() % (ROW - 5) + 1;
     Enemy_1_Exit = false;
    x = 14;
    y = 2;
    KeyPress = 0;
    Lose = false;
    Score = 0;
    Lv = 1;
    Menu = 1;
    for(int i = 0; i < ROW; i++)
    {
        for(int j =0; j < COL; j++)
            {
                Map[i][j] = 0;
            }
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
                if (y - 1 >= 1)
                {
                    y--;
                }
                KeyPress = 1;
            }
            break;
            case 'd':
            {
                if (y + 1 < COL - 3)
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
            if(i >= 0 && i < ROW && j >= 0 && j < COL)
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
    i_ = 0;
    j_ = 0; 
    for(int i = x_e_1; i < x_e_1 + 4; ++i)
    {
        for(int j = y_e_1; j < y_e_1 + 3; ++j)
        {
            if(i >=0 && i < ROW && j >=0 && j < COL)
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
void Draw_Menu(){
    system("clear");
    printf("===============Game Race===============\n");
    if (Menu == 1)
    {
        printf("=            >>> Start <<<            =\n");
    }
    else
    {
        printf("=                Start                =\n");
    }
    if (Menu == 2)
    {
        printf("=         >>> Information <<<         =\n");
    }
    else
    {
        printf("=             Information             =\n");
    }
    if (Menu == 3)
    {
        printf("=           >>>  Exit <<<             =\n");
    }
    else
    {
        printf("=                Exit                 =\n");
    }
    printf("=======================================\n");
}
void Infor(){
    system("clear");
    printf("===============Information==============\n");
    printf("=               Game Race              =\n");
    printf("=             Make by C/C++            =\n");
    printf("=           Coder: Le Tuan Anh         =\n");
    printf("=         Using A,W,S,D move car       =\n");
    printf("========================================\n");
    printf("Press any key continue menu!!!\n");
    getch();
}

int KeyBoardMenu(){
    while(true)
    {
        if (kbhit())
        {
            int ch = getch();
            switch(ch)
            {
                case 'w':
                {
                    if (Menu - 1 >= 1)
                    {
                        Menu--;
                        Draw_Menu();
                    }
                }
                break;   
                case 's':
                {
                    if (Menu + 1 <= 3)
                    {
                        Menu++;
                        Draw_Menu();
                    }
                }
                break;
                case 'x':
                {
                    if(Menu == 1)
                    {
                        return 0;
                    }
                    else if(Menu == 2)
                        {
                            Infor(); 
                            Draw_Menu();
                            break;
                        }
                        else
                        {
                            return 0;
                        }
                }
                break;
            }
        }
    }
    return 0;
}
int main(){  
    Menu:
    SetUp();
    Draw_Menu();
    KeyBoardMenu();
    if(Menu == 3)
    {
        return 0;
    }
    SetEnemy();
    SetPlayer();
    Draw_Map();
    while(true)
    {
        Time++;    
        Time_1++;
        if (Score >= Lv * 50)
        {
            Lv++;
            Speed -= 5000;
        }
        if (Time >= Speed)
        {
            Time = 0;
            Reset_Map_Enemy();
            x_e++;
            SetEnemy();
            if (x_e >= ROW + 4)
            {
                x_e = -4;
                srand(time(NULL));
                y_e = rand() % (COL - 5) + 1;
                Score+=10;
            }
            Draw_Map();
        }

        if( Time_1 >= Speed * 6)
        {
            Enemy_1_Exit = true;
            SetEnemy();
            Draw_Map();
            Time_1 = 0;
        }
        if(Time_1 >= Speed && Enemy_1_Exit == true)
        {
            Time_1 = 0;
            Reset_Map_Enemy();
            x_e_1++;
            SetEnemy();
            if(x_e_1 >= ROW + 4)
            {
                x_e_1 = -4;
                srand(time(NULL));
                y_e_1 = rand() % (COL - 5) + 1;
                Score += 10;
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
            printf("Press any key continue menu!!!");
            getch();
            goto Menu;
        }
    }
    Exit:
    return 0;
}
