#include "collision.h"
#include "common.h"
#include "types.h"
#include "utils.h"

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
