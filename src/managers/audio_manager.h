#pragma once

#include <miniaudio/miniaudio.h>

// Audio manager functions
///////////////////////////////////////////////////////
void audio_manager_init();
void audio_manager_shutdown();

ma_engine* audio_manager_get_engine();
///////////////////////////////////////////////////////
