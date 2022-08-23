#include <stdio.h>

int main() {
    char p, c;
    int k, pInt, t1;
    printf("Enter the plain text : ");
    scanf("%c", &p);
    printf("Enter the key value : ");
    scanf("%d", &k);
    pInt = p - 'a';
    t1 = (pInt+k)%26;
    c = t1 + 'a';

    printf("\n");
    printf("---- Encryption : ----");
    printf("\nYour cipher text : %c", c);

    int cInt;
    cInt = c - 'a';
    t1 = (cInt+26-k)%26;
    p = t1 + 'a';
    printf("\n\n");
    printf("---- Decryption : ----");
    printf("\nYour plain text : %c", p);
}