#include <stdio.h>
char undo[5][30][30]={0}; //전역변수

if (c=='h'||c=='j'||c=='k'||c=='l') {
  undo_save();
  move_func();
}

void undo_save()
{
  if (undocount==0) {
    int i=0;
  } else {
    // undo_use에 의해 바뀐 변수 i 를 선언
  }

for ( j = 0; j < 30; j++) {
  for ( k = 0; k < 30; k++) {
    undo[i][j][k]=a[stage][j][k]; //현재 맵 배열을 undo 3차원배열에 저장
  }
}

i++; // 0~ 4 까지의 3차원 배열에 차례대로 이전 맵 배열을 저장

if (i>=5) {
  i = i%5;         // undo 3차원 배열이 5까지니까 5를 넘어가면 다시 [0][j][k] 부터 저장
}

}
