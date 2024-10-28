#include <graphics.h>
#include <conio.h>
#include <math.h>

void koch(int x1, int y1, int x2, int y2, int it) {
    // Angle for the Koch curve
    float angle = 60 * M_PI / 180;
    
    // Calculate the points
    int x3 = (2 * x1 + x2) / 3;
    int y3 = (2 * y1 + y2) / 3;
    int x4 = (x1 + 2 * x2) / 3;
    int y4 = (y1 + 2 * y2) / 3;
    
    // Calculate the apex point of the triangle
    int x = x3 + (x4 - x3) * cos(angle) - (y4 - y3) * sin(angle);
    int y = y3 + (x4 - x3) * sin(angle) + (y4 - y3) * cos(angle);
    
    // Recursive case
    if (it > 0) {
        koch(x1, y1, x3, y3, it - 1);
        koch(x3, y3, x, y, it - 1);
        koch(x, y, x4, y4, it - 1);
        koch(x4, y4, x2, y2, it - 1);
    } else {
        // Draw the line segments for the Koch curve
        line(x1, y1, x3, y3);
        line(x3, y3, x, y);
        line(x, y, x4, y4);
        line(x4, y4, x2, y2);
    }
}

int main(void) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    
    // Define the initial points for the Koch curve
    int x1 = 100, y1 = 400, x2 = 400, y2 = 400; // Set coordinates for a horizontal line
    
    // Call the Koch function with the desired depth of recursion
    koch(x1, y1, x2, y2, 4);
    
    getch(); // Wait for user input before closing
    closegraph(); // Close the graphics mode
    return 0;
}
