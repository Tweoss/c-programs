#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rotate(int x, int rotnum); 
int main(){
    printf("%d",rotate(9,15));
}

int rotate(int x, int rotnum) {
    rotnum = 16 - rotnum;
    int i;
    for (i = 0; i< rotnum; i++) {
        div_t resultstruc = div(x,2);
        if (resultstruc.rem){
            x = resultstruc.quot + pow(2,sizeof(int)*4-1);
        }
        else {
            x = resultstruc.quot;
        }
    }
    return x;
}