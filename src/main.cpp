#include "game/game.h"

int main() {
  if(!game_init()) {
    return -1;
  }
  
  game_run();
  game_shutdown();
}
