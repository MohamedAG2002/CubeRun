#include "rand.h"
#include "engine/defines.h"

#include <random>

// GLOBALS
/////////////////////////////////////////////////////////////////////////////////
static std::random_device rand_device;
static std::default_random_engine engine(rand_device());
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
u32 random_u32() {
  std::uniform_int_distribution<u32> uni_dist;
  return uni_dist(engine);
}

const f32 random_f32(const f32 min, const f32 max) {
  std::uniform_real_distribution<f32> uni_dist(min, max);
  return uni_dist(engine);
}

const glm::vec3 random_vec3(const glm::vec3& min, const glm::vec3& max) {
  return glm::vec3(random_f32(min.x, max.x), random_f32(min.y, max.y), random_f32(min.z, max.z));
}
/////////////////////////////////////////////////////////////////////////////////
