#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int strBin_to_decimal(char *);
void print_binary(int dec);
int calcG(int num,int a);
int SBOX(int n);
int NS(int n);
int SR(int n);
int MC(int n);
int Mul(int n,int b);

int main(){

    char plainText[16], key[16];
    int w[6]={0,};
    int i,pText,kText,encText,w_;

    printf("Plain Text : ");
    scanf("%s",plainText);
    printf("Key        : ");
    scanf("%s",key);

    pText = strBin_to_decimal(plainText);
    kText = strBin_to_decimal(key);


    w[0] = (kText&65280)>>8;
    w[1] = kText&255;//185
    w[2] = calcG(w[1],1)^w[0];
    w[3] = w[1]^w[2];
    w[4] = calcG(w[3],2)^w[2];
    w[5] = w[3]^w[4];

    w_ = (w[0]<<8) + w[1];
    encText = pText ^ w_;
    printf("\n----------------------------------------------------");
    //printf("\nadd round key         : ");
    //print_binary(encText);

    encText = NS(encText);
    printf("\nnibble substitution   : ");
    print_binary(encText);

    encText = SR(encText);
    printf("\nshift row             : ");
    print_binary(encText);

    encText = MC(encText);
    printf("\nmix columns           : ");
    print_binary(encText);

    w_ = (w[2]<<8) + w[3];
    encText = encText ^ w_;
    printf("\nadd round key         : ");
    print_binary(encText);

    encText = NS(encText);
    printf("\nnibble substitution   : ");
    print_binary(encText);

    encText = SR(encText);
    printf("\nshift row             : ");
    print_binary(encText);

    w_ = (w[4]<<8) + w[5];
    encText = encText ^ w_;
    printf("\nadd round key         : ");
    print_binary(encText);

    printf("\n----------------------------------------------------");
    printf("\nENCRYPTION >> ");
    print_binary(encText);
    printf("\nDECRYPTION >> ");
    for(i=0;i<16;i++){
        if(i==0)
            printf("0");
        else
            printf("%c",plainText[i]);
    }

    return 0;
}

int strBin_to_decimal(char *x){
    int result=0, i;

    for(i=0; i<16; i++)
        result += (x[i]-'0')*pow(2,15-i);

    return result;
}
void print_binary(int dec){
    int i, bin[16];

    for(i=0; i<15; i++){
        bin[15-i]=dec%2;
        dec=dec/2;
    }
    bin[0]=dec;

    for(i=0; i<16; i++)
        printf("%d",bin[i]);
}

int calcG(int num,int a){
    int i,num0,num1,s0,s1;
    num1=num & 15;//9
    num0=(num & 240)>>4;//11
    s0=SBOX(num1);//2
    s1=SBOX(num0);//3
    if(a==1){
        s0=s0^8;
        }
    else{
        s0=s0^3;
    }
    return (s0<<4)+s1;
}
int SBOX(int n){
    int sbox[4][4]={{9,4,10,11},
                  {13,1,8,5},
                  {6,2,0,3},
                  {12,14,15,7}};
    int binary[4]={0,};
    int i=0,a,b;

    while(1){
        binary[3-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    a=binary[0]*2+binary[1];
    b=binary[2]*2+binary[3];

    return sbox[a][b];
}
int NS(int n){
    int n1,n2,n3,n4;
    n1 = (n>>12)&15;
    n2 = (n>>8)&15;
    n3 = (n>>4)&15;
    n4 = n&15;

    return (SBOX(n1)<<12) + (SBOX(n2)<<8) + (SBOX(n3)<<4) + SBOX(n4);
}
int SR(int n){
    int n1,n2,n3,n4;
    n1 = (n>>12)&15;
    n2 = (n>>8)&15;
    n3 = (n>>4)&15;
    n4 = n&15;

    return (n1<<12) + (n4<<8) + (n3<<4) + (n2);
}
int MC(int n){
    int mc[2][2]={{1,4},
                  {4,1}};
    int n1,n2,n3,n4;
    int n1_,n2_,n3_,n4_;

    n1_ = (n>>12)&15;
    n2_ = (n>>8)&15;
    n3_ = (n>>4)&15;
    n4_ = n&15;

    n1 = (n1_^Mul(n2_,mc[0][1]))<<12;
    n2 = (n2_^Mul(n1_,mc[1][0]))<<8;
    n3 = (n3_^Mul(n4_,mc[0][1]))<<4;
    n4 = (n4_^Mul(n3_,mc[1][0]));
    return n1 + n2 +n3 +n4;
}
int Mul(int n,int b){
    int x[3];
    int r,i,result=0;
    if(n >= 8)
        x[0]=((n<<1)-16)^3;
    else
        x[0]=n<<1;
    if(x[0] >= 8)
        x[1]=((x[0]<<1)-16)^3;
    else
        x[1]=x[0]<<1;
    if(x[1] >= 8)
        x[2]=((x[1]<<1)-16)^3;
    else
        x[2]=x[1]<<1;
    r=b%2;
    if(r==1)
        result=result^1;
    else
        result=result^0;
    b=b/2;
    for(i=0; i<2; i++){
        r=b%2;
        if(r==1)
            result=result^x[i];
        else
            result=result^0;
        b=b/2;
    }
    if(b==1)
        result=result^x[2];
    else
        result=result^0;

	return result;
}
