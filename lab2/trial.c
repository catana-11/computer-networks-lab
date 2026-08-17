#include <stdio.h>

int main() {

    int h[7];

    printf("Enter 4 data bits from msb to lsb: ");
    scanf("%d %d %d %d", &h[6], &h[5], &h[4], &h[2]);

    int x = h[2] + h[4] + h[6];
    if (x%2==0){
        x = 0;
    }
    else x=1;

    int y = h[5] + h[6];
    if (y%2==0){
        y = 0;
    }
    else y=1;


    int z = h[4] + h[5] + h[6];
    if (z%2==0){
        z = 0;
    }
    else z=1;


    h[0] = x; h[1] = y; h[3] = z;


    printf("\nhamming code: ");
    for (int i = 6; i >= 0; i--)
        printf("%d", h[i]);

    printf("\n");

    return 0;
}
