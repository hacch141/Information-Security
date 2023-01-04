// 202052311
// CHAUDHARI HARSH JAYDIPBHAI

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// step 1-2
uint32_t IV = 0;

// step 3
uint32_t ID_c = 123;
uint32_t AD_c = 12345;
uint32_t ID_tgs = 234;
uint32_t ID_v = 345;

// step 4
uint32_t TS_1 = 141;
uint32_t TS_2 = 236;
uint32_t TS_3 = 891;
uint32_t TS_4 = 100;
uint32_t TS_5 = 321;

// step 5
uint32_t Lifetime2 = 987;
uint32_t Lifetime4 = 987;

uint32_t K_c_tgs;
uint32_t K_c_v;

// s-box
uint8_t s_box[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

// here we store our 16 round keys globally
uint32_t R_key_K_c[16];
uint32_t R_key_K_v[16];
uint32_t R_key_K_tgs[16];
uint32_t R_key_K_c_tgs[16];
uint32_t R_key_K_c_tgs_new[16];
uint32_t R_key_K_c_v[16];
uint32_t R_key_K_c_v_new[16];

// here we store our 8 bit chuncks of the key
uint8_t pairs_of_8bits_for_key_K_c[4];
uint8_t pairs_of_8bits_for_key_K_v[4];
uint8_t pairs_of_8bits_for_key_K_tgs[4];
uint8_t pairs_of_8bits_for_key_K_c_tgs_new[4];
uint8_t pairs_of_8bits_for_key_K_c_tgs[4];
uint8_t pairs_of_8bits_for_key_K_c_v[4];
uint8_t pairs_of_8bits_for_key_K_c_v_new[4];

// function for making chunks of 8 bit from 32 bits
// and stored in arr
void make_chunks_of_32bits(uint32_t num, uint8_t *arr) {
    for(int i=0; i<4; i++) {
        arr[3-i] = (num>>(8*i))&255;
    }
}

// function for making chunks of 8 bit from 64 bits
// and stored in arr
void make_chunks_of_64bits(uint64_t num, uint8_t *arr) {
    for(int i=0; i<8; i++) {
        arr[7-i] = (num>>(8*i))&255;
    }
}

// function for finding value from s_box at (X0,Y0) co-ordinate
uint8_t sbox_value_x0_y0(uint8_t x0y0) {
    int x0 = x0y0>>4;
    int y0 = x0y0 & 15;
    return s_box[x0][y0];
}

// function for generating first round key
uint32_t first_round_key(uint32_t key, uint8_t *pairs_of_8bits_for_key_array) {
    make_chunks_of_32bits(key, pairs_of_8bits_for_key_array);
    uint32_t s_32_bit_for_key = 0;
    for(int i=0; i<4; i++) {
        uint8_t sbox_value = sbox_value_x0_y0(pairs_of_8bits_for_key_array[i]);
        s_32_bit_for_key = (s_32_bit_for_key<<8) | sbox_value;
    }
    return s_32_bit_for_key;
}

// function for generating all the 16 round keys
void generate_round_keys(uint32_t key, uint32_t *R_key_array) {
    for(int i=0; i<16; i++) {
    R_key_array[i] = key<<i | key>>(32-i);
    }
}

// function for finding the inverse of the given value by given number
uint8_t S_Inverse(int num) {
    for(int i=0; i<16; i++) {
        for(int j=0; j<16; j++) {
            if(s_box[i][j] == num) {
                return (uint8_t)(i<<4)|j;
            }
        }
    }
    return -1;
}

// function for finding the RoundFunction value
uint32_t RoundFunction(uint32_t right_half, uint32_t key) {
    uint32_t X = right_half^key;
    uint8_t pairs_of_8bits_for_X[4];
    make_chunks_of_32bits(X, pairs_of_8bits_for_X);
    uint32_t ans = 0;
    for(int i=0; i<4; i++) {
        ans = ans<<8 | S_Inverse(pairs_of_8bits_for_X[i]);
    }
    return ans;
}

// function for encrypting the plaintext
uint64_t Encryption(uint64_t plaintext, uint32_t R_Keys[]) {
    uint64_t cipher = plaintext;
    for(int i=0; i<16; i++) {
        uint32_t l0 = cipher >> 32;
        uint32_t r0 = cipher & (int)4294967295;
        uint32_t l1 = r0;
        uint32_t r1 = l0 ^ RoundFunction(r0, R_Keys[i]);
        cipher = (uint64_t)l1;
        cipher = (cipher<<32) | (uint64_t)r1;
    }
    return cipher;
}

// function for decrypting the ciphertext
uint64_t Decryption(uint64_t ciphertext, uint32_t R_Keys[]) {
    uint64_t again_plaintext = ciphertext;
    for(int i=15; i>=0; i--) {
        uint32_t l1 = again_plaintext >> 32;
        uint32_t r1 = again_plaintext & (int)4294967295;
        uint32_t r0 = l1;
        uint32_t l0 = r1 ^ RoundFunction(l1, R_Keys[i]);
        again_plaintext = (uint64_t)l0;
        again_plaintext = again_plaintext<< 32 | (uint64_t)r0;
    }   
    return again_plaintext;
}

// function for generating the random keys
uint32_t random_key() {
    srand(time(0));
    uint32_t num = rand();
    return num;
}

// function for concatenate 2 parts of 32 bits into 64 bits
uint64_t concatenate(uint32_t lefthalf, uint32_t rightHalf) {
    uint64_t con = lefthalf;
    con = con<<32;
    con = con | rightHalf;
    return con;
}

void encrypt_till_n(uint32_t R_Keys[], uint64_t ticket[], uint64_t encryped_ticket[], int n) {
    uint64_t temp = IV = 0;
    for(int i=0; i<n; i++) {
        encryped_ticket[i] = Encryption(ticket[i]^temp,R_Keys);
        temp = encryped_ticket[i];
    }
}

void decrypt_till_n(uint32_t R_Keys[], uint64_t decrypted_ticket[], uint64_t encryped_ticket[], int n) {
    uint64_t temp = IV = 0;
    for(int i=0; i<n; i++) {
        decrypted_ticket[i] = Decryption(encryped_ticket[i],R_Keys)^temp;
        temp = encryped_ticket[i];
    }
}

// driver code
int main () {

    K_c_tgs = random_key();
    K_c_v = random_key();

    uint32_t K_c = 12345;
    uint32_t K_tgs = 428;
    uint32_t K_v = 3941;

    /***************** (a) Authentication Service Exchange to obtain ticket-granting ticket ***************/
    // (1) C : AS IDc || IDtgs || TS1
    uint32_t C_TO_AS[3];
    C_TO_AS[0] = ID_c;
    C_TO_AS[1] = ID_tgs;
    C_TO_AS[2] = TS_1;

    // generating all the round keys
    // which we are going to use in our code
    uint32_t first_key_K_c = first_round_key(K_c,pairs_of_8bits_for_key_K_c);
    generate_round_keys(first_key_K_c,R_key_K_c);

    uint32_t first_key_K_tgs = first_round_key(K_tgs,pairs_of_8bits_for_key_K_tgs);
    generate_round_keys(first_key_K_tgs,R_key_K_tgs);

    uint32_t first_key_K_v = first_round_key(K_v,pairs_of_8bits_for_key_K_v);
    generate_round_keys(first_key_K_v,R_key_K_v);

    uint32_t first_key_K_c_tgs = first_round_key(K_c_tgs,pairs_of_8bits_for_key_K_c_tgs);
    generate_round_keys(first_key_K_c_tgs,R_key_K_c_tgs);

    uint32_t first_key_K_c_v = first_round_key(K_c_v,pairs_of_8bits_for_key_K_c_v);
    generate_round_keys(first_key_K_c_v,R_key_K_c_v);


    // Tickettgs = E(Ktgs, [Kc, tgs || IDC || ADC || IDtgs || TS2 || Lifetime2])
    uint64_t ticket_tgs[3];
    ticket_tgs[0] = concatenate(K_c_tgs, ID_c);
    ticket_tgs[1] = concatenate(AD_c, ID_tgs);
    ticket_tgs[2] = concatenate(TS_2, Lifetime2);

    // Encryption of ticket tgs
    uint64_t encrypted_ticket[3];
    encrypt_till_n(R_key_K_tgs,ticket_tgs,encrypted_ticket,3);
    uint64_t Tickettgs = encrypted_ticket[2];


    // (2) AS : C E1Kc, [Kc, tgs || IDtgs || TS2 || Lifetime2 || Tickettgs]2
    uint64_t AS_TO_C_Array[3];
    AS_TO_C_Array[0] = concatenate(K_c_tgs,ID_tgs);
    AS_TO_C_Array[1] = concatenate(TS_2,Lifetime2);
    AS_TO_C_Array[2] = Tickettgs;

    // Encryption
    uint64_t AS_TO_C_encryption[3];
    encrypt_till_n(R_key_K_c,AS_TO_C_Array,AS_TO_C_encryption,3);
    uint64_t Astoc = AS_TO_C_encryption[2];
    // Decryption
    uint64_t AS_TO_C_decryption[3];
    decrypt_till_n(R_key_K_c,AS_TO_C_decryption,AS_TO_C_encryption,3);


    // Client will decrypt the received data and recover the session  key, match the IDtgs for verification.
    printf("****** outputs IDtgs and T S2 ******");
    uint32_t new_ID_tgs = (AS_TO_C_decryption[0]<<32)>>32;
    uint32_t new_TS2 = AS_TO_C_decryption[1]>>32;
    printf("\n\n--------- Step 2 ---------");
    printf("\nIDtgs : %u",new_ID_tgs);
    printf("\nTS2 : %u",new_TS2);



    /***************** (b) Ticket-Granting Service Exchange to obtain service-granting ticket ***************/
    // Authenticatorc = E1Kc, tgs, [IDC || ADC || TS3]
    uint64_t Authenticator_c[2];
    Authenticator_c[0] = ID_c;
    Authenticator_c[1] = concatenate(AD_c,TS_3);

    // Encryption
    uint64_t Authenticator_c_encryption[2];
    encrypt_till_n(R_key_K_c_tgs,Authenticator_c,Authenticator_c_encryption,2);
    // Decryption
    uint64_t ticket_tgs_decryption[3];
    decrypt_till_n(R_key_K_tgs,ticket_tgs_decryption,encrypted_ticket,3);

    uint32_t newK_c_tgs = ticket_tgs_decryption[0]>>32;

    // Decrypting Authenticator
    uint32_t first_key_K_c_tgs_new = first_round_key(newK_c_tgs,pairs_of_8bits_for_key_K_c_tgs_new);
    generate_round_keys(first_key_K_c_tgs_new,R_key_K_c_tgs_new);

    uint64_t new_Authenticator_c[2];
    decrypt_till_n(R_key_K_c_tgs_new, new_Authenticator_c,Authenticator_c_encryption,2);

    uint32_t new_ID_c = new_Authenticator_c[0];
    uint32_t new_AD_c = new_Authenticator_c[1]>>32;
    uint32_t new_TS_3 = (new_Authenticator_c[1]<<32)>>32;

    if(new_ID_c==ID_c && new_AD_c==AD_c && new_TS_3==TS_3) {
        printf("\n\n--------- Step 3 ---------\n");
        printf("IDc : %u \n", new_ID_c);
        printf("ADc : %u \n", new_AD_c);
        printf("TS3 : %u \n", new_TS_3);
    }

    // Ticketv = E(Kv, [Kc, v || IDC || ADC || IDv || TS4 || Lifetime4])
    uint64_t ticket_v[3];
    ticket_v[0] = concatenate(K_c_v, ID_c);
    ticket_v[1] = concatenate(AD_c, ID_v);
    ticket_v[2] = concatenate(TS_4, Lifetime4);

    uint64_t encrypted_ticket_v[3];
    encrypt_till_n(R_key_K_v,ticket_v,encrypted_ticket_v,3);
    uint64_t Ticket_v = encrypted_ticket_v[2];

    // (4) TGS : C E1Kc, tgs, [Kc, v || IDv || TS4 || Ticketv]2
    uint64_t TGS_TO_C[3];
    TGS_TO_C[0] = K_c_v;
    TGS_TO_C[1] = concatenate(ID_v,TS_4);
    TGS_TO_C[2] = Ticket_v;

    uint64_t TGS_TO_C_encryption[3];
    encrypt_till_n(R_key_K_c_tgs,TGS_TO_C,TGS_TO_C_encryption,3);
    uint64_t Tgsc = TGS_TO_C_encryption[2];

    uint64_t TGS_TO_C_decryption[3];
    decrypt_till_n(R_key_K_c_tgs,TGS_TO_C_decryption,TGS_TO_C_encryption,3);

    uint32_t new_K_c_v =  TGS_TO_C_decryption[0];
    printf("\nRecovered Kcv IS : %u \n", new_K_c_v);

    uint32_t new_Ticket_v = TGS_TO_C_decryption[2];
    printf("Recovered Ticketv IS : %u \n\n", new_Ticket_v);

    uint32_t new_ID_v =  TGS_TO_C_decryption[1]>>32;

    uint32_t new_TS_4 =  (TGS_TO_C_decryption[1]<<32)>>32;
    
    if(new_ID_v==ID_v && new_TS_4==TS_4){
        printf("\n--------- Step 4 ---------\n");
        printf("IDv IS : %u \n", new_ID_v);
        printf("TS4 IS : %u \n", new_TS_4);
    }


    /***************** (c) Client/Server Authentication Exchange to obtain service ***************/
    // Authenticatorc = E 1Kc, v, [IDC || ADC || TS5]2
    uint64_t Authenticator_c_5[2];
    Authenticator_c_5[0] = ID_c;
    Authenticator_c_5[1] = concatenate(AD_c,TS_5);

    uint64_t Authenticator_c_5_encryption[2];
    encrypt_till_n(R_key_K_c_v,Authenticator_c_5,Authenticator_c_5_encryption,2);


    //Decrypting Ticket tgs
    uint64_t ticket_v_decryption[3];
    decrypt_till_n(R_key_K_v,ticket_v_decryption,encrypted_ticket_v,3);

    uint32_t newK_c_v = ticket_v_decryption[0]>>32;

    // Decrypting Authenticator
    uint32_t first_key_K_c_v_new = first_round_key(newK_c_v,pairs_of_8bits_for_key_K_c_v_new);
    generate_round_keys(first_key_K_c_v_new,R_key_K_c_v_new);

    uint64_t new_Authenticator_c_5[2];
    decrypt_till_n(R_key_K_c_v_new, new_Authenticator_c_5,Authenticator_c_5_encryption,2);

    uint32_t new_ID_c_5 = new_Authenticator_c_5[0];
    uint32_t new_AD_c_5 = new_Authenticator_c_5[1]>>32;
    uint32_t new_TS_5 = (new_Authenticator_c_5[1]<<32)>>32;

    if(new_ID_c_5==ID_c && new_AD_c_5==AD_c && new_TS_5==TS_5) {
        printf("\n--------- Step 5 ---------\n");
        printf("IDc : %u \n", new_ID_c_5);
        printf("ADc : %u \n", new_AD_c_5);
        printf("TS5 : %u \n", new_TS_5);
    }

    // (6) V : C E1Kc,v, [TS5 + 1]2 1for mutual authentication2
    uint64_t V_TO_C_array[1];
    V_TO_C_array[0] = TS_5+1;

    uint64_t V_TO_C_encryption[1];
    encrypt_till_n(R_key_K_c_v,V_TO_C_array,V_TO_C_encryption,1);

    uint64_t V_TO_C_decryption[1];
    decrypt_till_n(R_key_K_c_v,V_TO_C_decryption,V_TO_C_encryption,1);

    if(V_TO_C_decryption[0] == V_TO_C_array[0]) {
        printf("\n--------- Step 6 ---------");
        printf("\nRecovered text is: %lu \n", V_TO_C_decryption[0]);
    }

    return 0;
}	