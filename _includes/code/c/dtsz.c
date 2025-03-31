#include <stdio.h>
#include <stdlib.h>
int main() {
    int m;
    scanf("%d",&m);
    int *number = (int*)malloc(m*sizeof(int));
    for (int i=0;i<m;i++) {
        scanf("%d",&number[i]);
    }
    for(int i=0;i<m;i++) {
        for(int j=i+1;j<m;j++) {
            if(number[i]>number[j]) {
                int temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }
    }
    for(int i=0;i<m;i++) {
        printf("%d ",number[i]);
    }
    printf("\n");
    free(number);
    return 0;
}