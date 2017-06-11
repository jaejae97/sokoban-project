/*우선적으로 해야할것 목록
O안에 달러가 다 들어가면 스테이지 바뀌는 것 
옵션*/ 
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
/*nowx nowy 입력받는 함수*/
int nowx[10], nowy[10];
char a[10][30][30]={0};
char o[10][30][30];
int stage;
/*충돌체크+이동시켜주는 함수*/
int move_func(char direc) //nowx 와 nowy는 골뱅이의 처음  x좌표와 y좌표값이다. 
{   
   switch (direc)
   {
      case 'h' :
         if(a[stage][nowy[stage]][nowx[stage]-1]=='#')
            nowx[stage]=nowx[stage];
         else if(a[stage][nowy[stage]][nowx[stage]-1]=='$')
         {
            if(a[stage][nowy[stage]][nowx[stage]-2]!='$' && a[stage][nowy[stage]][nowx[stage]-2]!='#')
            {
               a[stage][nowy[stage]][nowx[stage]-2]=a[stage][nowy[stage]][nowx[stage]-1];
               a[stage][nowy[stage]][nowx[stage]-1]=a[stage][nowy[stage]][nowx[stage]];
               nowx[stage]=nowx[stage]-1;
            }
         }
         else      
            nowx[stage]=nowx[stage]-1;
         break;
      case 'j' :
         if(a[stage][nowy[stage]+1][nowx[stage]]=='#')
            nowy[stage]=nowy[stage];   
         else if(a[stage][nowy[stage]+1][nowx[stage]]=='$')
            {
               if(a[stage][nowy[stage]+2][nowx[stage]]!='$' && a[stage][nowy[stage]+2][nowx[stage]]!='#')
               {
                  a[stage][nowy[stage]+2][nowx[stage]]=a[stage][nowy[stage]+1][nowx[stage]];
                  a[stage][nowy[stage]+1][nowx[stage]]=a[stage][nowy[stage]][nowx[stage]];
                  nowy[stage]=nowy[stage]+1;
               }
            }
         else
            nowy[stage]=nowy[stage]+1;
         break;
      case 'k' :
         if(a[stage][nowy[stage]-1][nowx[stage]]=='#')
            nowy[stage]=nowy[stage]; 
         else if(a[stage][nowy[stage]-1][nowx[stage]]=='$')
         {
            if(a[stage][nowy[stage]-2][nowx[stage]]!='$' && a[stage][nowy[stage]-2][nowx[stage]]!='#')
            {
               a[stage][nowy[stage]-2][nowx[stage]]=a[stage][nowy[stage]-1][nowx[stage]];
               a[stage][nowy[stage]-1][nowx[stage]]=a[stage][nowy[stage]][nowx[stage]];
               nowy[stage]=nowy[stage]-1;
            }
         }
         else
            nowy[stage]=nowy[stage]-1;
         break;
      case 'l' :
         if(a[stage][nowy[stage]][nowx[stage]+1]=='#')
            nowx[stage]=nowx[stage];
         else if(a[stage][nowy[stage]][nowx[stage]+1]=='$')
         {   
            if(a[stage][nowy[stage]][nowx[stage]+2]!='$' && a[stage][nowy[stage]][nowx[stage]+2]!='#')
            {
               a[stage][nowy[stage]][nowx[stage]+2]=a[stage][nowy[stage]][nowx[stage]+1];
               a[stage][nowy[stage]][nowx[stage]+1]=a[stage][nowy[stage]][nowx[stage]];
               nowx[stage]=nowx[stage]+1;
            }
         }
         else
            nowx[stage]=nowx[stage]+1;
         break;
         
   }
   return 0;
}
/* @가 움직임에 따라 맵을 계속 고쳐주는 함수 */   
int updatemap()
{   
   int  i, j; //i는 y좌표, j는 x좌표 
   system("cls");
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
      {y++;x=0;}
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
      {a[stage][y][x]=tmp;x++;}    
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
/*O가 $로 모두 바뀌었을 때 stage1 에서 stage2로 넘어가게 하는 코드를 짜야한다.*/
   while(!(a[1][6][19]=='$' && a[1][6][20]=='$' && a[1][7][19]=='$' && a[1][7][20]=='$' && a[1][8][19]=='$' && a[1][8][20]=='$'))
   {
      tmp=getch();
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();
      
   }   
   stage=2; //stage 1에서 stage 2로 변경 
   for (i=0;i<20;i++)
   {   
      for (j=0;j<30;j++)
      {
         printf("%c",a[stage][i][j]);
      }
      printf("\n");
   } 
   while(!(a[2][1][1]=='$' && a[2][1][2]=='$' && a[2][2][1]=='$' && a[2][2][2]=='$' && a[2][3][1]=='$' && a[2][3][2]=='$' && a[2][4][1]=='$' && a[2][4][2]=='$' && a[2][5][1]=='$' && a[2][5][2]=='$'))
   {
      tmp=getch();
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();
   }
   stage=3;
   for (i=0;i<20;i++)
   {   
      for (j=0;j<30;j++)
      {
         printf("%c",a[stage][i][j]);
      }
      printf("\n");
   
   }
   while(1)
   {
      tmp=getch();
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();
   }
}
