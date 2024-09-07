#include "bar.h"
#include "game.h"

// Array of keys used for scanning keys in the event loop.
bool KEYS[322] = {0};

// Event handler
void keyboard() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    // check for messages
    switch (event.type) {
    // exit if the window is closed
    case SDL_QUIT:
      gloop = false; // set game state to done,(do what you want here)
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
    gloop = false;
  }
}
