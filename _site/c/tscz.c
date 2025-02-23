#include <stdio.h>
#include <string.h>
int main() {
  int n,i;
  scanf("%d",&n);
  char book[n][10],search[10];
  for(i=0;i<n;i++) {
    scanf("%s",book[i]);
  }
  scanf("%s",search);
  for(i=0;i<n;i++) {
    if(strcmp(search,book[i])==0) {
      printf("查找成功\n");
      return 0;
    }
  }
  printf("查找失败\n");
  return 0;
}