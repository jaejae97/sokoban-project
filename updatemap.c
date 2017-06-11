int updatemap()
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


      return 0;
}
