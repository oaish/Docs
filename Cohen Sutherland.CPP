#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void main() {
    int rcode_begin[4] = {0, 0, 0, 0}, rcode_end[4] = {0, 0, 0, 0}, region_code[4];
    int W_xmax, W_ymax, W_xmin, W_ymin, flag = 0;
    float slope;
    int x, y, x1, y1, i;
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "C:\\tc\\bgi");
    printf("\n****** Cohen Sutherland Line Clipping Algorithm ***********");
    printf("\n Now, enter XMin, YMin = ");
    scanf("%d %d", &W_xmin, &W_ymin);
    printf("\n First enter XMax, YMax = ");
    scanf("%d %d", &W_xmax, &W_ymax);
    printf("\n Please enter initial point x and y = ");
    scanf("%d %d", &x, &y);
    printf("\n Now, enter final point x1 and y1 = ");
    scanf("%d %d", &x1, &y1);

    cleardevice();
    rectangle(W_xmin, W_ymin, W_xmax, W_ymax);
    line(x, y, x1, y1);
    line(0, 0, 600, 0); // X-axis
    line(0, 0, 0, 600); // Y-axis

    // Compute region codes for the beginning point
    if (y > W_ymax) {
        rcode_begin[0] = 1; // Top
    }
    if (y < W_ymin) {
        rcode_begin[1] = 1; // Bottom
    }
    if (x > W_xmax) {
        rcode_begin[2] = 1; // Right
    }
    if (x < W_xmin) {
        rcode_begin[3] = 1; // Left
    }

    // Compute region codes for the end point
    if (y1 > W_ymax) {
        rcode_end[0] = 1; // Top
    }
    if (y1 < W_ymin) {
        rcode_end[1] = 1; // Bottom
    }
    if (x1 > W_xmax) {
        rcode_end[2] = 1; // Right
    }
    if (x1 < W_xmin) {
        rcode_end[3] = 1; // Left
    }

    // Check if line is completely outside the clipping window
    flag = 1;
    for (i = 0; i < 4; i++) {
        region_code[i] = rcode_begin[i] && rcode_end[i];
        if (region_code[i] == 1) {
            flag = 0;
        }
    }

    if (flag == 0) {
        printf("\n Line is completely outside the window");
    } else {
        // Line needs clipping
        slope = (float)(y1 - y) / (x1 - x);

        // Clipping the beginning point
        if (rcode_begin[2] == 0 && rcode_begin[3] == 1) { // left
            y += (W_xmin - x) * slope;
            x = W_xmin;
        } 
        if (rcode_begin[2] == 1 && rcode_begin[3] == 0) { // right
            y += (W_xmax - x) * slope;
            x = W_xmax;
        } 
        if (rcode_begin[0] == 1 && rcode_begin[1] == 0) { // top
            x += (W_ymax - y) / slope;
            y = W_ymax;
        } 
        if (rcode_begin[0] == 0 && rcode_begin[1] == 1) { // bottom
            x += (W_ymin - y) / slope;
            y = W_ymin;
        }

        // Clipping the end point
        if (rcode_end[2] == 0 && rcode_end[3] == 1) { // left
            y1 += (W_xmin - x1) * slope;
            x1 = W_xmin;
        } 
        if (rcode_end[2] == 1 && rcode_end[3] == 0) { // right
            y1 += (W_xmax - x1) * slope;
            x1 = W_xmax;
        } 
        if (rcode_end[0] == 1 && rcode_end[1] == 0) { // top
            x1 += (W_ymax - y1) / slope;
            y1 = W_ymax;
        } 
        if (rcode_end[0] == 0 && rcode_end[1] == 1) { // bottom
            x1 += (W_ymin - y1) / slope;
            y1 = W_ymin;
        }
    }

    delay(1000);
    clearviewport();
    rectangle(W_xmin, W_ymin, W_xmax, W_ymax);
    line(0, 0, 600, 0);
    line(0, 0, 0, 600);
    setcolor(RED);
    line(x, y, x1, y1);

    getch();
    closegraph();
}
