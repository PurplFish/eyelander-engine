#pragma once
#define MAX_ENTITIES 4096

typedef struct {
    float x, y;
    float rotation;
    float scaleX, scaleY;
} Transform;

typedef struct{
    Transform transforms [MAX_ENTITIES];
} ECS;