#include "event.h"

#include <glm/vec2.hpp>

#include <unordered_map>
#include <vector>

// Event pool
/////////////////////////////////////////////////////////////////////////////////
struct EventPool {
  std::unordered_map<EventType, std::vector<EventFunc>> pool;
};

static EventPool events;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void event_listen(const EventType type, const EventFunc func) {
  events.pool[type].push_back(func);
}

bool event_dispatch(const EventType type, const EventDesc& desc) {
  for(auto& fn : events.pool[type]) {
    if(fn(type, desc)) {
      return true;
    }
  }

  return false; 
}
/////////////////////////////////////////////////////////////////////////////////
