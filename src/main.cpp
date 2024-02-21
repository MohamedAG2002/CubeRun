#include "core/game.h"

int main()
{
  game_init(800, 600, "Cube Run");
  game_run();
  game_shutdown();
}
