#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <time.h>
#include <unistd.h>
void first();
void second();
void third();
void fourth();
void fifth();
int nowx[10], nowy[10];
char a[10][30][30]={0};
char o[10][30][30];
char undo[5][30][30]={0};
int stage,savestage;
char word;
char tmp;
char name[11];
int undocount=0;
int udsort=0;  //udsort는 undo[udsort][][]의 3차원 배열 변수이다

 int getch(void)
 {
    int ch;
    struct termios buf;
    struct termios save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag&=~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;

 }
