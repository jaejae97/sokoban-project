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
      option();
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
        option();
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
        option();
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
        option();
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
         option();
         a[stage][nowy[stage]][nowx[stage]]=o[stage][nowy[stage]][nowx[stage]];
         move_func(tmp);
         a[stage][nowy[stage]][nowx[stage]]='@';
         updatemap();

      }

}
