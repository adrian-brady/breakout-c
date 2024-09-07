#include "ball.h"
#include "bar.h"
#include "common.h"
#include "drawing.h"
#include "game.h"
#include "input.h"
#include "types.h"
#include "utils.h"

// The time difference since the last frame draw.
double delta;

// Game loop
extern bool gloop;

// The Global Paddle
extern Bar *gbar;

int main() {
  init_globals();
  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
                              &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_Init(SDL_INIT_VIDEO);

  unsigned int a, b = SDL_GetTicks(), SDL_GetTicks();

  gbar = (Bar *)malloc(sizeof(Bar));
  Bar *bar = gbar;
  Ball ball = initBall(DOWN, RIGHT);
  initBar(bar);
  bool play = true;

  while (gloop) {

    a = SDL_GetTicks();
    delta = a - b;
    keyboard();

    if (delta > 1000 / 10.0 && play) {
      handleInput();
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      printf("fps: %f\n", 1000 / delta);

      drawVerticalLine(0, renderer);
      drawVerticalLine(getPixel(COUNT - 1), renderer);
      drawHorizontalLine(0, renderer);

      updateBallPos(&ball, renderer, bar);
      drawBar(renderer, bar);

      b = a;

      drawBall(&ball, renderer);
      // printf("x: %d, y: %d\n", ball.rect.x, ball.rect.y);
      if (ball.rect.y < 0) {
        play = false;
        printf("You Lost!\n");
      }
      SDL_RenderPresent(renderer);
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
