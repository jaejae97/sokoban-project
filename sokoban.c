#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <string.h>
#include <unistd.h>

int nowx[6], nowy[6]; // 스테이지 마다 골뱅이의 위치가 있는데, 그 위치의 x, y좌표를 저장한 배열
int stop; // 너무 길어서 코드로 이해해주세요.
char tmp; // 문자들을 잠깐 저장하기 위해 만든 변수
char a[6][30][30]={0}; // 전체 맵 배열
char o[6][30][30]; //O만을 저장한 맵 배열
char undo[5][30][30]={0}; // 언두 맵 배열
int stage; // 3차원 배열로 설정되어 있는 맵 배열이 [a][][]와 같다면 a 위치가 스테이지가 저장되는 위치이다.
int savestage; //  save할 때 현재 스테이지가 저장되는 변수
int o_number[6]={0}; //보관 장소 개수
int box_number[6]={0}; //박스 개수
char base_map[6][30][30]={0};  //초기 맵배열 저장 배열
int base_nowx[6], base_nowy[6]; //초기 @위치 저장 배열
char name[11]; //플레이어 이름
int undocount=0; //undo를 사용한 횟수를 저장하는 변수이다.
int udsort;  //udsort는 undo[udsort][][]의 3차원 배열 변수이다


int getch(); // 키보드 입력값을 버퍼에 출력하지 않게하는 함수
void updatemap(); //맵에 변경사항이 생길 때 마다 맵을 새로 출력해주는 함수
void save(); //현재 맵 상태를 저장해주는 함수
void undo_save(); //
void undo_use(); //
void move_func(char); //게임 룰을 지키면서 창고지기가 이동하도록 하는 함수
void option_func(char); //키가 입력됨에 따라 옵션을 실행 시켜주는 함수
void open_file(); //게임을 시작할 때 맵을 불러와주는 함수
void display(); //게임 실행에 필요한 명령들을 출력시켜주는 함수
void load(); //save 에서 저장한 맵 상태를 불러와주는 함수
void replay();// 옵션 replay를 실행하는 함수 + new 옵션 추가
/**********stage 별 맵 함수********/
void first(); //맵1를 플레이할 때 실행되는 함수
void second(); //맵2를 플레이할 때 실행되는 함수
void third(); //맵3를 플레이할 때 실행되는 함수
void fourth(); //맵4를 플레이할 때 실행되는 함수
void fifth(); //맵5를 플레이할 때 실행되는 함수

int main(void)
{
   int check;


  do // 처음 시작 + 이름 입력
  {
    system("clear");
    printf("Start....\n");
    printf("input name : ");
    check=0; // 반복문 탈출을 위한 변수
    scanf("%s",name); //  문자열 받기

    for (int i=0;i<strlen(name);i++) // 문자열 하나씩 영문자인지 체크, 영문자가 아닐 때 다시 이름을 입력
    {
      if(!(((name[i]>='a')&&(name[i]<='z'))||((name[i]>='A')&&(name[i]<='Z'))))
      {
        check=1;
        system("clear");
        printf("이름을 다시 입력하세요.\n");
        sleep(1);
        break;
      }
    }

    if (strlen(name)>10) // 문자열이 10자 이상일 때 다시 이름을 입력
    {
     check=1;
     system("clear");
     printf("이름을 다시 입력하세요.\n");
     sleep(1);
    }
  } while(check!=0) ;

  open_file();

  if (box_number[stage]!=o_number[stage])
  {
    printf("삐빗!! 박스 개수와 보관장소 개수가 다릅니다..프로그램을 종료합니다.");
    return 0;
  }

  printf("\n");

  stage=1;

  do
  {
      stop=0;

      if (stage==1 && stop==0)
     {
       first();
       if (stop==0)
          stage++;
     }
     if (stage==2 && stop==0)
     {
       second();
       if (stop==0)
          stage++;
     }
     if (stage==3 && stop==0)
     {
       third();
       if (stop==0)
          stage++;
     }
     if (stage==4 && stop==0)
     {
       fourth();
       if (stop==0)
          stage++;
     }
     if (stage==5 && stop==0)
     {
       fifth();
       if (stop==0)
          stage++;
     }
  }
  while (stage<6);
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
       replay();
       printf("%c\n", input);
       sleep(1);
       break;

    case 'n' :
       stage=1;
       replay();
       printf("%c\n", input);
       sleep(1);
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
       load();
       stop=1;
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
            if(a[stage][nowy[stage]][nowx[stage]-2]!='$' && a[stage][nowy[stage]][nowx[stage]-2]!='#')//왼쪽에 달러,벽이 없으면 x좌표 변경
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
               if(a[stage][nowy[stage]+2][nowx[stage]]!='$' && a[stage][nowy[stage]+2][nowx[stage]]!='#')//아래쪽에 달러,벽이 없으면 y좌표 변경
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
            if(a[stage][nowy[stage]-2][nowx[stage]]!='$' && a[stage][nowy[stage]-2][nowx[stage]]!='#')// 위쪽 이동시 달러,벽이 없으면 y좌표 변경
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
            if(a[stage][nowy[stage]][nowx[stage]+2]!='$' && a[stage][nowy[stage]][nowx[stage]+2]!='#')// 왼쪽 이동시 달러,벽이 없으면 x좌표 변경
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

   fprintf(m,"%d %d %d %d\n",savestage,undocount,nowx[stage],nowy[stage]);

    for(i=0; i<20; i++)
    {
        for(j=0; j<30; j++)
        {
            fprintf(m, "%c", a[stage][i][j]);
        }
    }
    fprintf(m,"e\n");

    for (k=0;k<5;k++)
   {
      for (i=0;i<20;i++)
      {
         for (j=0;j<30;j++)
         {
            fprintf(m,"%c",undo[k][i][j]);
         }
      }
      fprintf(m,"e\n");
   }

    fclose(m);
}

void load() //save한 맵을 불러오는 함수
{
   FILE *m; // savefile 열기

   int i,j,k;
   int x,y;
   m=fopen("sokoban.txt","r");
   char tmp;
   fscanf(m,"%d %d %d %d",&stage,&undocount,&x,&y);
   nowx[stage]=x;
   nowy[stage]=y;

   fscanf(m,"%c",&tmp);

   x=0;
   y=0;
      while(1)
   {
      fscanf(m,"%c",&tmp);

      if (tmp=='\n')
      {
         y++;
         x=0;
      }
      else if (tmp=='e')
      {
         break;
      }
      else
      {
         a[stage][y][x]=tmp;
         x++;
      }
    }

      while(1)
   {
      fscanf(m,"%c",&tmp);

      if (tmp=='\n')
      {
         y++;
         x=0;
      }
      else if (tmp=='e')
      {
         k++;
         x=0;
         y=0;
         break;
      }
      else
      {
         undo[k][y][x]=tmp;
         x++;
      }
    }


   fclose(m);
   stop=1;
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


/****************************replay 함수*******************************/
void replay()
{
  int i, j, k;
  nowx[stage]=base_nowx[stage]; //초기 설정된 @배열 위치를
  nowy[stage]=base_nowy[stage]; //현재 @배열 위치 덮어씌우기
  for (i = 1; i < 6; i++) {
    for (j = 0; j < 20; j++) {
      for (k = 0; k < 30; k++) {
        a[i][j][k]=base_map[i][j][k]; // 초기 맵 배열을 현재 맵 배열에 덮어씌우기
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 20; j++) {
      for (int k = 0; k < 30; k++) {
        undo[i][j][k]='\0';  // 언두 배열을 null으로 초기화
      }
    }
  }
  undocount=0; // 언두카운트 초기화 = 언두를 5번 다시 쓸 수 있다

}



void open_file() // 파일 여는 함수
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
       if (stop==1)
             break;
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
           if (stop==1)
             break;
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
         if (stop==1)
             break;
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
         if (stop==1)
             break;
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
          if (stop==1)
             break;
          a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
          move_func(tmp);
          a[stage][nowy[stage]][nowx[stage]]='@';
          updatemap();

       }
  }
