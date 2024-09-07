#include "common.h"
#include "types.h"
#include "utils.h"

// Returns a pre-initialized paddle.
void initBar(Bar *bar) {
  bar->row = getPixel((WINDOW_HEIGHT / SIZE) - 5);
  bar->width = 5;
  bar->pos = (WINDOW_WIDTH - getPixel(bar->width)) / 2;
  bar->pos = getPixel((bar->pos / SIZE) + 4);
}

// Moves the paddle left one grid unit.
void barLeft(Bar *bar) {
  if (bar->pos - SIZE > LEFT_COLUMN_BOUND) {
    bar->pos = getPixel((bar->pos / SIZE) - 1);
  }
}

// Moves the paddle right one grid unit.
void barRight(Bar *bar) {
  if (bar->pos + SIZE < RIGHT_COLUMN_BOUND) {
    bar->pos = getPixel((bar->pos / SIZE) + 1);
  }
}
