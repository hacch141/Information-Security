#include <stdio.h>

int main () {
    char p, c;
    int a, b;
    int pInt, cInt, key;
    printf("Enter the plain text : ");
    scanf("%c", &p);
    printf("Enter the value of (a,b) : ");
    scanf("%d %d", &a, &b);
    pInt = p - 'a';
    cInt = ((a*pInt)+b)%26;
    c = cInt+'a';

    printf("\n");
    printf("---- Encryption : ----");
    printf("\nYour cipher text : %c", c);

    int aInv = 0;

    int fg = 0;
    for(int i=0; i<26; i++) {
        fg = (a*i)%26;

        if(fg == 1) {
            aInv = i;
        }
    }

    pInt = (aInv*(cInt+26-b))%26;
    p = pInt + 'a';

    printf("\n\n");
    printf("---- Decryption : ----");
    printf("\nYour plain text : %c", p);

    return 0;
}