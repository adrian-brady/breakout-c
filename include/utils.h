#ifndef UTILS_H
#define UTILS_H

#include "common.h"
#include "types.h"

int getPixel(int pixel);
void storeColor(SDL_Renderer* renderer, Color* color);
void restoreColor(SDL_Renderer* renderer, Color* color);

#endif
