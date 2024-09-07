#ifndef TYPES_H
#define TYPES_H

#include "common.h"

typedef struct Bar {
  int pos;
  int row;
  int width;
} Bar;

enum VerticalDirection {
  UP,
  DOWN,
  V_NONE,
};

enum HorizontalDirection {
  RIGHT,
  LEFT,
  H_NONE,
};

typedef struct Color {
  Uint8 red;
  Uint8 green;
  Uint8 blue;
  Uint8 alpha;
} Color;

typedef struct Ball {
  SDL_Rect rect;
  enum VerticalDirection vdir;
  enum HorizontalDirection hdir;
  int pos_x_bound;
  int pos_y_bound;
  int neg_x_bound;
  int neg_y_bound;
} Ball;

#endif
