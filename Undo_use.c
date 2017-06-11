void undo_use() {             //undo_save 와 undo_use의 i는 공유되어야함


if (undocount < 5) {

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

  if (udsort<0) {
    udsort = udsort + 5;
   }

  undocount++;   //stage 별로 count 초기화
  }

}
