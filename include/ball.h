#ifndef BALL_H
#define BALL_H

#include "common.h"
#include "types.h"

void updateBallPos(Ball *ball, SDL_Renderer *renderer, Bar *bar);
Ball initBall(enum VerticalDirection vdir, enum HorizontalDirection hdir);

#endif
