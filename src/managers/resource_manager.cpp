#include "managers/resource_manager.h"
#include "managers/audio_manager.h"
#include "graphics/mesh.h"

#include <miniaudio/miniaudio.h>

#include <unordered_map>
#include <cstdio>
#include <string>

// Resource manager struct
/////////////////////////////////////////////////
struct resource_manager 
{
  std::unordered_map<std::string, mesh_t*> meshes;
  std::unordered_map<std::string, ma_sound> sounds;
};

static resource_manager* rsrc_man;
/////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////
static void load_meshes()
{
  rsrc_man->meshes["Cube_Mesh"] = mesh_load();
}

static void load_fonts()
{

}

static void load_sounds()
{
  ma_engine* engine = audio_manager_get_engine();
   
  auto load = [&](const std::string& name, const std::string& path) {
    ma_sound_init_from_file(engine, path.c_str(), 0, NULL, NULL, &rsrc_man->sounds[name]);
  };

  load("Player_Death", "assets/audio/player_death.wav");
}
/////////////////////////////////////////////////

// Resource manager functions
/////////////////////////////////////////////////
void resource_manager_init()
{
  rsrc_man = new resource_manager{};

  load_meshes();
  load_fonts();
  load_sounds();
}

void resource_manager_shutdown()
{
  for(auto& [key, value] : rsrc_man->meshes)
    mesh_destroy(value);
  rsrc_man->meshes.clear();

  for(auto& [key, value] : rsrc_man->sounds)
    ma_sound_uninit(&value);
  rsrc_man->sounds.clear();

  delete rsrc_man;
}

const mesh_t* resource_get_mesh(const std::string& id)
{
  if(rsrc_man->meshes.find(id) == rsrc_man->meshes.end())
  {
    printf("ERROR: Could not find mesh of name \'%s\'\n", id.c_str());
    return nullptr;
  }

  return rsrc_man->meshes[id];
}

ma_sound& resource_get_audio(const std::string id)
{
  if(rsrc_man->sounds.find(id) == rsrc_man->sounds.end())
    printf("ERROR: Could not find sound of name \'%s\'\n", id.c_str());

  return rsrc_man->sounds[id];
}
/////////////////////////////////////////////////
