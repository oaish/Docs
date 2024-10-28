#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
int round(double x) {
return (int)(x + 0.5);
}
int main() {
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
int x1, y1, x2, y2;
float x, y, xi, yi, dx, dy;
int k, s;
printf("Enter the coordinates of the first point (x1, y1): ");
scanf("%d %d", &x1, &y1);
printf("Enter the coordinates of the second point (x2, y2): ");
scanf("%d %d", &x2, &y2);
x = x1;
y = y1;
putpixel(x, y, WHITE);
dx = x2 - x1;
dy = y2 - y1;
if (abs(dx) > abs(dy)) {
s = abs(dx);
} else {
s = abs(dy);
}
printf("%f",s);
xi = dx / s;
yi = dy / s;
printf("\n %f %f",xi,yi);
for (k = 0; k < s; k++) {
x = x + xi;
y = y + yi;
putpixel(round(x), round(y), WHITE);
}
getch();
closegraph();
return 0;
}