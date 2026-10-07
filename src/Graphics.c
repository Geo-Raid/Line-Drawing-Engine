#include <stdlib.h>
#include "Tools.h"
#include <math.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define DISPLAY_SCALE 2

unsigned int frameBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

int DrawLine(int x1, int y1, int x2, int y2, unsigned int color) {
    if (x1 < 0 || x1 > SCREEN_WIDTH || x2 < 0 || x2 > SCREEN_WIDTH ||
        y1 < 0 || y1 > SCREEN_HEIGHT || y2 < 0 || y2 > SCREEN_HEIGHT)
        return -1;

    int dx = abs(x2 - x1);
    int stepX = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int stepY = y1 < y2 ? 1 : -1;
    int error = dx + dy;

    while (!(x1 == x2) || !(y1 == y2)) {
        frameBuffer[y1][x1] = color;

        int doubledError = 2 * error;
        if (doubledError >= dy) {
            error += dy;
            x1 += stepX;
        }
        if (doubledError <= dx) {
            error += dx;
            y1 += stepY;
        }
    }

    return 1;
}


int DrawObject(char *name) {
    int ObjectIndex = GetIndexOfObject(name);
    
    if (ObjectIndex == -1) return 0;

    for (int i = 0; i < ScreenObjects[ObjectIndex].SideNumber; i++) {
        struct Line line = ScreenObjects[ObjectIndex].Sides[i];

        DrawLine(line.x1, line.y1, line.x2, line.y2, line.color);
    }

    return 0;
}

void ClearBuffer() {
    memset(frameBuffer, 0, sizeof(frameBuffer[0][0]) * SCREEN_HEIGHT * SCREEN_WIDTH);
}