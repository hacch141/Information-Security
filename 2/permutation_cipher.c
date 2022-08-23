#include <stdio.h>

int main () {
    
    char str1[5];

    printf("Enter plain text : ");
    scanf("%s", &str1);

    int key[2][5] = {{1,2,3,4,5},{3,2,1,4,5}};

    char cipher[5];
    for(int i=0; i<5; i++) {
        cipher[i] = str1[ key[1][i]-1 ];
    }
    cipher[5] = '\0';

    printf("Encrypted text : %s", cipher);

    char plain[5];
    for(int i=0; i<5; i++) {
        plain[ key[1][i]-1 ] = cipher[i];
    }
    plain[5] = '\0';

    printf("\nDecrypted text : %s", plain);

    return 0;
}