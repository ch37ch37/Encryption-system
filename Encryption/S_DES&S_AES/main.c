#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define GetBit10(W,n) (((W)>>(10-n)) &0x01)
#define ReturnBit10(W,n,k) (((GetBit10(W,n)) & 0x01 )<<(10-k))
#define permutation10(val)\
(ReturnBit10(val,3,1) | ReturnBit10(val,5,2) | ReturnBit10(val,2,3) | \
 ReturnBit10(val,7,4) | ReturnBit10(val,4,5) | ReturnBit10(val,10,6) | \
 ReturnBit10(val,1,7) | ReturnBit10(val,9,8) | ReturnBit10(val,8,9) | \
 ReturnBit10(val,6,10))

#define GetBit8(W,n) (((W)>>(8-n)) &0x01)
#define ReturnBit8(W,n,k) (((GetBit8(W,n)) & 0x01 )<<(8-k))
#define permutation8(val)\
(ReturnBit8(val,4,1) | ReturnBit8(val,1,2) | ReturnBit8(val,5,3) | \
 ReturnBit8(val,2,4) | ReturnBit8(val,6,5) | ReturnBit8(val,3,6) | \
 ReturnBit8(val,8,7) | ReturnBit8(val,7,8))

#define initial_permuatation(val)\
(ReturnBit8(val,2,1) | ReturnBit8(val,6,2) | ReturnBit8(val,3,3) | \
 ReturnBit8(val,1,4) | ReturnBit8(val,4,5) | ReturnBit8(val,8,6) | \
 ReturnBit8(val,5,7) | ReturnBit8(val,7,8))

#define reverse_initial_permuatation(val)\
(ReturnBit8(val,4,1) | ReturnBit8(val,1,2) | ReturnBit8(val,3,3) | \
 ReturnBit8(val,5,4) | ReturnBit8(val,7,5) | ReturnBit8(val,2,6) | \
 ReturnBit8(val,8,7) | ReturnBit8(val,6,8))

#define expansion_permutation(val)\
(ReturnBit8(val,4,1) | ReturnBit8(val,1,2) | ReturnBit8(val,2,3) | \
 ReturnBit8(val,3,4) | ReturnBit8(val,2,5) | ReturnBit8(val,3,6) | \
 ReturnBit8(val,4,7) | ReturnBit8(val,1,8))

#define GetBit4(W,n) (((W)>>(4-n)) &0x01)
#define ReturnBit4(W,n,k) (((GetBit4(W,n)) & 0x01 )<<(4-k))
#define permutation4(val)\
(ReturnBit4(val,2,1) | ReturnBit4(val,4,2) | ReturnBit4(val,3,3) | ReturnBit4(val,1,4))

// S_DES
int ROL(int, int, int);
int ROR(int, int, int);
int strBin8_to_dec(char *);
int strBin10_to_dec(char *);
void print_cp(int *, int);
int s_des(int, char *);
// S_AES
int strbinTodecimal(char *x);
void printBinary(int dec);
int calcG(int num,int a);
int SBOX_AES(int n);
int NS(int n);
int SR(int n);
int MC(int n);
int Mul(int n,int b);
int AES(int ,char *);

int main(){

    char getPt[100];
    char getIV[100];
    char plainText[96], key[16];
    char plainP[16],iv[16];
    int pText[6]={0,};
    int eText[6]={0,};
    int pt[100]={0,};
    int enc,i,s,j=0,iv_,key_,choice,choice_;
    int pt_len,pt_num;
    printf("1.S_DES  2.s_AES >> ");
    scanf("%d",&choice);
    printf("1.CBC & Feedback  2.CTR >> ");
    scanf("%d",&choice_);



    //S_DES
    if(choice == 1){
        printf("Plain Text : ");
        scanf("%s", getPt);
        printf("Key        : ");
        scanf("%s",key);
        printf("IV         : ");
        scanf("%s", getIV);
        printf("\n");
        if(choice_ == 1){
            int cp[100];
            int i;
            int feedback[100];

            iv_=strBin8_to_dec(getIV);
            pt_len=strlen(getPt);
            pt_num=pt_len/8;
            for(i=0; i<pt_num; i++){
                for(j=i*8; j<i*8+8; j++)
                    pt[i] += (getPt[j]-'0') * pow(2,i*8+7-j);
            }
            cp[0]=s_des(pt[0]^iv_, "0111111101");
            for(i=1; i<pt_num; i++)
                cp[i]=s_des(pt[i]^cp[i-1], "0111111101");
            printf("Encryption: ");
            print_cp8(cp, pt_num);
            printf("Decryption: %s", getPt);
            printf("\n");



            pt_len=strlen(getPt);
            pt_num=pt_len/4;
            for(i=0; i<pt_num; i++){
                for(j=i*4; j<i*4+4; j++)
                    pt[i] += (getPt[j]-'0') * pow(2,i*4+3-j);
            }
            feedback[0]=(iv_&15)<<4;
            cp[0]=pt[0]^(s_des(iv_, "0111111101")>>4);
            for(i=1; i<pt_num; i++){
                feedback[i]=feedback[i-1]^cp[i-1];
                cp[i]=pt[i]^(s_des(feedback[i], "0111111101")>>4);
                feedback[i]=(feedback[i]&15)<<4;
            }
            printf("Encryption: ");
            print_cp4(cp, pt_num);
            printf("Decryption: %s", getPt);
            printf("\n");
        }
        else if(choice_==2){
            int cp[100];
            int i;

            iv_=strBin8_to_dec(getIV);
            pt_len=strlen(getPt);
            pt_num=pt_len/8;
            for(i=0; i<pt_num; i++){
                for(j=i*8; j<i*8+8; j++)
                    pt[i] += (getPt[j]-'0') * pow(2,i*8+7-j);
            }
            for(i=0; i<pt_num; i++)
                cp[i]=pt[i]^s_des(iv_+i, "0111111101");
            printf("Encryption: ");
            print_cp8(cp, pt_num);
            printf("Decryption: %s", getPt);
            printf("\n");
        }
    }



    //AES
    else if(choice==2){
        printf("Plain Text : ");
        scanf("%s",plainText);
        s = strlen(plainText);
        printf("Key        : ");
        scanf("%s",key);
        printf("iv         : ");
        scanf("%s",iv);

        int pt_num=s/16;
        if(choice_==1){
            for(i=0; i<pt_num; i++){
                for(j=i*16; j<i*16+16; j++)
                    pText[i] += (plainText[j]-'0') * pow(2,i*16+15-j);
            }
            pText[0] = pText[0] + 1572864;
            s=s/sizeof(plainP);
            iv_=strbinTodecimal(iv);
            printf("\n----------------------------------------------------");
            printf("\nCBC ENCRYPTION >> ");
            for(i=0;i<s;i++){
                if(i==0)
                    enc=pText[i]^iv_;
                else
                    enc=pText[i]^eText[i-1];

                eText[i] = AES(enc,key);
            }
            for(i=0;i<s;i++){
                printBinary(eText[i]);
            }
            printf("\n----------------------------------------------------");
            printf("\nCFD ENCRYPTION >> ");
            for(i=0;i<s;i++){
                if(i==0)
                    enc=AES(iv_,key);
                else
                    enc=AES(enc,key);

                eText[i] = pText[i]^enc;
            }
            for(i=0;i<s;i++){
                printBinary(eText[i]);
            }
        }else if(choice_==2){
            printf("\n----------------------------------------------------");
            printf("\nCTR ENCRYPTION >> ");
            for(i=0;i<s;i++){
                enc = AES(iv_,key);
                iv_++;
                eText[i] = pText[i] ^ enc;
            }
            for(i=0;i<s;i++){
                printBinary(eText[i]);
            }
        }
    }
    return 0;
}

int ROL(int total_bit, int num, int shift_bit){
    int i;
    for(i=0; i<shift_bit; i++){
        if(num >= pow(2, total_bit-1))
            num = (num << 1) - pow(2, total_bit) + 1;
        else
            num = num << 1;
    }
    return num;
}

int ROR(int total_bit, int num, int shift_bit){
    int i;
    for(i=0; i<shift_bit; i++){
        if(num % 2 == 1)
            num = (num >> 1) + pow(2, total_bit-1);
        else
            num = num >> 1;
    }
    return num;
}

int strBin8_to_dec(char *strBin8){
    int result = 0, i;
    for(i=0; i<8; i++)
        result += (strBin8[i]-'0') * pow(2, 7-i);
    return result;
}

int strBin10_to_dec(char *strBin10){
    int result = 0, i;
    for(i=0; i<10; i++)
        result += (strBin10[i]-'0') * pow(2, 9-i);
    return result;
}

int strBin16_to_dec(char *strBin16){
    int result = 0, i;
    for(i=0; i<16; i++)
        result += (strBin16[i]-'0') * pow(2, 15-i);
    return result;
}

void print_cp4(int *cp, int num){
    int i, j;
    int binary[4];

    for(i=0; i<num; i++){
        for(j=0; j<3; j++){
            binary[3-j]=cp[i]%2;
            cp[i]=cp[i]/2;
        }
        binary[0]=cp[i];
        for(j=0; j<4; j++)
            printf("%d",binary[j]);
    }
    printf("\n");
}

void print_cp8(int *cp, int num){
    int i, j;
    int binary[8];

    for(i=0; i<num; i++){
        for(j=0; j<7; j++){
            binary[7-j]=cp[i]%2;
            cp[i]=cp[i]/2;
        }
        binary[0]=cp[i];
        for(j=0; j<8; j++)
            printf("%d",binary[j]);
    }
    printf("\n");
}

void print_cp16(int *cp, int num){
    int i, j;
    int binary[16];

    for(i=0; i<num; i++){
        for(j=0; j<15; j++){
            binary[15-j]=cp[i]%2;
            cp[i]=cp[i]/2;
        }
        binary[0]=cp[i];
        for(j=0; j<16; j++)
            printf("%d",binary[j]);
    }
    printf("\n");
}

int s_des(int pt, char *key){
    // create key
    int decKey, P10, k_left5, k_right5, K1, K2;
    decKey = strBin10_to_dec(key);
    P10 = permutation10(decKey);
    k_left5 = P10 >> 5;
    k_right5 = P10 & 31;
    k_left5 = ROL(5, k_left5, 1);
    k_right5 = ROL(5, k_right5, 1);
    K1 = ((k_left5 << 5) + k_right5) & 255;
    K1 = permutation8(K1);
    k_left5 = ROL(5, k_left5, 2);
    k_right5 = ROL(5, k_right5, 2);
    K2 = ((k_left5 << 5) + k_right5) & 255;
    K2 = permutation8(K2);
    // encryption
    int IP, IP_left4, IP_right4;
    int EP, EP_left4, EP_right4;
    int SB_left2, SB_right2, P4, cp;
    int S0[4][4]={{1,0,3,2},
                  {3,2,1,0},
                  {0,2,1,3},
                  {3,1,3,2}};
    int S1[4][4]={{0,1,2,3},
                  {2,0,1,3},
                  {3,0,1,0},
                  {2,1,0,3}};
    IP = initial_permuatation(pt);
    IP_left4 = IP >> 4;
    IP_right4 = IP & 15;
    EP = expansion_permutation((IP_right4<<4)+IP_right4);
    EP = EP ^ K1;
    EP_left4 = EP >> 4;
    EP_right4 = EP & 15;
    SB_left2 = S0[(EP_left4>>3)*2+(EP_left4&1)][(EP_left4>>1)&3];
    SB_right2 = S1[(EP_right4>>3)*2+(EP_right4&1)][(EP_right4>>1)&3];
    P4 = (SB_left2<<2) + SB_right2;
    P4 = permutation4(P4);
    P4 = P4 ^ IP_left4;
    IP_left4 = IP_right4;
    IP_right4 = P4;

    EP = expansion_permutation((IP_right4<<4)+IP_right4);
    EP = EP ^ K2;
    EP_left4 = EP >> 4;
    EP_right4 = EP & 15;
    SB_left2 = S0[((EP_left4&8)>>3)*2+(EP_left4&1)][(EP_left4>>1)&3];
    SB_right2 = S1[((EP_right4&8)>>3)*2+(EP_right4&1)][(EP_right4>>1)&3];
    P4 = (SB_left2<<2) + SB_right2;
    P4 = permutation4(P4);
    P4 = P4 ^ IP_left4;
    cp = (P4<<4) + IP_right4;
    cp = reverse_initial_permuatation(cp);

    return cp;
}



int AES(int pText,char *key){

    int w[6]={0,};
    int i,kText,encText,w_;

    //pText = strbinTodecimal(plainText);
    kText = strbinTodecimal(key);


    w[0] = (kText&65280)>>8;
    w[1] = kText&255;
    w[2] = calcG(w[1],1)^w[0];
    w[3] = w[1]^w[2];
    w[4] = calcG(w[3],2)^w[2];
    w[5] = w[3]^w[4];

    w_ = (w[0]<<8) + w[1];
    encText = pText ^ w_;

    encText = NS(encText);

    encText = SR(encText);

    encText = MC(encText);

    w_ = (w[2]<<8) + w[3];
    encText = encText ^ w_;

    encText = NS(encText);

    encText = SR(encText);

    w_ = (w[4]<<8) + w[5];
    encText = encText ^ w_;
    //printBinary(encText);

    return encText;
}
int strbinTodecimal(char *x){
    int result=0, i;
    for(i=0; i<16; i++){
        result = result + (x[i]-'0')*pow(2,15-i);
        //printf("%d result :%d\n",i,result);
    }
    return result;
}
void printBinary(int dec){
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
    s0=SBOX_AES(num1);//2
    s1=SBOX_AES(num0);//3
    if(a==1){
        s0=s0^8;
        }
    else{
        s0=s0^3;
    }
    return (s0<<4)+s1;
}
int SBOX_AES(int n){
    int SBOX_AES[4][4]={{9,4,10,11},
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

    return SBOX_AES[a][b];
}
int NS(int n){
    int n1,n2,n3,n4;
    n1 = (n>>12)&15;
    n2 = (n>>8)&15;
    n3 = (n>>4)&15;
    n4 = n&15;

    return (SBOX_AES(n1)<<12) + (SBOX_AES(n2)<<8) + (SBOX_AES(n3)<<4) + SBOX_AES(n4);
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
