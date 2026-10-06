#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIDE_NUMBER 30
#define MAX_OBJECT_NAME_LENGTH 30
#define MAX_NUMBER_OF_OBJECTS 50

#include "Graphics.h"

struct Line {
    double x1;
    double y1;
    double x2;
    double y2;
    unsigned int color;
    char uid[5];
};


struct ScreenObject {
    char Name[MAX_OBJECT_NAME_LENGTH];
    int SideNumber;
    int Origin[2];
    struct Line Sides[MAX_SIDE_NUMBER];
};

struct ScreenObject ScreenObjects[MAX_NUMBER_OF_OBJECTS];


int reduceObject() {
    int nextIndex = 0;

    for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++) {
        if (ScreenObjects[i].Name[0] != '\0') {
            if (nextIndex != i) {
                ScreenObjects[nextIndex] = ScreenObjects[i];
            }
            nextIndex++;
        }
    }

    for (int i = nextIndex; i < MAX_NUMBER_OF_OBJECTS; i++) {
        memset(&ScreenObjects[i], 0, sizeof(ScreenObjects[i]));
    }

    return 0;
}


int AppendObject(char *name, int sidenumber, int *origin) {
    if (name == NULL || origin == NULL) return -1;

    reduceObject();
    for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++) {
        if (ScreenObjects[i].Name[0] == '\0') {
            memset(&ScreenObjects[i], 0, sizeof(ScreenObjects[i]));
            snprintf(ScreenObjects[i].Name, sizeof(ScreenObjects[i].Name), "%s", name);
            ScreenObjects[i].SideNumber = sidenumber;
            memcpy(ScreenObjects[i].Origin, origin, sizeof(ScreenObjects[i].Origin));
            return 0;
        }
    }
    return -1;
}


int RemoveObject(char *name) {
    if (name == NULL) return -1;

    for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++) {
        if (strcmp(ScreenObjects[i].Name, name) == 0) {
            memset(&ScreenObjects[i], 0, sizeof(ScreenObjects[i]));
            return 0;
        }
    }
    return -1;
}

int GetIndexOfObject(char *name) {
    if (name == NULL) return -1;

    for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++) {
        if (ScreenObjects[i].Name[0] != '\0' && strcmp(ScreenObjects[i].Name, name) == 0) {
            return i;
        }
    }
    return -1;
}