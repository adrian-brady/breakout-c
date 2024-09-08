#include "ball.h"
#include "bar.h"
#include "constants.h"
#include "drawing.h"
#include "input.h"
#include "types.h"
#include "utils.h"

Bar *gbar;
bool gloop;
bool playLoop;
Ball *gball;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void init_globals() {
  gbar = (Bar *)malloc(sizeof(Bar));
  gloop = true;
  gball = (Ball *)malloc(sizeof(Ball));
  playLoop = true;
  initBall(gball, DOWN, RIGHT);
  initBar(gbar);
}

void init_SDL() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
                              &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

int game_loop() {
  // The time difference since the last frame draw.
  double delta;
  unsigned int a, b = SDL_GetTicks(), SDL_GetTicks();

  while (gloop) {
    a = SDL_GetTicks();
    delta = a - b;
    keyboard();

    if (delta > 1000 / 10.0) {
      handleInput();
      if (playLoop) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        printf("fps: %f\n", 1000 / delta);

        drawVerticalLine(0, renderer);
        drawVerticalLine(getPixel(COUNT - 1), renderer);
        drawHorizontalLine(0, renderer);

        updateBallPos(gball, renderer, gbar);
        drawBar(renderer, gbar);

        b = a;

        drawBall(gball, renderer);
        // printf("x: %d, y: %d\n", ball.rect.x, ball.rect.y);
        if (gball->rect.y < 0) {
          playLoop = false;
          printf("You Lost!\n");
        }
        SDL_RenderPresent(renderer);
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

int game() {
  init_globals();
  init_SDL();

  game_loop();
}
