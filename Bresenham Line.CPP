#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void bresenhamLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        putpixel(x0, y0, WHITE);
        delay(10);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int main() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

    int x0 = 50, y0 = 50, x1 = 500, y1 = 300;
    bresenhamLine(x0, y0, x1, y1);

    getch();
    closegraph();
    return 0;
}
