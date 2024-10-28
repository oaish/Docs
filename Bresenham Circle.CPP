#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

void symm(int x, int y, int xc, int yc);

void draw_circle(int xc, int yc, int r) {
    int x = 0, y = r, p = 1 - r;
    symm(x, y, xc, yc);

    for (x = 0; x < y; x++) {
        if (p < 0) {
            p += 2 * x + 3;
        } else {
            p += 2 * (x - y) + 5;
            y--;
        }
        symm(x, y, xc, yc);
        delay(10);
    }
}

void main() {
    int x0, y0, r;
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

    printf("Enter center coordinates:\n");
    scanf("%d%d", &x0, &y0);
    printf("Enter radius:\n");
    scanf("%d", &r);

    draw_circle(x0, y0, r);

    getch();
    closegraph();
}

void symm(int x, int y, int xc, int yc) {
    putpixel(xc + x, yc - y, YELLOW);
    putpixel(xc + y, yc - x, YELLOW);
    putpixel(xc + y, yc + x, YELLOW);
    putpixel(xc + x, yc + y, YELLOW);
    putpixel(xc - x, yc + y, YELLOW);
    putpixel(xc - y, yc + x, YELLOW);
    putpixel(xc - y, yc - x, YELLOW);
    putpixel(xc - x, yc - y, YELLOW);
}
