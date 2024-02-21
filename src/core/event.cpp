#include "event.h"

#include <cstdio>
#include <unordered_map>
#include <vector>

// Globals
////////////////////////////////////////////////
static std::unordered_map<event_type_e, std::vector<pfn_event_callback>> event_pool;
////////////////////////////////////////////////

// Event functions
////////////////////////////////////////////////
void event_shutdown()
{
  for(auto& [k, v] : event_pool)
    v.clear();
  event_pool.clear();
}

void event_listen(const event_type_e type, pfn_event_callback callback)
{
  event_pool[type].push_back(callback);
}

void event_dispatch(const event_type_e& type, const event_desc_t& event)
{
  for(auto& func : event_pool[type])
  {
    if(func(type, event))
      break;
    else 
      printf("ERROR: Event not handled\n");
  }
}
////////////////////////////////////////////////
