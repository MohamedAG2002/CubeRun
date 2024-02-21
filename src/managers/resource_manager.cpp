#include "managers/resource_manager.h"
#include "graphics/mesh.h"

#include <unordered_map>
#include <cstdio>
#include <string>

// Resource manager struct
/////////////////////////////////////////////////
struct resource_manager 
{
  std::unordered_map<std::string, mesh_t*> meshes;
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
  // Clearing and destroying meshes
  for(auto& [key, value] : rsrc_man->meshes)
    mesh_destroy(value);
  rsrc_man->meshes.clear();

  delete rsrc_man;
}

const mesh_t* resource_get_mesh(const std::string& id)
{
  if(rsrc_man->meshes.find(id) == rsrc_man->meshes.end())
  {
    printf("Could not find mesh of name \'%s\'\n", id.c_str());
    return nullptr;
  }

  return rsrc_man->meshes[id];
}
/////////////////////////////////////////////////
