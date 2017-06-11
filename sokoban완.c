#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <time.h>
#include <unistd.h>

int nowx[6], nowy[6];
char tmp;
char a[6][30][30]={0};
char o[6][30][30];
char undo[5][30][30]={0};
char r_map[6][30][30]={0};
int stage;
int savestage;
int o_number[6]={0};
int box_number[6]={0};
char enter;
char name[11];
int undocount=0;
int udsort;  //udsort는 undo[udsort][][]의 3차원 배열 변수이다


int getch(); // 키보드 입력값을 버퍼에 출력하지 않게하는 함수
void updatemap();
void save();
void undo_save();
void undo_use();
void move_func(char);
void option_func(char);
void open_file();
void display();
void new();
/**********stage 별 맵 함수********/
void first();
void second();
void third();
void fourth();
void fifth();

int main(void)
{
  printf("Start....\n");
  printf("input name :");
  scanf("%s", name);

  open_file();

  if (box_number[stage]!=o_number[stage])
  {
    printf("삐빗!! 박스 개수와 보관장소 개수가 다릅니다..프로그램을 종료합니다.");
    return 0;
  }

  printf("\n");

  stage=1;
  if (stage==1)
     {
       first();
       stage++;
     }
     if (stage==2)
     {
       second();
       stage++;
     }
     if (stage==3)
     {
       third();
       stage++;
     }
     if (stage==4)
     {
       fourth();
       stage++;
     }
     if (stage==5)
     {
       fifth();
       stage++;
     }
}

void first() // map1 합수
{
  int i,j;
  for (i=0;i<20;i++)
  {
     for (j=0;j<30;j++)
     {
        printf("%c",a[stage][i][j]);
     }
     printf("\n");
  }
   while(!(a[1][7][19]=='$' && a[1][7][20]=='$' && a[1][8][19]=='$' && a[1][8][20]=='$' && a[1][9][19]=='$' && a[1][9][20]=='$')) // 박스가 보관장소에 다들어갈 때까지 반복, 배열들은 보관장소의 좌표
   {
      tmp=getch();
      if (tmp=='h'||tmp=='j'||tmp=='k'||tmp=='l') {
        undo_save();
      }
      option_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
      move_func(tmp);
      a[stage][nowy[stage]][nowx[stage]]='@';
      updatemap();


   }
}

void second() // map2 합수
{
  int i,j;
  printf("Hello %s\n", name);
  for (i=0;i<20;i++)
   {
      for (j=0;j<30;j++)
      {
         printf("%c",a[stage][i][j]);
      }
      printf("\n");
   }
   undocount=0; // undo 횟수 초기화
   while(!(a[2][2][1]=='$' && a[2][2][2]=='$' && a[2][3][1]=='$' && a[2][3][2]=='$' && a[2][4][1]=='$' && a[2][4][2]=='$' && a[2][5][1]=='$' && a[2][5][2]=='$' && a[2][6][1]=='$' && a[2][6][2]=='$')) // 박스가 보관장소에 다들어갈 때까지 반복, 배열들은 보관장소의 좌표
     {

        tmp=getch();
        if (tmp=='h'||tmp=='j'||tmp=='k'||tmp=='l') {
          undo_save();
        }
        option_func(tmp);
        a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
        move_func(tmp);
        a[stage][nowy[stage]][nowx[stage]]='@';
        updatemap();

     }
 }

void third() //map3 함수
{
  int i,j;
    printf("Hello %s\n", name);
    for (i=0;i<20;i++)
     {
        for (j=0;j<30;j++)
        {
           printf("%c",a[stage][i][j]);
        }
        printf("\n");

     }
     undocount=0;
     while(!(a[3][7][1]=='$' && a[3][7][2]=='$' && a[3][7][3]=='$' && a[3][7][4]=='$' && a[3][8][2]=='$' && a[3][8][3]=='$' && a[3][8][4]=='$' && a[3][9][1]=='$' && a[3][9][2]=='$' && a[3][9][3]=='$' && a[3][9][4]=='$')) // 박스가 보관장소에 다들어갈 때까지 반복, 배열들은 보관장소의 좌표
     {

        tmp=getch();
        if (tmp=='h'||tmp=='j'||tmp=='k'||tmp=='l') {
          undo_save();
        }
        option_func(tmp);
        a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
        move_func(tmp);
        a[stage][nowy[stage]][nowx[stage]]='@';
        updatemap();

     }
}

void fourth() //map4 함수
{
  int i,j;
     printf("Hello %s\n", name);
     for (i=0;i<20;i++)
     {
        for (j=0;j<30;j++)
        {
           printf("%c",a[stage][i][j]);
        }
        printf("\n");

     }
     undocount=0;
     while(!(a[4][2][17]=='$' && a[4][2][18]=='$' && a[4][2][19]=='$' && a[4][2][20]=='$' && a[4][3][17]=='$' && a[4][3][18]=='$' && a[4][3][19]=='$' && a[4][3][20]=='$' && a[4][4][17]=='$' && a[4][4][18]=='$' && a[4][4][19]=='$' && a[4][4][20]=='$' && a[4][5][17]=='$'&& a[4][5][18]=='$'&& a[4][5][19]=='$'&& a[4][5][20]=='$'&& a[4][6][17]=='$'&& a[4][6][18]=='$'&& a[4][6][19]=='$'&& a[4][6][20]=='$')) // 박스가 보관장소에 다들어갈 때까지 반복, 배열들은 보관장소의 좌표
     {

        tmp=getch();
        if (tmp=='h'||tmp=='j'||tmp=='k'||tmp=='l') {
          undo_save();
        }
        option_func(tmp);
        a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
        move_func(tmp);
        a[stage][nowy[stage]][nowx[stage]]='@';
        updatemap();

     }
}

void fifth() //map5 함수
{
  int i,j;
     printf("Hello %s\n", name);
     for (i=0;i<20;i++)
      {
         for (j=0;j<30;j++)
         {
            printf("%c",a[stage][i][j]);
         }
         printf("\n");

      }
      undocount=0;
      while(!(a[5][6][1]=='$' && a[5][6][2]=='$' && a[5][6][3]=='$' && a[5][6][4]=='$' && a[5][7][1]=='$' && a[5][7][2]=='$' && a[5][7][3]=='$' && a[5][7][4]=='$' && a[5][8][1]=='$' && a[5][8][2]=='$' && a[5][8][3]=='$' && a[5][8][4]=='$')) // 박스가 보관장소에 다들어갈 때까지 반복, 배열들은 보관장소의 좌표
      {

         tmp=getch();
         if (tmp=='h'||tmp=='j'||tmp=='k'||tmp=='l') {
           undo_save();
         }
         option_func(tmp);
         a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
         move_func(tmp);
         a[stage][nowy[stage]][nowx[stage]]='@';
         updatemap();

      }

}


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

void option_func(char input)
{
  switch (input)
  {
    case 'u' :
       undo_use();
       printf("%c\n", input);
       sleep(1);
       break;

    case 'r' :
       break;

    case 'n' :
       new();
       break;

    case 'e' :
       save();
       system("clear");
       printf("SEE YOU %s....\n", name);
       printf("\n\n (Command) %c\n", input);
       sleep(1);
       exit(1);

    case 's' :
       save();
       printf("%c\n", input);
       sleep(1);
       break;

    case 'f' :
       break;

    case 'd' :
       display();
       break;

    case 't' :
       break;
  }
}

void display()
{
  system("clear");
  printf("Hello %s\n\n\n", name);
  printf("h(왼쪽), j(아래), k(위), l(오른쪽)\n");
  printf("u(undo)\n");
  printf("r(replay)\n");
  printf("n(new)\n");
  printf("e(exit)\n");
  printf("s(save)\n");
  printf("f(file load)\n");
  printf("d(display help)\n");
  printf("t(top)\n");
  printf("\n\n\n\n\n\n\n\n\n(Command) d\n");
  sleep(2);
  return;
}


/*충돌체크+이동시켜주는 함수*/
void move_func(char direc) //nowx 와 nowy는 골뱅이의 처음 x좌표와 y좌표값이다.
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
}


/**************************undo에 save하는 배열 함수**************************/
void undo_save()
{
    int j, k;

for ( j = 0; j < 20; j++) {
  for ( k = 0; k < 30; k++) {
    undo[udsort][j][k]=a[stage][j][k]; //현재 맵 배열을 undo 3차원배열에 저장
  }
}

udsort++; // 0~ 4 까지의 3차원 배열에 차례대로 이전 맵 배열을 저장

if (udsort>=5) {
  udsort = 0;         // undo 3차원 배열이 5까지니까 5를 넘어가면 다시 [0][j][k] 부터 저장
}

}

/* @가 움직임에 따라 맵을 계속 고쳐주는 함수 */
void updatemap()
{
   int  i, j; //i는 y좌표, j는 x좌표
   system("clear");
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
      printf("(Command) ");
}

/*맵 세이브 함수*/
/*현재 맵을 sokoban.txt에 저장*/
void save()
{
   int i, j,k;
   savestage=stage;
   FILE *m;
      m=fopen("sokoban.txt", "w");

      for (k=1;k<6;k++)
         {
           fprintf(m, "map\n");
           for(i=0; i<20; i++)
          {
            for(j=0; j<30; j++)
            {
               fprintf(m, "%c", a[k][i][j]);
            }
         }
        }
        fprintf(m,"end");
      fclose(m);
}

/*******************undo_use 함수 시작***********************/

void undo_use() {             //undo_save 와 undo_use의 i는 공유되어야함


if (undocount < 5) {

  if (udsort<0) {
    udsort = udsort + 5;
   }

  for (int j = 0; j < 20; j++) {
    for (int k = 0; k < 30; k++) {
      a[stage][j][k]=undo[udsort-1][j][k]; //이전 배열 저장
     }
   }

  updatemap();  // 이전 배열 출력

  for (int j = 0; j < 20; j++) {            // 이전 배열의 @ 위치를 기억
    for (int k = 0; k < 30; k++) {
      if (a[stage][j][k]=='@') {
        nowx[stage]=k;
        nowy[stage]=j;
      }
    }
  }
  udsort--;
  undocount++;   //stage 별로 count 초기화
  }

}

/************************undo_use 함수 끝*****************************/

void open_file()
{
   FILE *f;
   f = fopen("map1-5.txt", "r");
   int x,y;
   x=0;
   y=0;
   for (int k=1;k<6;k++)
   {
      for (int i=0;i<20;i++)
      {
         for (int j=0;j<30;j++)
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
         o_number[stage]++;
      }
      else if (tmp=='$')
      {
      a[stage][y][x]=tmp;
      x++;
      box_number[stage]++;
      }
      else
      {
      a[stage][y][x]=tmp;
      x++;
    }

   }
   fclose(f);

   for (int i = 1; i < 6; i++) {
     for (int j = 0; j < 20; j++) {
       for (int k = 0; k < 30; k++) {
         r_map[i][j][k]=a[i][j][k];
         if (a[i][j][k]=='@')
           base_man[i][j][k]=a[i][j][k];
       }
     }
    }

 }

 void new()
 {
   int  i, j; //i는 y좌표, j는 x좌표
   stage=1;
   system("clear");
  system("clear");
  printf("Hello %s\n", name);
         for (i=0;i<20;i++)
         {
            for (j=0;j<30;j++)
            {
               printf("%c",r_map[stage][i][j]);
            }
         }
      printf("(Command) ");

      for (i=0;i<20;i++)
      {
         for (j=0;j<30;j++)
         {
           a[stage][i][j]=r_map[stage][i][j];
         }
      }
 }
