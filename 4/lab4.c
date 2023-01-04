// 202052311
// CHAUDHARI HARSH JAYDIPBHAI

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


uint64_t g = 2;
uint64_t P = 4294967296-5;

// function for finding power of the given number
uint64_t num_pow(uint64_t num, uint64_t pow, uint64_t n) {
    uint64_t A = num%n;
    uint64_t b;
    if(pow&1 == 1) {
    	b = A;
    }
    else {
    	b = 1;
    }
    pow = pow>>1;

    while(pow > 0) {
        A = (A*A)%n;
        if(pow&1 == 1) {
            b = (b*A)%n;
        }
        pow = pow>>1;
    }
    return b;
}

// function for finding gcd of two numbers
uint64_t gcd(uint64_t n1, uint64_t n2) {
    uint64_t i, gcd;
    for(i=1; i <= n1 && i <= n2; i++)
    {
        if(n1%i==0 && n2%i==0) {
            gcd = i;
        }
    }
    return gcd;
}

// function for finding value of e
// gcd of phi and e will give one
uint64_t gcd_1(uint64_t phi) {
    uint64_t ans;
    for(uint64_t i=2; i<phi; i++) {
        ans = gcd(phi, i);
        if(ans == 1) {
            return i;
        }
    }
    return -1;
}

// extended euclidean algorithm
int gcdExtended(int a, int b, int* x, int* y)
{
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    int x1, y1; 
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

// function for finding inverse of e with modulo phi
// here we use d notation for it
int find_d(int A, int M)
{
    int x, y, res;
    int g = gcdExtended(A, M, &x, &y);
    if (g != 1) {
        printf("Inverse doesn't exist");
		return -1;
	}
    else {
        res = (x % M + M) % M;
    }
	return res;
}

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
uint32_t round_keys[16];
// here we store our 8 bit chuncks of the key
uint8_t pairs_of_8bits_for_key[4];

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
uint32_t first_round_key(uint32_t key) {
    make_chunks_of_32bits(key, pairs_of_8bits_for_key);
    uint32_t s_32_bit_for_key = 0;
    for(int i=0; i<4; i++) {
        uint8_t sbox_value = sbox_value_x0_y0(pairs_of_8bits_for_key[i]);
        s_32_bit_for_key = (s_32_bit_for_key<<8) | sbox_value;
    }
    return s_32_bit_for_key;
}

// function for generating all the 16 round keys
void generate_round_keys(uint32_t key) {
    for(int i=0; i<16; i++) {
        round_keys[i] = key<<i | key>>(32-i);
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
uint64_t Encryption(uint64_t plaintext) {
    uint64_t cipher = plaintext;
    for(int i=0; i<16; i++) {
        uint32_t l0 = cipher >> 32;
        uint32_t r0 = cipher & (int)4294967295;
        uint32_t l1 = r0;
        uint32_t r1 = l0 ^ RoundFunction(r0, round_keys[i]);
        cipher = (uint64_t)l1;
        cipher = (cipher<<32) | (uint64_t)r1;
    }
    return cipher;
}

// function for decrypting the ciphertext
uint64_t Decryption(uint64_t ciphertext) {
    uint64_t again_plaintext = ciphertext;
    for(int i=15; i>=0; i--) {
        uint32_t l1 = again_plaintext >> 32;
        uint32_t r1 = again_plaintext & (int)4294967295;
        uint32_t r0 = l1;
        uint32_t l0 = r1 ^ RoundFunction(l1, round_keys[i]);
        again_plaintext = (uint64_t)l0;
        again_plaintext = again_plaintext<< 32 | (uint64_t)r0;
    }   
    return again_plaintext;
}

// function for finding the MAC value 
uint32_t MAC(uint64_t M, uint32_t K) {
    uint32_t L0 = M>>32;
    uint32_t R0 = M & (int)4294967295;
    return (L0 ^ R0) ^ K;
}

// driver code
int main () {

    // step 1
    printf("\n -------------  For Alice  ---------------");
    // Alice selects two large prime numbers pa, qa of 32 bits
    printf("\nEnter 1st Prime : ");
    uint32_t pa;
    scanf("%u", &pa);
    printf("\nEnter 2nd Prime : ");
    uint32_t qa;
    scanf("%u", &qa);

    // step 2
    // Alice computes na = paqa
    uint64_t na = pa*qa;
    printf("\n na : %lu", na);
    // Alice computes ϕ(na)
    uint64_t phia = (pa-1)*(qa-1);
    printf("\n phia : %lu", phia);

    // step 3
    // Alice finds ea such that gcd(ea, xa) = 1
    uint64_t ea = gcd_1(phia);
    printf("\n ea : %lu", ea);

    // step 4-5
    // Alice computes da such that eada ≡ 1 mod xa
    uint64_t da = find_d(ea, phia);
    printf("\n da : %lu", da);

    printf("\n\n");

    // step 6
    // Bob selects two large prime numbers pb, qb of 32 bits
    printf("\n --------------  For Bob  -----------------");
    printf("\nEnter 1st Prime : ");
    uint32_t pb;
    scanf("%u", &pb);
    printf("\nEnter 2nd Prime : ");
    uint32_t qb;
    scanf("%u", &qb);

    // step 7
    // Bob computes nb = pbqb
    uint64_t nb = pb*qb;
    printf("\n nb : %lu", nb);
    // Bob computes ϕ(nb)
    uint64_t phib = (pb-1)*(qb-1);
    printf("\n phib : %lu", phib);

    // step 8
    // Bob finds eb such that gcd(eb, xb) = 1
    uint64_t eb = gcd_1(phib);
    printf("\n eb : %lu", eb);

    // step 9-10
    // Bob computes db such that ebdb ≡ 1 mod xb
    uint64_t db = find_d(eb, phib);
    printf("\n db : %lu", db);

    printf("\n");

    printf("\n-----------------------------------------\n");

    // step 11
    // Alice selects a random integer 0 < A < p and computes Diffie-Hellman (DH) public key KA = g^A
    printf("\n Enter A for Alice : ");
    uint64_t A;
    scanf("%lu", &A);
    uint64_t Ka = num_pow(g, A, P);
    printf("\n Ka : %lu", Ka);

    // step 12
    // Alice signs on his public key using his RSA secret key and sends signature SA and DH public key KA to Bob
    uint64_t Sa = num_pow(Ka, da, na);
    printf("\n Sa : %lu \n", Sa);

    // step 13
    // Bob selects a random integer 0 < B < p and computes Diffie-Hellman (DH) public key KB = g^B
    printf("\n Enter B for Bob : ");
    uint64_t B;
    scanf("%lu", &B);
    uint64_t Kb = num_pow(g, B, P);
    printf("\n Kb : %lu", Kb);

    // step 14
    // Bob signs on his public key using his RSA secret key and sends signature SB and DH public key KB to Alice
    uint64_t Sb = num_pow(Kb, db, nb);
    printf("\n Sb : %lu \n", Sb);

    printf("\n-----------------------------------------\n");

    // step 15
    // Alice verifies the SB if verification passes then he computes K = g^AB
    uint64_t Va = num_pow(Sa, ea, na);
    printf("\n Va : %lu", Va);
    printf("\n For Veryfication Ka = %lu , Va = %lu \n", Ka, Va);
    uint64_t K1 = num_pow(Ka, B, P);
    printf("\n K1 : %lu \n", K1);

    // step 16
    // Bob verifies the SA if verification passes then he computes K = g^AB
    uint64_t Vb = num_pow(Sb, eb, nb);
    printf("\n Vb : %lu", Vb);
    printf("\n For Veryfication Ka = %lu , Va = %lu \n", Kb, Vb);
    uint64_t K2 = num_pow(Kb, A, P);
    printf("\n K2 : %lu", K2);

    printf("\n-----------------------------------------\n");

    // step 17
    // Alice now selects a message of 64 bits and encrypts the message MA using the below mentioned Symmetric-Enc algorithm
    uint64_t Ma;
    printf("\n\n Alice's plain text : ");
    scanf("%lu", &Ma);
    // generate 16 round keys using key
    uint32_t key = K1 = K2;
    uint32_t F_R_key = first_round_key(key);
    generate_round_keys(F_R_key);
    uint64_t ciphertext = Encryption(Ma);

    // step 18
    // Print the above generated ciphertext C
    printf("\n cipher text : %lu \n", ciphertext);
    
    // step 19
    // Alice xor the least significant 32 bits of MA with the most significant 32 bits of MA and K to generate the MAC, MACA
    uint32_t MACa = MAC(Ma, key);
    printf("\n MACa : %u \n", MACa);

    // step 20
    // Alice sends C, MACA to Bob

    // step 21
    // Bob decrypts C using K and recovers MA after that verifies the MACA
    uint64_t recovered_Ma = Decryption(ciphertext);
    printf("\n recovered Ma : %lu \n", recovered_Ma);

    // step 22
    // Print the output from the MAC verification algorithm from Bob’s side
    uint32_t MACb = MAC(recovered_Ma, key);
    printf("\n MACb : %u \n", MACb);

    if(MACa == MACb) {
        printf("\n Your MAC of recovered Ma is successfully veryfied by Bob side.");
    }

    return 0;
}