#include "types.h"

Bar *gbar;
bool gloop;

void init_globals() {
  gbar = (Bar *)malloc(sizeof(Bar));
  gloop = true;
}
