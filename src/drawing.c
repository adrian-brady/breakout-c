#include "common.h"
#include "types.h"
#include "utils.h"

// Draws a vertical line from the top of the window to the bottom.
// Used for drawing wall columns
void drawVerticalLine(int pos, SDL_Renderer *renderer) {
  SDL_Rect rect;
  rect.x = pos;
  rect.w = SIZE;
  rect.h = SIZE;

  for (int i = 0; i < WINDOW_HEIGHT; i += SIZE) {
    rect.y = i;
    SDL_RenderFillRect(renderer, &rect);
  }
}

// Draws a horizontal line from the left of the window to the right.
// Used for drawing border wall.
void drawHorizontalLine(int pos, SDL_Renderer *renderer) {
  SDL_Rect rect;
  rect.y = pos;
  rect.w = SIZE;
  rect.h = SIZE;

  for (int i = 0; i < WINDOW_WIDTH; i += SIZE) {
    rect.x = i;
    SDL_RenderFillRect(renderer, &rect);
  }
}

// Draws the ball to the renderer
void drawBall(Ball *ball, SDL_Renderer *renderer) {

  Color old;
  storeColor(renderer, &old);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &ball->rect);

  restoreColor(renderer, &old);
}

// Draws the paddle to the renderer.
void drawBar(SDL_Renderer *renderer, Bar *bar) {
  Color old;
  storeColor(renderer, &old);

  SDL_Rect rect;
  rect.x = bar->pos;
  rect.y = bar->row;
  rect.w = bar->width * SIZE;
  rect.h = SIZE;

  // printf("x: %d, y: %d, w: %d, h: %d\n", rect.x, rect.y, rect.w, rect.h);

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, &rect);

  restoreColor(renderer, &old);
}
