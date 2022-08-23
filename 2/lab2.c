#include <stdio.h>

int main () {

    char secret_key[20];
    printf("Enter the secret key : ");
    gets(secret_key);

    int check[26];
    for(int i=0; i<26; i++) {
        check[i] = 0;
    }

    char key[5][5];
    int m=0, n=0;


    for(int i=0; i<20; i++) {
        if(secret_key[i]>='a' && secret_key[i]<='z' && (check[secret_key[i]-'a']==0)) {
            if(secret_key[i]=='j') {
                secret_key[i] = 'i';
            }
            key[m/5][n%5] = secret_key[i];
            m++;
            n++;
            check[secret_key[i]-'a'] = 1;
        }
    }
    
    for(int i=0; i<26; i++) {
        if(check[i] == 0 && i!=10) {
            key[m/5][n%5] = i+'a';
            m++;
            n++;
        }

    }

    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }

    char str1[4];
    printf("Enter plain text : ");
    scanf("%s", &str1);

    char cipher[4];
    char plain[4];

    char a,b;
    int x1,y1,x2,y2,i;
    for(i=0; i<4; i+=2) {
        a = str1[i];
        b = str1[i+1];

        for(int m=0; m<5; m++) {
            for(int n=0; n<5; n++) {
                if(key[m][n]==a) {
                    x1 = m;
                    y1 = n;
                }
                if(key[m][n]==b) {
                    x2 = m;
                    y2 = n;
                }
            }
        }

        if(y1==y2) {
            a = key[(x1+1)%5][y1];
            b = key[(x2+1)%5][y2];
        }
        else if(x1==x2) {
            a = key[x1][(y1+1)%5];
            b = key[x2][(y2+1)%5];
        }
        else {
            a = key[x1][y2];
            b = key[x2][y1];
        }
        
        cipher[i] = a;
        cipher[i+1] = b;
    }

    cipher[i] = '\0';

    printf("cipher text : %s",cipher);


    for(i=0; i<4; i+=2) {
        a = cipher[i];
        b = cipher[i+1];

        for(int m=0; m<5; m++) {
            for(int n=0; n<5; n++) {
                if(key[m][n]==a) {
                    x1 = m;
                    y1 = n;
                }
                if(key[m][n]==b) {
                    x2 = m;
                    y2 = n;
                }
            }
        }

        if(y1==y2) {
            a = key[(x1-1)%5][y1];
            b = key[(x2-1)%5][y2];
        }
        else if(x1==x2) {
            a = key[x1][(y1-1+5)%5];
            b = key[x2][(y2-1+5)%5];
        }
        else {
            a = key[x1][y2];
            b = key[x2][y1];
        }
        
        plain[i] = a;
        plain[i+1] = b;
    }

    plain[i] = '\0';

    printf("\nplain text : %s",plain);

    return 0;
}