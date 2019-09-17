#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROR(N,W,i) (((W)>>(i)) | ((W)<<(N-(i))))
#define ROL(N,W,i) (((W)<<(i)) | ((W)>>(N-(i))))
#define GetBit10(W,n) (((W)>>(10-n))&0x01)
#define ReturnBit10(W,n,k) (((GetBit10(W,n))&0x01)<<(10-k))
#define permutation10(val)\
( ReturnBit10(val,3,1) | ReturnBit10(val,5,2) | ReturnBit10(val,2,3) | \
ReturnBit10(val,7,4) | ReturnBit10(val,4,5) | ReturnBit10(val,10,6) | \
ReturnBit10(val,1,7) | ReturnBit10(val,9,8) | ReturnBit10(val,8,9) | \
ReturnBit10(val,6,10))
#define GetBit8(W,n) (((W)>>(8-n))&0x01)
#define ReturnBit8(W,n,k) (((GetBit8(W,n))&0x01)<<(8-k))
#define permutation8(val)\
( ReturnBit8(val,4,1) | ReturnBit8(val,1,2) | ReturnBit8(val,5,3) | \
ReturnBit8(val,2,4) | ReturnBit8(val,6,5) | ReturnBit8(val,3,6) | \
ReturnBit8(val,8,7) | ReturnBit8(val,7,8))
#define IP(val)\
( ReturnBit8(val,2,1) | ReturnBit8(val,6,2) | ReturnBit8(val,3,3) | \
ReturnBit8(val,1,4) | ReturnBit8(val,4,5) | ReturnBit8(val,8,6) | \
ReturnBit8(val,5,7) | ReturnBit8(val,7,8))
#define reverseIP(val)\
( ReturnBit8(val,4,1) | ReturnBit8(val,1,2) | ReturnBit8(val,3,3) | \
ReturnBit8(val,5,4) | ReturnBit8(val,7,5) | ReturnBit8(val,2,6) | \
ReturnBit8(val,8,7) | ReturnBit8(val,6,8))
#define EP(val)\
( ReturnBit8(val,4,1) | ReturnBit8(val,1,2) | ReturnBit8(val,2,3) | \
ReturnBit8(val,3,4) | ReturnBit8(val,2,5) | ReturnBit8(val,3,6) | \
ReturnBit8(val,4,7) | ReturnBit8(val,1,8))
#define GetBit4(W,n) (((W)>>(4-n))&0x01)
#define ReturnBit4(W,n,k) (((GetBit4(W,n))&0x01)<<(4-k))
#define permutation4(val)\
( ReturnBit4(val,2,1) | ReturnBit4(val,4,2) | ReturnBit4(val,3,3) | \
ReturnBit4(val,1,4))

typedef struct bit10{
    unsigned p10:10;
}p10;

typedef struct bit8{
    unsigned p8:8;
}p8;

typedef struct bit5{
    unsigned p5:5;
}p5;

typedef struct bit4{
    unsigned p4:4;
}p4;


char *uintToBinary10(p10 i, int cnt){
    static char s[11]={'0',};
    int count=cnt;

    do{s[--count]='0'+(char)(i.p10 & 1);
    i.p10=i.p10>>1;
    }while(count);
    return s;
}

char *uintToBinary8(p8 i, int cnt){
    static char s[11]={'0',};
    int count=cnt;

    do{s[--count]='0'+(char)(i.p8 & 1);
    i.p8=i.p8>>1;
    }while(count);
    return s;
}

int c2n(char item){
    return item-'0';
}

int s10_to_dec(char *s){
    int i=0, dec=0;

    for(i=0; i<10; i++){
        dec+=(c2n(s[i])*pow(2,9-i));
    }
    return dec;
}

int s8_to_dec(char *s){
    int i=0, dec=0;

    for(i=0; i<8; i++){
        dec+=(c2n(s[i])*pow(2,7-i));
    }
    return dec;
}

int slice_left5(int n){
    int binary[10]={0,};
    int left[5]={0,};
    int result=0;
    int i=0;

    while(1){
        binary[9-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    for(i=0; i<5; i++)
        left[i]=binary[i];
    for(i=0; i<5; i++)
        result+=(left[i]*pow(2,4-i));
    return result;
}

int slice_right5(int n){
    int binary[10]={0,};
    int right[5]={0,};
    int result=0;
    int i=0;

    while(1){
        binary[9-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    for(i=0; i<5; i++)
        right[i]=binary[i+5];
    for(i=0; i<5; i++)
        result+=(right[i]*pow(2,4-i));
    return result;
}

int slice_left4(int n){
    int binary[8]={0,};
    int left[4]={0,};
    int result=0;
    int i=0;

    while(1){
        binary[7-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    for(i=0; i<4; i++)
        left[i]=binary[i];
    for(i=0; i<4; i++)
        result+=(left[i]*pow(2,3-i));
    return result;
}

int slice_right4(int n){
    int binary[8]={0,};
    int right[4]={0,};
    int result=0;
    int i=0;

    while(1){
        binary[7-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    for(i=0; i<4; i++)
        right[i]=binary[i+4];
    for(i=0; i<4; i++)
        result+=(right[i]*pow(2,3-i));
    return result;
}

int S0(int n){
    int s0[4][4]={{1,0,3,2},
                  {3,2,1,0},
                  {0,2,1,3},
                  {3,1,3,2}};
    int binary[4]={0,};
    int i=0,a,b;

    while(1){
        binary[3-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    a=binary[0]*2+binary[3];
    b=binary[1]*2+binary[2];

    return s0[a][b];
}

int S1(int n){
    int s1[4][4]={{0,1,2,3},
                  {2,0,1,3},
                  {3,0,1,0},
                  {2,1,0,3}};
    int binary[4]={0,};
    int i=0,a,b;

    while(1){
        binary[3-i]=n%2;
        n=n/2;
        i++;
        if(n==0)
            break;
    }
    a=binary[0]*2+binary[3];
    b=binary[1]*2+binary[2];

    return s1[a][b];
}


int main()
{
    char getKey_bin[11];
    char getKey_s[11];
    p10 initKey;
    p10 permuate10;
    p8 key1,key2;
    p5 left,right;

    printf("------- S-DES Å° »ý¼º -------\n");
    printf("Key : ");
    scanf("%s",getKey_bin);
    initKey.p10=s10_to_dec(getKey_bin);

    permuate10.p10 = permutation10(initKey.p10);
    left.p5=slice_left5(permuate10.p10);
    right.p5=slice_right5(permuate10.p10);

    left.p5=ROL(5,left.p5,1);
    right.p5=ROL(5,right.p5,1);
    key1.p8=left.p5*32+right.p5;
    if(key1.p8>=256 && key1.p8<512)
        key1.p8-=256;
    else if(key1.p8>=512)
        key1.p8-=512;
    key1.p8=permutation8(key1.p8);
    printf("Key1 : %s \n",uintToBinary8(key1,8));

    left.p5=ROL(5,left.p5,2);
    right.p5=ROL(5,right.p5,2);

    key2.p8=left.p5*32+right.p5;
    if(key2.p8>=256 && key2.p8<512)
        key2.p8-=256;
    else if(key2.p8>=512)
        key2.p8-=512;
    key2.p8=permutation8(key2.p8);
    printf("Key2 : %s \n-----------------------------\n",uintToBinary8(key2,8));

    //////////////////////////////////////////////////////////////////////////////////////////////

    char getPt[9];
    p8 cp;
    p8 ipip;
    p4 left4,right4;
    p8 epep;
    p8 xorK1,xorK2;
    p4 permuate4;
    p4 funK1,funK2;

    printf("PlainText : ");
    scanf("%s",getPt);
    ipip.p8=s8_to_dec(getPt);
    ipip.p8=IP(ipip.p8);
    left4.p4=slice_left4(ipip.p8);
    right4.p4=slice_right4(ipip.p8);
    epep.p8=left4.p4*16+right4.p4;
    epep.p8=EP(epep.p8);
    xorK1.p8=epep.p8^key1.p8;
    left4.p4=slice_left4(xorK1.p8);
    right4.p4=slice_right4(xorK1.p8);
    permuate4.p4=permutation4((S0(left4.p4)*4)+S1(right4.p4));
    funK1.p4=(slice_left4(ipip.p8))^permuate4.p4;

    epep.p8=EP(funK1.p4*16+funK1.p4);
    xorK2.p8=epep.p8^key2.p8;
    left4.p4=slice_left4(xorK2.p8);
    right4.p4=slice_right4(xorK2.p8);
    permuate4.p4=permutation4((S0(left4.p4)*4)+S1(right4.p4));
    funK2.p4=(slice_right4(ipip.p8))^permuate4.p4;
    cp.p8=reverseIP(funK2.p4*16+funK1.p4);
    printf("CipherText : %s \n",uintToBinary8(cp,8));

    return 0;
}
