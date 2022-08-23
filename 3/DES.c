#include <stdio.h>
#include <stdint.h>
#include <string.h>

// char arr[1][64];

// int binaryToDecimal(uint64_t n) {
//     int dec_value = 0;
//     int base = 1;
//     uint64_t temp = n;
//     while (temp) {
//         int last_digit = temp % 10;
//         temp = temp / 10;
//         dec_value += last_digit * base;
//         base = base * 2;
//     }
//     return dec_value;
// }

// void binary_to_decimal(char *bArr) {
//     uint64_t cipher_in_decimal = 0;
//     for(int i=63; i>=0; i--) {
//         int j = bArr[i]-'0';
//         if(i == 63) {
//             cipher_in_decimal = (cipher_in_decimal)|j;    
//             continue;
//         }
//         cipher_in_decimal = (cipher_in_decimal<<1)|j;
//     }
//     printf("\nCipher i Decimal : %lu",cipher_in_decimal);
// }

void strrev(char *str1) {   
    int i, len, temp;  
    len = strlen(str1);    
    for (i = 0; i < len/2; i++) {  
        temp = str1[i];  
        str1[i] = str1[len - i - 1];  
        str1[len - i - 1] = temp;  
    }  
}

void encryption(char IPstr[], char* cipher, char PC2str[16][48]) {

    int expand[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                       6, 7, 8, 9, 8, 9, 10, 11,
                       12, 13, 12, 13, 14, 15, 16, 17,
                       16, 17, 18, 19, 20, 21, 20, 21,
                       22, 23, 24, 25, 24, 25, 26, 27,
                       28, 29, 28, 29, 30, 31, 32, 1 };

     int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

    int final_permutation[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                                39, 7, 47, 15, 55, 23, 63, 31,
                                38, 6, 46, 14, 54, 22, 62, 30,
                                37, 5, 45, 13, 53, 21, 61, 29,
                                36, 4, 44, 12, 52, 20, 60, 28,
                                35, 3, 43, 11, 51, 19, 59, 27,
                                34, 2, 42, 10, 50, 18, 58, 26,
                                33, 1, 41, 9, 49, 17, 57, 25 };


    char R0[17][32];
    for(int i=0; i<32; i++) {
        R0[0][i] = IPstr[i+32];
    }
    R0[0][32] = '\0';
    // printf("\nR0 : %s", R0);

    char L0[17][32];
    for(int i=0; i<32; i++) {
        L0[0][i] = IPstr[i];
    }
    L0[0][32] = '\0';
    // printf("\nL0 : %s", L0);
    
    for(int k=0; k<16; k++) {

        char expandTo48bits[48];
        for(int i=0; i<48; i++) {
            expandTo48bits[i] = R0[k][expand[i]-1];
        }
        expandTo48bits[48] = '\0';

        char xor48[48];
        for(int i=0; i<48; i++) {
        int i1 = expandTo48bits[i]-'0';
        int i2 = PC2str[k][i]-'0';
            if(i1 == i2) {
                xor48[i] = '0';
            }
            else {
                xor48[i] = '1';
            }
        }
        xor48[48] = '\0';
        printf("\nXOR 48 : %s",xor48);

        char substitute[32];
        for(int i=0; i<8; i++) {
            char pairOfSix[6];
            for(int j=0; j<6; j++) {
                pairOfSix[j] = xor48[(i*6)+j];
            }
            int row = (2*(pairOfSix[0]-'0') + (1*(pairOfSix[5]-'0')));
            int col = (8*(pairOfSix[1]-'0') + (4*(pairOfSix[2]-'0')) + 2*(pairOfSix[3]-'0') + (1*(pairOfSix[4]-'0')));

            printf("\nrow : %d", row);
            printf("  col : %d", col);

            int val_FromS_Box = s[i][row][col];
            char val_FromS_Box_binaray[4];
            for(int j=0; j<4; j++) {
                val_FromS_Box_binaray[j] = ((val_FromS_Box>>j)&1) + '0';
            }
            val_FromS_Box_binaray[4] = '\0';
            strrev(val_FromS_Box_binaray);
            for(int j=0; j<4; j++) {
                substitute[(i*4)+j] = val_FromS_Box_binaray[j];
            }
        }
        substitute[32] = '\0';
        printf("\nsubstitued : %s",substitute);

        int permutation[32] = { 16, 7, 20, 21,
                        29, 12, 28, 17,
                        1, 15, 23, 26,
                        5, 18, 31, 10,
                        2, 8, 24, 14,
                        32, 27, 3, 9,
                        19, 13, 30, 6,
                        22, 11, 4, 25 };
        
        char after_Permutation[32];
        for(int i=0; i<32; i++) {
            after_Permutation[i] = substitute[permutation[i]-1];
        }
        after_Permutation[32] = '\0';
        printf("After Perm : %s",after_Permutation);
        
        char xor_of_L0_and_Perm[32];
        for(int i=0; i<32; i++) {
            int i1 = L0[k][i] - '0';
            int i2 = after_Permutation[i] - '0';
            if(i1 == i2) {
                xor_of_L0_and_Perm[i] = '0';
            }
            else {
                xor_of_L0_and_Perm[i] = '1';
            }
        }
        xor_of_L0_and_Perm[32] = '\0';
        printf("\nxor_of_L0_and_Perm : %s",xor_of_L0_and_Perm);

        for(int i=0; i<32; i++) {
            L0[k+1][i] = R0[k][i];
            // if(k+1 == 16) {
            //     arr[0][i] = R0[k][i];
            // }
        }
        L0[k+1][32] = '\0';
        printf("\nL[%d] : %s",k+1,L0[k+1]);     
        for(int i=0; i<32; i++) {
            R0[k+1][i] = xor_of_L0_and_Perm[i];
            // if(k+1 == 16) {
            //     arr[0][i+32] = R0[k][i];
            // }
        }
        R0[k+1][32] = '\0';
        // if(k+1 == 16) {
        //     arr[0][64] = '\0';
        // }
        printf("\nR[%d] : %s",k+1,R0[k+1]);
    }


    char temp_for_swap[64];
    for(int i=0; i<32; i++) {
        temp_for_swap[i] = R0[16][i];
    }
    for(int i=32; i<64; i++) {
        temp_for_swap[i] = L0[16][i%32];
    }
    temp_for_swap[64] = '\0';

    for(int i=0; i<64; i++) {
        cipher[i] = temp_for_swap[final_permutation[i]-1];
    }
    cipher[64] = '\0';
    printf("\nIP Inverse : %s",cipher);
}


void leftCircular(char k[28], int shift, char* array) {
    if(shift == 1) {
        char temp = k[0]; 
        for(int i=0;i<27;i++){
            array[i]=k[i+1];
        }
        array[27] = temp;
        array[28] = '\0';
    }
    else if(shift == 2) {
        char temp1 = k[0];
        char temp2 = k[1];
        for(int i=0; i<26; i++) {
            array[i] = k[i+2];
        }
        array[26] = temp1;
        array[27] = temp2;
        array[28] = '\0';
    }
}


int main () {

    uint64_t plaintext;
    printf("Enter plain text : ");
    scanf("%lu", &plaintext);

    printf("\nplain text : %lu",plaintext);
    char binarystr[64];
    for(int i=0; i<64; i++) {
        binarystr[i] = ((plaintext>>i)&1)+'0';
    }

    binarystr[64] = '\0';
    strrev(binarystr);
    printf("\nbinary string of plain text : %s",binarystr);

    int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                  60, 52, 44, 36, 28, 20, 12, 4,
                  62, 54, 46, 38, 30, 22, 14, 6,
                  64, 56, 48, 40, 32, 24, 16, 8,
                  57, 49, 41, 33, 25, 17, 9 , 1,
                  59, 51, 43, 35, 27, 19, 11, 3,
                  61, 53, 45, 37, 29, 21, 13, 5,
                  63, 55, 47, 39, 31, 23, 15, 7
                  };

    char IPstr[64];
    for(int i=0; i<64; i++) {
        IPstr[i] = binarystr[IP[i]-1];
    }
    IPstr[64] = '\0';

    printf("\nIP string of plain text     : %s",IPstr);

    uint64_t key;
    printf("\nEnter key : ");
    scanf("%lu", &key);
    printf("\nkey : %lu",key);
    char binarykey[64];
    for(int i=0; i<64; i++) {
        binarykey[i] = ((key>>i)&1)+'0';
    }

    binarykey[64] = '\0';
    strrev(binarykey);
    printf("\nbinary string of key        : %s",binarykey);

    int PC1[56] = {57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4
                  };

    char PC1str[56];
    for(int i=0; i<56; i++) {
        PC1str[i] = binarykey[PC1[i]-1];
    }
    PC1str[56] = '\0';

    printf("\nPC1 string of key           : %s",PC1str);


    char C0[28];
    for(int i=0; i<28; i++) {
        C0[i] = PC1str[i];
    }
    C0[28] = '\0';

    char D0[28];
    for(int i=28; i<56; i++) {
        D0[i%28] = PC1str[i];
    }
    D0[28] = '\0';


    int shift_table[16] = { 1, 1, 2, 2,
                            2, 2, 2, 2,
                            1, 2, 2, 2,
                            2, 2, 2, 1 };

    char C[17][28];
    char D[17][28];

    for(int i=0; i<28; i++) {
        C[0][i] = C0[i];
    }
    C[0][28] = '\0';
    printf("\nC0 : %s",C[0]);
    for(int i=0; i<28; i++) {
        D[0][i] = D0[i];
    }
    D[0][28] = '\0';
    printf("\nD0 : %s",D[0]);

    for(int i=0; i<16; i++) {
        char array1[28];
        leftCircular(C[i], shift_table[i], array1);
        for(int j=0; j<28; j++) {
            C[i+1][j] = array1[j];
        }
        C[i+1][28] = '\0';
        char array2[28];
        leftCircular(D[i], shift_table[i], array2);
        for(int j=0; j<28; j++) {
            D[i+1][j] = array2[j];
        }
        D[i+1][28] = '\0';
    }
    
    printf("\n");

    char final_key[16][56];
    for(int i=0; i<16; i++) {
        for(int j=0; j<56; j++) {
            if(j<28) {
                final_key[i][j] = C[i+1][j];
            }
            else {
                final_key[i][j] = D[i+1][j%28];
            }
        }
        final_key[i][56] = '\0';
        printf("\nFinal Key[%d] : %s",i,final_key[i]);
    }

    int PC2[48] = { 14, 17, 11, 24, 1, 5,
                     3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32 };

    char PC2str[16][48];
    for(int i=0; i<16; i++) {
        for(int j=0; j<48; j++) {
            PC2str[i][j] = final_key[i][PC2[j]-1];
        }
        PC2str[i][48] = '\0';
        printf("\nPC2str[%d] : %s",i, PC2str[i]);
    }

    char cipher[64];
    encryption(IPstr,cipher,PC2str);

    return 0;
}