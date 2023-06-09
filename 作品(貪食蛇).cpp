#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define speed 500 
void print();
void goto_xy(int x, int y);
void set();
void move();
void getch_noblock();
void food();
void printmap();
void check_hit_body();
typedef struct {
    int x,y;
}node;

node snake[10000];

const int M=20,N=20;
int snakebody[40][30]={0},bodylong=10,x=(M/4)*2,y=(N/4)*2,checkfood=0,foodx ,foody,tail=0,keycheck=0,foodconfirmX=0,foodconfirmY=0,score=0;
char keyboard=72;
int r;
int main(){
	print();
	system("cls");
    SetConsoleOutputCP(437);
    printmap();
    set();
    while(keyboard!=27){
        food();
        getch_noblock();
        move();
        check_hit_body();
        Sleep(speed);
    }
    goto_xy(M*2+13,8);
    SetConsoleOutputCP(950);
    printf("遊戲結束");
    Sleep(speed);
    return 0;
}
void print()
{
	printf("\t歡迎來到貪食蛇小遊戲\n");
	printf("\n遊戲規則:\n");
	printf("\n->用方向鍵移動\n");
	printf("\n->食物會隨機生成在範圍內任意區域\n");
	printf("\n->每吃一個身體長會增加一格\n");
	printf("\n\n按任意件開始遊戲....\n");
	getch();
}
 void goto_xy(int x, int y)
 {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

void set(){
    for(int i=0;i<bodylong;i++){
        snake[i].x=x+i;
        r=x;
        snake[i].y=y;
        goto_xy(snake[i].x,snake[i].y);
        printf("%c",254);
    }

}
void move(){
    int p=0;
    node body;
    node pre;
       while(p!=bodylong){
        if(p==0){
            pre.x=snake[p].x;
            pre.y=snake[p].y;
            if(keyboard==72){
                snake[p].y--;
                if(snake[0].y==0)keyboard=27;
                goto_xy(snake[p].x,snake[p].y);
                printf("%c",254);
                p++;
            }else if(keyboard==75){
                snake[p].x-=2;
                if(snake[0].x==0)keyboard=27;
                goto_xy(snake[p].x,snake[p].y);
                printf("%c",254);
                p++;
            }else if(keyboard==80){
                snake[p].y++;
                if(snake[0].y==N+1)keyboard=27;
                goto_xy(snake[p].x,snake[p].y);
                printf("%c",254);
                p++;
            }else if(keyboard==77){
                snake[p].x+=2;
                if(snake[0].x==M*2+2)keyboard=27;
                goto_xy(snake[p].x,snake[p].y);
                printf("%c",254);
                p++;
            }
        }else {
            goto_xy(pre.x,pre.y);
            printf("%c",254);
            body.x=snake[p].x;
            body.y=snake[p].y;
            snake[p].x=pre.x;
            snake[p].y=pre.y;
            pre.x=body.x;
            pre.y=body.y;
            if(p==bodylong-1){
                goto_xy(pre.x,pre.y);
                printf("  ");
            }
            p++;
            if(p==bodylong && snake[0].x==foodconfirmX && snake[0].y==foodconfirmY){
                snake[p].x=pre.x;
                snake[p].y=pre.y;
                score++;
                goto_xy(M*2+23,7);
                SetConsoleOutputCP(950);
                printf("%d",score);
                SetConsoleOutputCP(437);
                goto_xy(snake[p].x, snake[p].y);
                bodylong++;
                printf("%c",254);
                checkfood=0;
                break;
            }

        }

    }
}
int b=72;
void getch_noblock(){
    if(kbhit()){
        char a=getch();
        switch(a){
            case -32:
            a=getch();
            switch(a){
                case 72:
                    if(b==80)break;
                    b=a;
                    keyboard=a;break;
                case 80:
                    if(b==72)break;
                    b=a;
                    keyboard=a;break;
                case 75:
                    if(b==77)break;
                    b=a;
                    keyboard=a;break;
                case 77:
                    if(b==75)break;
                    b=a;
                    keyboard=a;break;
                default :break;
            }
        default :break;
        }
        if(a==27){
            keyboard=a;
        }
    }
}
void food(){
    if(checkfood==0){
        bool inbody=false;
        srand(time(0));
        foodx=2+(rand()%M)*2;
        foody=1+rand()%N;
        for(int i=0;i<bodylong;i++){
            if(foody==snake[i].y && foodx==snake[i].x){
                inbody=true;
            }
        }
        if(inbody==false){
            goto_xy(foodx,foody);
            printf("%c",234);
            checkfood=1;
            foodconfirmX=foodx;
            foodconfirmY=foody;
        }
    }
}
void printmap(){

    for(int t=0;t<=M+1;t++){
        if(t==0)printf("%c%c",201,205);
        else if(t==M+1)printf("%c",187);
        else printf("%c%c",205,205);
    }
    printf("\n");
    for(int e=1;e<=N;e++){
        for(int t=0;t<=M+1;t++){
            if(t==0){printf("%c ",186);}
            else if(t==M+1){printf("%c",186);}
            else {printf("  ");}
        }
        if(e==7){
            for(int k=0;k<5;k++){
                    printf("  ");
            }
            SetConsoleOutputCP(950);
            printf("你的分數: ");
            printf("%d",score);
            SetConsoleOutputCP(437);
        }
        printf("\n");
    }
    for(int t=0;t<=M+1;t++){
        if(t==0)printf("%c%c",200,205);
        else if(t==M+1)printf("%c",188);
        else printf("%c%c",205,205);
    }
}

void check_hit_body(){
    for(int a=1;a<bodylong;a++){
            if(snake[0].x==snake[a].x && snake[0].y==snake[a].y){
                keyboard=27;
            }
        }
}
