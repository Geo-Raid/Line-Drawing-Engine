#ifndef TOOLS_H
#define TOOLS_H

#include "Tools.c"

extern int reduceObject();
extern void AppendObject(char *name, int sidenumber, int *origin);

extern struct ScreenObject ScreenObjects[50];

extern int RemoveObject(char *name);
extern int GetIndexOfObject(char *name);

#endif