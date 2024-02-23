#include "managers/audio_manager.h"
#include "managers/resource_manager.h"
#include "core/event.h"
#include "core/defines.h"

#include <miniaudio/miniaudio.h>

// Audio manager struct
///////////////////////////////////////////////////////
struct audio_manager_t 
{
  ma_engine* engine;
};

static audio_manager_t s_audio_man;
///////////////////////////////////////////////////////

// Callbacks
///////////////////////////////////////////////////////
b8 audio_callback(const event_type_e type, const event_desc_t& desc)
{
  if(type == EVENT_AUDIO_PLAYED)
  {
    ma_sound* sound = &resource_get_audio(desc.sound_id);
    ma_sound_start(sound);

    return true; 
  }
  if(type == EVENT_AUDIO_PAUSED)
  {
    ma_sound sound = resource_get_audio(desc.sound_id);
    ma_sound_stop(&sound);

    return true; 
  }
  else if(type == EVENT_AUDIO_STOPPED)
  {
    ma_sound sound = resource_get_audio(desc.sound_id);
    ma_sound_stop(&sound);
    ma_sound_seek_to_pcm_frame(&sound, 0);

    return true;
  }

  return false;
}
///////////////////////////////////////////////////////

// Audio manager functions
///////////////////////////////////////////////////////
void audio_manager_init()
{
  // Listen to events 
  event_listen(EVENT_AUDIO_PLAYED, audio_callback); 
  event_listen(EVENT_AUDIO_STOPPED, audio_callback); 
  event_listen(EVENT_AUDIO_PAUSED, audio_callback); 

  // Miniaudio init
  s_audio_man.engine = new ma_engine;
  ma_result result = ma_engine_init(NULL, s_audio_man.engine);
  if(result != MA_SUCCESS)
    printf("ERROR: Failed to create miniaudio\n");
}

void audio_manager_shutdown()
{
  ma_engine_uninit(s_audio_man.engine);
}

ma_engine* audio_manager_get_engine()
{
  return s_audio_man.engine;
}
///////////////////////////////////////////////////////
