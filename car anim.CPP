#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

void drawCar(int x, int y) {
    // Draw the body of the car
    rectangle(x, y, x + 100, y + 40);   // Main body
    rectangle(x + 15, y - 20, x + 85, y); // Top body

    // Draw the wheels
    circle(x + 25, y + 40, 10); // Left wheel
    circle(x + 75, y + 40, 10); // Right wheel
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI"); // Update this path to the BGI folder if necessary

    int x = 0, y = 200;  // Initial position of the car
    int maxX = getmaxx(); // Screen width

    while (!kbhit()) { // Run until a key is pressed
        // Clear the previous frame
        cleardevice();

        // Draw the car at the current position
        drawCar(x, y);

        // Delay to control the speed of the car
        delay(50);

        // Move the car to the right
        x += 10;

        // Reset position when the car reaches the end of the screen
        if (x > maxX) {
            x = 0;
        }
    }

    closegraph(); // Close the graphics mode
    return 0;
}
