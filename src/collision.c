#include "collision.h"
#include "types.h"

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

// Checks if a point is within 2 bounds on an axis.
bool isInBounds(int b1, int b2, int p1) {
  if (p1 >= b1 && p1 <= b2)
    return true;
  return false;
}
