#ifndef OBJECTFUNCTIONS_H
#define OBJECTFUNCTIONS_H

#include "ObjectFunctions.c"

extern int AddLine(char *name, double x1, double y1, double x2, double y2, unsigned int color);
extern int RemoveLine(char *name, int SideToRemove);
extern int MoveObject(char *name, int dx, int dy);
extern int CreateShape(char *name, int sides, int length);
extern void RotateObject(char *name, double angle);
extern int CheckCollision(char *object, char *CollisionObject);

#endif