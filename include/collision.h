#ifndef COLLISION_H
#define COLLISION_H

#include "common.h"
#include "types.h"

bool checkCollision(Bar *bar, Ball *ball);
bool isInBounds(int b1, int b2, int p1);

#endif
