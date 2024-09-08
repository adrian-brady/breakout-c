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
