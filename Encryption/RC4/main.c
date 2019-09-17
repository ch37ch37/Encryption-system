#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void SWAP(int *,int *);
int main()
{
    char key[6]={'a','b','c','d','e'},Ptext[6];
    printf("PlainText >> ");
    scanf("%s",Ptext);
    int i,j,l,t,k,cp[6];
    int S[256],T[256];
    for(i=0;i<256;i++){
        S[i] = i;
        T[i] = key[i%strlen(key)];
    }
    j=0;
    for(i=0;i<256;i++){
        j=(j+S[i]+T[i])%256;
        SWAP(&S[i],&S[j]);
    }
    i=0;
    j=0;
    printf("CP >> ");
    for(l=0;l<strlen(Ptext);l++){
        i=(i+1) % 256;
        j = (j+S[i]) % 256;
        SWAP(&S[i],&S[j]);
        t=(S[i]+S[j])%256;
        k=S[t];
        cp[l]=Ptext[l]^k;
        printf("%x",cp[l]);
    }

    return 0;
}
void SWAP(int *A,int *B){
    int emt;
    emt = *A;
    *A = *B;
    *B = emt;
}
