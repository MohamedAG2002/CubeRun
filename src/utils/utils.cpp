#include "utils.h"
#include "core/defines.h"

#include <random>

// Globals
///////////////////////////////////////////////////////////////
static std::random_device rand_device;
static std::default_random_engine engine(rand_device());
///////////////////////////////////////////////////////////////

// Utils functions
////////////////////////////////////////////////
i32 get_random_int()
{
  std::uniform_int_distribution<i32> uniform_dist;
  return uniform_dist(engine);
}

i32 get_random_int(i32 min, i32 max)
{
  std::uniform_int_distribution<i32> uniform_dist(min, max);
  return uniform_dist(engine);
}
////////////////////////////////////////////////
