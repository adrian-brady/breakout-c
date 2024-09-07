#include "common.h"
#include "types.h"

// Returns the subpixel value given a grid pixel coordinate.
int getPixel(int pixel) { return (pixel * SIZE); }

// Stores the RGBA color of an SDL_Renderer for later restoration.
void storeColor(SDL_Renderer *renderer, Color *colors) {
  SDL_GetRenderDrawColor(renderer, &colors->red, &colors->green, &colors->blue,
                         &colors->alpha);
}

// Restores the RGBA color of an SDL_Renderer.
void restoreColor(SDL_Renderer *renderer, Color *colors) {
  SDL_SetRenderDrawColor(renderer, colors->red, colors->green, colors->blue,
                         colors->alpha);
}

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

bool checkCollision(Bar *bar, Ball *ball);

// Updates the ball's position. Checks for the ball hitting the outside border
// of the playspace. Additionally checks for collision with the paddle.
void updateBallPos(Ball *ball, SDL_Renderer *renderer, Bar *bar) {
  switch (ball->vdir) {
  case UP:
    if (ball->rect.y - SIZE > ball->neg_y_bound) {
      ball->rect.y -= SIZE;
    } else {
      ball->vdir = DOWN;
      ball->rect.y += SIZE;
    }
    break;
  case DOWN:
    if (ball->rect.y + SIZE < getPixel((bar->row / SIZE) + 5)) {
      ball->rect.y += SIZE;
    } else {
      // game ends
      ball->rect.y = -100;
      break;
    }
    break;
  case V_NONE:
    break;
  }

  switch (ball->hdir) {
  case RIGHT:
    if (ball->rect.x + SIZE < ball->pos_x_bound) {
      ball->rect.x += SIZE;
    } else {
      ball->hdir = LEFT;
      ball->rect.x -= SIZE;
    }
    break;
  case LEFT:
    if (ball->rect.x - SIZE > ball->neg_x_bound) {
      ball->rect.x -= SIZE;
    } else {
      ball->hdir = RIGHT;
      ball->rect.x += SIZE;
    }
    break;
  case H_NONE:
    break;
  }
  if (checkCollision(bar, ball)) {
    switch (ball->vdir) {
    case UP:
      ball->vdir = DOWN;
      break;
    case DOWN:
      ball->vdir = UP;
      break;
    case V_NONE:
      break;
    }

    switch (ball->hdir) {
    case RIGHT:
      ball->hdir = LEFT;
      break;
    case LEFT:
      ball->hdir = RIGHT;
      break;
    case H_NONE:
      break;
    }
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

// The time difference since the last frame draw.
double delta;

// returns a pre-initialized ball.
Ball initBall(enum VerticalDirection vdir, enum HorizontalDirection hdir) {
  Ball ball;
  ball.vdir = vdir;
  ball.hdir = hdir;
  ball.rect.x = 0;
  ball.rect.y = 0;
  ball.rect.h = SIZE;
  ball.rect.w = SIZE;
  ball.neg_x_bound = LEFT_COLUMN_BOUND;
  ball.neg_y_bound = TOP_ROW_BOUND;
  ball.pos_x_bound = RIGHT_COLUMN_BOUND;
  ball.pos_y_bound = BOTTOM_ROW_BOUND;

  return ball;
}

// Returns a pre-initialized paddle.
void initBar(Bar *bar) {
  bar->row = getPixel((WINDOW_HEIGHT / SIZE) - 5);
  bar->width = 5;
  bar->pos = (WINDOW_WIDTH - getPixel(bar->width)) / 2;
  bar->pos = getPixel((bar->pos / SIZE) + 4);
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

// Checks if a point is within 2 bounds on an axis.
bool isInBounds(int b1, int b2, int p1) {
  if (p1 >= b1 && p1 <= b2)
    return true;
  return false;
}

// Checks for collision between a paddle and a ball.
bool checkCollision(Bar *bar, Ball *ball) {
  // Determines next move horizontal component
  int ball_x;
  if (ball->hdir == RIGHT) {
    ball_x = ball->rect.x + SIZE;
  } else if (ball->hdir == LEFT) {
    ball_x = ball->rect.x - SIZE;
  } else {
    ball_x = ball->rect.x;
  }

  // Determines next move vertical component.
  int ball_y;
  if (ball->vdir == UP) {
    ball_y = ball->rect.y - SIZE;
  } else if (ball->vdir == DOWN) {
    ball_y = ball->rect.y + SIZE;
  } else {
    ball_y = ball->rect.y;
  }

  // Check bounds for vertical and horizontal points
  bool xBound = isInBounds(bar->pos, bar->pos + (bar->width * SIZE), ball_x);
  bool yBound = isInBounds(bar->row, bar->row + SIZE, ball_y);
  if (xBound && yBound) {
    printf("bound by both x and y\n");
    return true;
  } else if (xBound) {
    printf("bound by x\n");
  } else if (yBound) {
    printf("bound by y\n");
  } else {
    printf("not bound\n");
  }

  return false;
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

// Array of keys used for scanning keys in the event loop.
bool KEYS[322] = {0};

// Game loop
bool loop = true;

// Event handler
void keyboard() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    // check for messages
    switch (event.type) {
    // exit if the window is closed
    case SDL_QUIT:
      loop = false; // set game state to done,(do what you want here)
      break;
    // check for keypresses
    case SDL_KEYDOWN:
      if (event.key.keysym.sym < 322 && event.key.keysym.sym >= 0)
        KEYS[event.key.keysym.sym] = true;
      break;
    default:
      break;
    }
  }
}

void clearKeys() {
  for (int i = 0; i < 322; i++) {
    KEYS[0] = false;
  }
}

// The Global Paddle
Bar *gbar;

// Input handling
void handleInput() {
  if (KEYS[SDLK_d]) {
    barRight(gbar);
    KEYS[SDLK_d] = false;
  }
  if (KEYS[SDLK_a]) {
    barLeft(gbar);
    KEYS[SDLK_a] = false;
  }
  if (KEYS[SDLK_ESCAPE] || KEYS[SDLK_q]) {
    loop = false;
  }
}

int main() {
  SDL_Event event;
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

  while (loop) {

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
