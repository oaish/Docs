#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

void disp(int n, float c[][3]) {
    float maxx, maxy;
    int i;
    maxx = getmaxx();
    maxy = getmaxy();
    maxx = maxx / 2;
    maxy = maxy / 2;

    for (i = 0; i < n - 1; i++) {
        line(maxx + c[i][0], maxy - c[i][1], maxx + c[i + 1][0], maxy - c[i + 1][1]);
    }
    line(maxx + c[n - 1][0], maxy - c[n - 1][1], maxx + c[0][0], maxy - c[0][1]);

    setcolor(GREEN);
    line(0, maxy, maxx * 2, maxy); // X-axis
    line(maxx, 0, maxx, maxy * 2); // Y-axis
    setcolor(WHITE);
}

void mul(int n, float b[][3], float c[][3], float a[][3]) {
    int i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++)
            a[i][j] = 0;

    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++) {
                a[i][j] += c[i][k] * b[k][j];
            }
}

void translation(int n, float c[][3], float tx, float ty) {
    int i;
    for (i = 0; i < n; i++) {
        c[i][0] += tx;
        c[i][1] += ty;
    }
}

void scaling(int n, float c[][3], float sx, float sy) {
    float b[3][3], a[10][3]; // Corrected size for b and a
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            b[i][j] = 0;

    for (i = 0; i < 3; i++)
        b[i][i] = 1;

    b[0][0] *= sx; // Scaling for x-axis
    b[1][1] *= sy; // Scaling for y-axis
    b[2][2] = 1;

    mul(n, b, c, a);
    setcolor(GREEN);
    disp(n, a);
}

void rotation(int n, float c[][3], float ra) {
    int i;
    float b[3][3], a[10][3];
    float cosA = cos(ra * M_PI / 180);
    float sinA = sin(ra * M_PI / 180);
    
    for (i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            b[i][j] = 0;

    b[0][0] = cosA;
    b[0][1] = sinA;
    b[1][0] = -sinA;
    b[1][1] = cosA;
    b[2][2] = 1;

    mul(n, b, c, a);
    setcolor(RED);
    disp(n, a);
}

void reflection(int n, float c[][3]) {
    float b[3][3], a[10][3];
    int i, ch, j;
    cleardevice();
    printf("\n\t* * MENU * *");
    printf("\n\t1) ABOUT X-AXIS");
    printf("\n\t2) ABOUT Y-AXIS");
    printf("\n\t3) ABOUT ORIGIN");
    printf("\t4) ABOUT X=Y");
    printf("\n\t5) ABOUT X=-Y");
    printf("\n\t6) EXIT");
    printf("\n\tENTER YOUR CHOICE: ");
    scanf("%d", &ch);
    cleardevice();
    disp(n, c);

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            b[i][j] = 0;

    for (i = 0; i < 3; i++)
        b[i][i] = 1;

    switch (ch) {
        case 1: // Reflection about X-axis
            b[1][1] = -1;
            break;
        case 2: // Reflection about Y-axis
            b[0][0] = -1;
            break;
        case 3: // Reflection about Origin
            b[0][0] = -1;
            b[1][1] = -1;
            break;
        case 4: // Reflection about X=Y
            b[0][0] = 0;
            b[1][1] = 0;
            b[0][1] = 1;
            b[1][0] = 1;
            break;
        case 5: // Reflection about X=-Y
            b[0][0] = 0;
            b[1][1] = 0;
            b[0][1] = -1;
            b[1][0] = -1;
            break;
        case 6:
            return; // Exit without doing anything
        default:
            printf("\n\tINVALID CHOICE!");
            return;
    }

    mul(n, b, c, a);
    setcolor(RED);
    disp(n, a);
}

void shearing(int n, float c[][3]) {
    float b[3][3], sh, a[10][3];
    int i, ch, j;
    cleardevice();
    printf("\n\t* * * MENU * * *");
    printf("\n\t1) X SHEARING");
    printf("\n\t2) Y SHEARING");
    printf("\n\t3) EXIT");
    printf("\n\tENTER YOUR CHOICE: ");
    scanf("%d", &ch);
    
    if (ch == 3) return;
    
    printf("\n\tENTER THE VALUE for SHEARING: ");
    scanf("%f", &sh);
    cleardevice();

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            b[i][j] = 0;

    for (i = 0; i < 3; i++)
        b[i][i] = 1;

    switch (ch) {
        case 1: // X Shearing
            b[1][0] = sh;
            break;
        case 2: // Y Shearing
            b[0][1] = sh;
            break;
        default:
            printf("\n\tINVALID CHOICE!");
            return;
    }

    mul(n, b, c, a);
    setcolor(RED);
    disp(n, a);
}

void main() {
    int i, cho, n, gd = DETECT, gm;
    float c[10][3], tx, ty, sx, sy, ra;

    initgraph(&gd, &gm, "C:\\turboc3\\bgi");
    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter the co-ordinates of the %d vertex: ", i + 1);
        scanf("%f%f", &c[i][0], &c[i][1]);
        c[i][2] = 1; // Homogeneous coordinates
    }

    do {
        clrscr();
        cleardevice();
        printf("\n\t\t\t * * * MENU * * *");
        printf("\n\t 1) TRANSLATION");
        printf("\n\t 2) SCALING ");
        printf("\n\t 3) ROTATION ");
        printf("\n\t 4) REFLECTION ");
        printf("\n\t 5) SHEARING");
        printf("\n\t 6) EXIT");
        printf("\n\t ENTER YOUR CHOICE: ");
        scanf("%d", &cho);
        
        switch (cho) {
            case 1:
                printf("\n\tEnter translation factor for X & Y axis: ");
                scanf("%f%f", &tx, &ty);
                cleardevice();
                setcolor(WHITE);
                disp(n, c);
                translation(n, c, tx, ty);
                setcolor(YELLOW);
                disp(n, c);
                getch();
                break;
            case 2:
                printf("\n\tEnter scaling factor for X & Y axis: ");
                scanf("%f%f", &sx, &sy);
                cleardevice();
                setcolor(WHITE);
                disp(n, c);
                scaling(n, c, sx, sy);
                getch
