#include "audio_system.h"
#include "engine/audio/music_type.h"
#include "engine/audio/sound_type.h"
#include "engine/core/event.h"

#include <miniaudio/miniaudio.h>

#include <cstdio>
#include <string>

// AudioSystem
/////////////////////////////////////////////////////////////////////////////////
struct AudioSystem {
  ma_engine* engine;
  ma_sound sounds[SOUNDS_MAX];
  ma_sound music[MUSIC_MAX];
};

static AudioSystem audio_sys;
/////////////////////////////////////////////////////////////////////////////////

// Private functions 
/////////////////////////////////////////////////////////////////////////////////
static bool audio_event_callback(const EventType type, const EventDesc& desc) {
  if(type == EVENT_SOUND_PLAY) {
    ma_sound_start(&audio_sys.sounds[desc.sound_type]);
    return true; 
  }
  else if(type == EVENT_MUSIC_PLAY) {
    ma_sound_start(&audio_sys.music[desc.music_type]);
    return true; 
  } 
  else if(type == EVENT_MUSIC_STOP) {
    ma_sound_stop(&audio_sys.music[desc.music_type]);
    ma_sound_seek_to_pcm_frame(&audio_sys.music[desc.music_type], 0);
    return true;
  }

  return false;
}

static void load_sound(const std::string& path, const SoundType type) {
  ma_result result = ma_sound_init_from_file(audio_sys.engine, path.c_str(), 0, nullptr, nullptr, &audio_sys.sounds[type]);
  if(result != MA_SUCCESS) {
    fprintf(stderr, "[AUDIO-ERROR, ERROR-CODE = %i]: Failed to load audio at \'%s\'\n", result, path.c_str());
    return;
  }
}

static void load_music(const std::string& path, const MusicType type) {
  ma_result result = ma_sound_init_from_file(audio_sys.engine, path.c_str(), 0, nullptr, nullptr, &audio_sys.music[type]);
  if(result != MA_SUCCESS) {
    fprintf(stderr, "[AUDIO-ERROR, ERROR-CODE = %i]: Failed to load audio at \'%s\'\n", result, path.c_str());
    return;
  }
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool audio_system_init() {
  audio_sys.engine = new ma_engine{};

  ma_result result = ma_engine_init(nullptr, audio_sys.engine);
  if(result != MA_SUCCESS) {
    fprintf(stderr, "[AUDIO-ERROR, ERROR-CODE = %i]: Failed to initialize \'ma_engine\'\n", result);
    delete audio_sys.engine;

    return false;
  }

  // Listening to events 
  event_listen(EVENT_SOUND_PLAY, audio_event_callback);
  event_listen(EVENT_MUSIC_PLAY, audio_event_callback);
  event_listen(EVENT_MUSIC_STOP, audio_event_callback);
  
  // Loading sounds
  load_sound("assets/audio/player_hit.wav", SOUND_HIT);
  load_sound("assets/audio/player_hit.wav", SOUND_FALL);
  load_sound("assets/audio/player_death.wav", SOUND_DEATH);

  // Loading music 
  load_music("assets/audio/song21.mp3", MUSIC_BACKGROUND);

  return true;
}

void audio_system_shutdown() {
  ma_engine_uninit(audio_sys.engine);

  delete audio_sys.engine;
}
/////////////////////////////////////////////////////////////////////////////////
