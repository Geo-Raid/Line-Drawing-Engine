#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graphics.h"
#include "Tools.h"

#define PI 3.1415926

int AddLine(char *name, double x1, double y1, double x2, double y2, unsigned int color) {
    int ObjectIndex = GetIndexOfObject(name);
    if (ObjectIndex == -1) return 0; // Returns if Object is not in ScreenObjects

    // Adds the specified line to the Object
    ScreenObjects[ObjectIndex].Sides[ScreenObjects[ObjectIndex].SideNumber] = (struct Line){x1, y1, x2, y2, color};
    ScreenObjects[ObjectIndex].SideNumber++; // Increments the number of sides in the Object
    return 0;
}

int RemoveLine(char *name, int SideToRemove) {
    int ObjectIndex = GetIndexOfObject(name);
    if (ObjectIndex == -1) return 0; // Returns if Object is not in ScreenObjects

    struct Line Remove = {0.0, 0.0, 0.0, 0.0, 0, ""}; // Change this later for better code

    ScreenObjects[ObjectIndex].Sides[SideToRemove] = Remove;

    for (int i = 0; i < ScreenObjects[ObjectIndex].SideNumber; i++) {
        if (ScreenObjects[ObjectIndex].Sides[i].x1 == 0 && ScreenObjects[ObjectIndex].Sides[i].x2 == 0) {
            for (int j = i; j < ScreenObjects[ObjectIndex].SideNumber; j++) {
                ScreenObjects[ObjectIndex].Sides[j] = ScreenObjects[ObjectIndex].Sides[j + 1]; 
            }
            return 0;
        }
    }

    return 0;
}

int RemoveAllLines(char *name) {
    int ObjectIndex = GetIndexOfObject(name);
    if (ObjectIndex == -1) return 0; // Returns if Object is not in ScreenObjects
    memset(ScreenObjects[ObjectIndex].Sides, 0, sizeof(ScreenObjects[ObjectIndex].Sides) * 6);

    return 0;
}

int MoveObject(char *name, int dx, int dy) {
    int ObjectIndex = GetIndexOfObject(name);
    if (ObjectIndex == -1) return 0; // Returns if Object is not in ScreenObjects

    for (int i = 0; i < ScreenObjects[ObjectIndex].SideNumber; i++) {
        ScreenObjects[ObjectIndex].Sides[i].x1 += dx;
        ScreenObjects[ObjectIndex].Sides[i].y1 += dy;
        ScreenObjects[ObjectIndex].Sides[i].x2 += dx;
        ScreenObjects[ObjectIndex].Sides[i].y2 += dy;
    }

    ScreenObjects[ObjectIndex].Origin[0] += dx;
    ScreenObjects[ObjectIndex].Origin[1] += dy;

    return 0;
}

int CreateShape(char *name, int sides, int length) {
    int ObjectIndex = GetIndexOfObject(name);
    if (ObjectIndex == -1) return 0; // Returns if Object is not in ScreenObjects
    
    if (sides < 3) return 0; // A polygon must have at least 3 sides

    unsigned int LineColor = 0x00FFFFFF;
    
    double CenterX = ScreenObjects[ObjectIndex].Origin[0];
    double CenterY = ScreenObjects[ObjectIndex].Origin[1];

    // Calculate the radius (distance from center to vertices)
    double Radius = length / (2.0 * sin(PI / sides));
    double xp, yp, xp2, yp2;
    double TurnAngle = (2.0 * PI) / sides;
    double NextAngle;
    
    double CurrentAngle = PI * 3 / 2; 

    for (int i = 0; i < sides; i++) {
        xp = CenterX + Radius * cos(CurrentAngle);
        yp = CenterY + Radius * sin(CurrentAngle);

        NextAngle = CurrentAngle + TurnAngle;
        xp2 = CenterX + Radius * cos(NextAngle);
        yp2 = CenterY + Radius * sin(NextAngle);

        AddLine(name, xp, yp, xp2, yp2, LineColor);

        CurrentAngle += TurnAngle;
    }

    // Calculates the Internal radius of the shape
    double radius = length / (2 * tan(PI / (double)sides));
    ScreenObjects[ObjectIndex].InternalRadius = radius;
    return 0;
}

void RotateObject(char *name, double angle) {
    int ObjectIndex = GetIndexOfObject(name);
    if (ObjectIndex == -1) return; // Returns if Object is not in ScreenObjects

    int Origin[2] = {ScreenObjects[ObjectIndex].Origin[0], ScreenObjects[ObjectIndex].Origin[1]};
    double rad = angle * (PI / 180.0);

    double x1, y1, x2, y2;

    for (int i = 0; i < ScreenObjects[ObjectIndex].SideNumber; i++) {
        x1 = ScreenObjects[ObjectIndex].Sides[i].x1 - Origin[0];
        y1 = ScreenObjects[ObjectIndex].Sides[i].y1 - Origin[1];
        x2 = ScreenObjects[ObjectIndex].Sides[i].x2 - Origin[0];
        y2 = ScreenObjects[ObjectIndex].Sides[i].y2 - Origin[1];

        ScreenObjects[ObjectIndex].Sides[i].x1 = x1 * cos(rad) - y1 * sin(rad) + Origin[0];
        ScreenObjects[ObjectIndex].Sides[i].y1 = x1 * sin(rad) + y1 * cos(rad) + Origin[1];
        ScreenObjects[ObjectIndex].Sides[i].x2 = x2 * cos(rad) - y2 * sin(rad) + Origin[0];
        ScreenObjects[ObjectIndex].Sides[i].y2 = x2 * sin(rad) + y2 * cos(rad) + Origin[1];
    }

}

int CheckCollision(char *object, char *CollisionObject) {
    int ObjectIndex = GetIndexOfObject(object);
    if (ObjectIndex == -1) return -1; // Returns if Object is not in ScreenObjects

    int CollisionObjectIndex = GetIndexOfObject(CollisionObject);
    if (CollisionObjectIndex == -1) return -1; // Returns if Object is not in ScreenObjects

    double dx = (double)ScreenObjects[ObjectIndex].Origin[0] - ScreenObjects[CollisionObjectIndex].Origin[0];
    double dy = (double)ScreenObjects[ObjectIndex].Origin[1] - ScreenObjects[CollisionObjectIndex].Origin[1];
    double Distance = sqrt(dx * dx + dy * dy);

    double CombinedRadius = ScreenObjects[ObjectIndex].InternalRadius + ScreenObjects[CollisionObjectIndex].InternalRadius;

    if (Distance <= CombinedRadius)
        return 1;

    return 0;
}