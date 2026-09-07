/* gintest.c
 *
 * Simple test of Tektronix 4010 GIN mode.
 *
 * Sends ESC SUB to enter GIN mode.
 * After the user presses a key, reads:
 *
 *      key
 *      x high
 *      x low
 *      y high
 *      y low
 *      CR
 *
 * and prints the decoded coordinates.
 */

#include <stdio.h>

int main(void)
{
    int key;
    int xh, xl;
    int yh, yl;
    int cr;
    int x, y;

    printf("\033\032");      /* ESC SUB */
    fflush(stdout);

    while (1) {

        key = getchar();
        if (key == EOF)
            break;

        xh = getchar();
        xl = getchar();
        yh = getchar();
        yl = getchar();
        cr = getchar();

        x = ((xh - 0x20) << 5) + (xl - 0x20);
        y = ((yh - 0x20) << 5) + (yl - 0x20);

        printf("\n");
        printf("key = '%c' (%d)\n", key, key);
        printf("x   = %d\n", x);
        printf("y   = %d\n", y);
        printf("\n");

        printf("\033\032");
        fflush(stdout);
    }

    return 0;
}