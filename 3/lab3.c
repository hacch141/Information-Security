// 202052311
// CHAUDHARI HARSH JAYDIPBHAI

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
uint32_t R_key[16];

// here we store our 8 bit chuncks of the key
uint8_t pairs_of_8bits_for_R_key[4];

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

// driver code
int main () {

    uint32_t plainText;
    scanf("%u", &plainText);
    uint32_t key;
    scanf("%u", &key);

    uint32_t first_key = first_round_key(key,pairs_of_8bits_for_R_key);
    generate_round_keys(first_key,R_key);

    uint64_t cipher =  Encryption(plainText, R_key);
    printf("cipher : %u \n", cipher);

    uint64_t plain =  Decryption(cipher, R_key);
    printf("plain : %u \n", plain);

    return 0;
}	