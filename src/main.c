#include <stdio.h>
#include "Window.h"
#include "Tools.h"
#include "Graphics.h"
#include "TimeKeep.h"
#include "ObjectFunctions.h"

int main(void) {
    HWND hwnd = NULL;
    
    if (!CreateAppWindow(&hwnd)) {
        return -1;
    }

    // Target a smooth retro cap, like 60 FPS
    init_timer(60.0);

    AppendObject("triangle1", 0, (int[]){SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2}); // test code for objects
    CreateShape("triangle1", 3, 80);
    AppendObject("name", 0, (int[]){300, 200}); // test code for objects
    CreateShape("name", 3, 50);

    BOOL running = TRUE;
    while (running) {
        // 1. Process standard OS messages
        running = ProcessWindowMessages();

        printf("Collision: %d\n", CheckCollision("name", "triangle1"));

        ClearBuffer();
        DrawObject("triangle1");
        DrawObject("name");
        // 3. Command Windows to instantly update the viewport display area
        InvalidateRect(hwnd, NULL, FALSE);

        // 4. Force the loop to pause if it's moving too fast
        cap_frame_rate();
    }

    cleanup_timer();
    return 0;
}