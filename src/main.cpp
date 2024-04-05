#include "engine/core/game.h"

int main() {
  Game game;
  if(!game_init(game)) {
    return -1;
  }
  
  game_run(game);
  game_shutdown(game);
}
