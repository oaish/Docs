#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void main() {
    int n, i, j, k, gd, gm, dy, dx;
    int x, y, temp;
    int a[20][2], xi[20];
    float slope[20];

    clrscr();
    printf("\n\n\tEnter the number of edges of the polygon: ");
    scanf("%d", &n);

    printf("\n\n\tEnter the coordinates of the polygon:\n\n");
    for (i = 0; i < n; i++) {
        printf("\tX%d Y%d: ", i, i);
        scanf("%d%d", &a[i][0], &a[i][1]);
    }

    // Closing the polygon
    a[n][0] = a[0][0];
    a[n][1] = a[0][1];

    // Initialize graphics mode
    detectgraph(&gd, &gm);
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    /* Draw Polygon */
    for (i = 0; i < n; i++) {
        line(a[i][0], a[i][1], a[i + 1][0], a[i + 1][1]);
    }

    getch(); // Wait for a key press before filling

    // Calculate slopes
    for (i = 0; i < n; i++) {
        dy = a[i + 1][1] - a[i][1];
        dx = a[i + 1][0] - a[i][0];
        
        // Check for special cases for slope calculation
        if (dy == 0) slope[i] = 0.0;  // Horizontal line
        else if (dx == 0) slope[i] = 1.0; // Vertical line
        else slope[i] = (float)dx / dy; // Calculate slope
    }

    // Scanline fill
    for (y = 0; y < getmaxy(); y++) {
        k = 0;
        for (i = 0; i < n; i++) {
            // Check for intersection with the scanline
            if (((a[i][1] <= y) && (a[i + 1][1] > y)) || 
                ((a[i][1] > y) && (a[i + 1][1] <= y))) ) {
                xi[k] = (int)(a[i][0] + slope[i] * (y - a[i][1]));
                k++;
            }
        }

        // Sort x-intersections
        for (j = 0; j < k - 1; j++) {
            for (i = 0; i < k - 1; i++) {
                if (xi[i] > xi[i + 1]) {
                    temp = xi[i];
                    xi[i] = xi[i + 1];
                    xi[i + 1] = temp;
                }
            }
        }

        // Fill between pairs of intersections
        setcolor(3);
        for (i = 0; i < k; i += 2) {
            line(xi[i], y, xi[i + 1], y);
        }
    }

    getch(); // Wait for user input before closing
    closegraph(); // Close graphics mode
}
