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

    AppendObject("name", 0, (int[]){150,150}); // test code for objects
    CreateShape("name", 3, 60);

    BOOL running = TRUE;
    while (running) {
        // 1. Process standard OS messages
        running = ProcessWindowMessages();

        DrawObject("name");

        // 3. Command Windows to instantly update the viewport display area
        InvalidateRect(hwnd, NULL, FALSE);

        // 4. Force the loop to pause if it's moving too fast
        cap_frame_rate();
    }

    cleanup_timer();
    return 0;
}