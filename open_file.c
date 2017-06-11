void open_file()
{
   FILE *f;
   f = fopen("map1-5.txt", "r"); //파일 열기
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
      fscanf(f, "%c", &tmp); // tmp로 파일 확인
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
