#include <stdio.h>

int main() {

    int h[7];

    printf("enter 4 data bits msb to lsb: ");  
    scanf("%d %d %d %d", &h[6], &h[5], &h[4], &h[2]);

    h[0] = (h[2] + h[4] + h[6]) % 2;
    h[1] = (h[2] + h[5] + h[6]) % 2;
    h[3] = (h[4] + h[5] + h[6]) % 2;

    printf("\nhamming code: ");
    for(int i = 6; i >=0; i--)
        printf("%d", h[i]);

    printf("\n\nenter received hamming code msb to lsb: ");

    scanf("%d %d %d %d %d %d %d", 
        &h[6], &h[5], &h[4], &h[3], &h[2], &h[1], &h[0]);

    int s1 = (h[0] + h[2] + h[4] + h[6]) % 2;
    int s2 = (h[1] + h[2] + h[5] + h[6]) % 2;
    int s4 = (h[3] + h[4] + h[5] + h[6]) % 2;

    int errorPos = s1 + (2 * s2) + (4 * s4);

    if(errorPos == 0) printf("\nno error detected\n");

    else{
        printf("\nerror detected at bit position %d.\n", errorPos);

        h[errorPos - 1] = h[errorPos-1] ^ 1;

        printf("corrected hamming code: ");
        for(int i = 6; i>=0; i--)
            printf("%d", h[i]);

        printf("\n");
    }

    printf("\nrecovered data bits: %d%d%d%d\n", h[6], h[5], h[4], h[2]);

    return 0;
}