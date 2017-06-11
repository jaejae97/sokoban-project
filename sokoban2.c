#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <time.h>
#include <unistd.h>

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
/*nowx nowy 입력받는 함수*/
int nowx[10], nowy[10];
char a[10][30][30]={0};
char o[10][30][30];
char undo[5][30][30]={0};
int stage;
char name[11];
/*충돌체크+이동시켜주는 함수*/
int move_func(char direc) //nowx 와 nowy는 골뱅이의 처음 x좌표와 y좌표값이다.
{
   switch (direc)
   {
      case 'h' :
         if(a[stage][nowy[stage]][nowx[stage]-1]=='#')//왼쪽 이동시 벽이 있을 때
            nowx[stage]=nowx[stage];
         else if(a[stage][nowy[stage]][nowx[stage]-1]=='$')//왼쪽 이동시 달러가 있을 때
         {
            if(a[stage][nowy[stage]][nowx[stage]-2]!='$' && a[stage][nowy[stage]][nowx[stage]-2]!='#')//왼쪽에 달러,벽이 없으면 이동
            {
               a[stage][nowy[stage]][nowx[stage]-2]=a[stage][nowy[stage]][nowx[stage]-1];
               a[stage][nowy[stage]][nowx[stage]-1]=a[stage][nowy[stage]][nowx[stage]];
               nowx[stage]=nowx[stage]-1;
            }
         }
         else
            nowx[stage]=nowx[stage]-1;//왼쪽 이동시 벽,달러가 없을 때
         break;
      case 'j' :
         if(a[stage][nowy[stage]+1][nowx[stage]]=='#')//아래쪽 이동시 벽이 있을 때
            nowy[stage]=nowy[stage];
         else if(a[stage][nowy[stage]+1][nowx[stage]]=='$')//아래쪽 이동시 달러가 있을 때
            {
               if(a[stage][nowy[stage]+2][nowx[stage]]!='$' && a[stage][nowy[stage]+2][nowx[stage]]!='#')
               {
                  a[stage][nowy[stage]+2][nowx[stage]]=a[stage][nowy[stage]+1][nowx[stage]];
                  a[stage][nowy[stage]+1][nowx[stage]]=a[stage][nowy[stage]][nowx[stage]];
                  nowy[stage]=nowy[stage]+1;
               }
            }
         else
            nowy[stage]=nowy[stage]+1;//아래쪽 이동시 벽,달러가 없을 때
         break;
      case 'k' :
         if(a[stage][nowy[stage]-1][nowx[stage]]=='#')//위쪽 이동시 벽이 있을 때
            nowy[stage]=nowy[stage];
         else if(a[stage][nowy[stage]-1][nowx[stage]]=='$')//위쪽 이동시 달러가 있을 때
         {
            if(a[stage][nowy[stage]-2][nowx[stage]]!='$' && a[stage][nowy[stage]-2][nowx[stage]]!='#')
            {
               a[stage][nowy[stage]-2][nowx[stage]]=a[stage][nowy[stage]-1][nowx[stage]];
               a[stage][nowy[stage]-1][nowx[stage]]=a[stage][nowy[stage]][nowx[stage]];
               nowy[stage]=nowy[stage]-1;
            }
         }
         else
            nowy[stage]=nowy[stage]-1;//위쪽 이동시 벽,달러가 없을 때
         break;
      case 'l' :
         if(a[stage][nowy[stage]][nowx[stage]+1]=='#')//왼쪽 이동시 벽이 있을 때
            nowx[stage]=nowx[stage];
         else if(a[stage][nowy[stage]][nowx[stage]+1]=='$')//왼쪽 이동시 달러가 있을 때
         {
            if(a[stage][nowy[stage]][nowx[stage]+2]!='$' && a[stage][nowy[stage]][nowx[stage]+2]!='#')
            {
               a[stage][nowy[stage]][nowx[stage]+2]=a[stage][nowy[stage]][nowx[stage]+1];
               a[stage][nowy[stage]][nowx[stage]+1]=a[stage][nowy[stage]][nowx[stage]];
               nowx[stage]=nowx[stage]+1;
            }
         }
         else
            nowx[stage]=nowx[stage]+1;//왼쪽 이동시 벽,달러가 없을 때
         break;
   }
   return 0;
}
/* @가 움직임에 따라 맵을 계속 고쳐주는 함수 */
int updatemap()
{
   int  i, j; //i는 y좌표, j는 x좌표
   system("clear");
  printf("Hello %s\n", name);
         for (i=0;i<20;i++)
         {
            for (j=0;j<30;j++)
            {
               printf("%c",a[stage][i][j]);
            }
            printf("\n");
         }
      return 0;

}
int main(void)
{
  printf("Start....\n");
  printf("input name :");
  scanf("%s", name);

   char tmp;
   FILE *f;
   f = fopen("map1-5.txt", "r");
   int x,y;
   x=0;
   y=0;
   int i,j,k;
   for (k=1;k<6;k++)
   {
      for (i=0;i<20;i++)
      {
         for (j=0;j<30;j++)
         {
            o[k][i][j]=' ';
         }
      }
   }
   while(1)
   {
      fscanf(f, "%c", &tmp);
      if (tmp=='\n')
      {
      y++;
      x=0;
    }
      else if (tmp=='e')
         break;
      else if (tmp=='m')
      {
         stage++;
         x=0;
         y=0;
         fscanf(f,"%c",&tmp);
         fscanf(f,"%c",&tmp);
         fscanf(f,"%c",&tmp);
      }
      else if(tmp=='@')
      {
         nowx[stage]=x;
         nowy[stage]=y;
         a[stage][y][x]=tmp;
         x++;
      }
      else if(tmp=='O')
      {
         a[stage][y][x]=tmp;
         o[stage][y][x]=tmp;
         x++;
      }
      else
      {
      a[stage][y][x]=tmp;
      x++;
    }
   }
   printf("\n");
   stage=1;
   for (i=0;i<20;i++)
   {
      for (j=0;j<30;j++)
      {
         printf("%c",a[stage][i][j]);
      }
      printf("\n");
   }

   fclose(f);
/*tmp 재활용*/
while(!(a[1][7][19]=='$' && a[1][7][20]=='$' && a[1][8][19]=='$' && a[1][8][20]=='$' && a[1][9][19]=='$' && a[1][9][20]=='$'))
 {
    tmp=getch();
    a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
    move_func(tmp);
    a[stage][nowy[stage]][nowx[stage]]='@';
    updatemap();
 }
stage=2; //stage 1에서 stage 2로 변경
printf("Hello %s\n", name);
for (i=0;i<20;i++)
 {
    for (j=0;j<30;j++)
    {
       printf("%c",a[stage][i][j]);
    }
    printf("\n");
 }
 while(!(a[2][2][1]=='$' && a[2][2][2]=='$' && a[2][3][1]=='$' && a[2][3][2]=='$' && a[2][4][1]=='$' && a[2][4][2]=='$' && a[2][5][1]=='$' && a[2][5][2]=='$' && a[2][6][1]=='$' && a[2][6][2]=='$'))
   {
      tmp=getch();
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();
   }
  stage=3;
  printf("Hello %s\n", name);
  for (i=0;i<20;i++)
   {
      for (j=0;j<30;j++)
      {
         printf("%c",a[stage][i][j]);
      }
      printf("\n");

   }
   while(!(a[3][7][1]=='$' && a[3][7][2]=='$' && a[3][7][3]=='$' && a[3][7][4]=='$' && a[3][8][2]=='$' && a[3][8][3]=='$' && a[3][8][4]=='$' && a[3][9][1]=='$' && a[3][9][2]=='$' && a[3][9][3]=='$' && a[3][9][4]=='$'))
   {
      tmp=getch();
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();
   }
   stage=4;
   printf("Hello %s\n", name);
   for (i=0;i<20;i++)
   {
      for (j=0;j<30;j++)
      {
         printf("%c",a[stage][i][j]);
      }
      printf("\n");

   }
   while(!(a[4][2][17]=='$' && a[4][2][18]=='$' && a[4][2][19]=='$' && a[4][2][20]=='$' && a[4][3][17]=='$' && a[4][3][18]=='$' && a[4][3][19]=='$' && a[4][3][20]=='$' && a[4][4][17]=='$' && a[4][4][18]=='$' && a[4][4][19]=='$' && a[4][4][20]=='$' && a[4][5][17]=='$'&& a[4][5][18]=='$'&& a[4][5][19]=='$'&& a[4][5][20]=='$'&& a[4][6][17]=='$'&& a[4][6][18]=='$'&& a[4][6][19]=='$'&& a[4][6][20]=='$'))
   {
      tmp=getch();
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();
   }
   stage=5;
   printf("Hello %s\n", name);
   for (i=0;i<20;i++)
    {
       for (j=0;j<30;j++)
       {
          printf("%c",a[stage][i][j]);
       }
       printf("\n");

    }
    while(!(a[5][6][1]=='$' && a[5][6][2]=='$' && a[5][6][3]=='$' && a[5][6][4]=='$' && a[5][7][1]=='$' && a[5][7][2]=='$' && a[5][7][3]=='$' && a[5][7][4]=='$' && a[5][8][1]=='$' && a[5][8][2]=='$' && a[5][8][3]=='$' && a[5][8][4]=='$'))
    {
       tmp=getch();
       a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
       move_func(tmp);
       a[stage][nowy[stage]][nowx[stage]]='@';
       updatemap();
    }
}
