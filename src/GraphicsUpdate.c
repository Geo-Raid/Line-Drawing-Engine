#include <stdio.h>
#include "Window.h"
#include "Tools.h"
#include "Graphics.h"
#include "TimeKeep.h"
#include "ObjectFunctions.h"

void UpdateGraphics() {
    ClearBuffer();
    DrawObject("Player");
    DrawObject("test");
    return;
}