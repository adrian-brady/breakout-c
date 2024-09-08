#ifndef DRAWING_H
#define DRAWING_H

#include "common.h"
#include "types.h"

// drawVerticalLine
void drawVerticalLine(int pos, SDL_Renderer *renderer);
// drawHorizontalLine
void drawHorizontalLine(int pos, SDL_Renderer *renderer);
// drawBall
void drawBall(Ball *ball, SDL_Renderer *renderer);
// drawBar
void drawBar(SDL_Renderer *renderer, Bar *bar);

#endif
