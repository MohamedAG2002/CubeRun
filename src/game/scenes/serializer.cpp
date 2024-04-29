#include "serializer.h"
#include "engine/defines.h"
#include "game/entities/entity_manager.h"

#include <yaml-cpp/yaml.h>

#include <cstdio>
#include <string>
#include <fstream>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void serialize_entities(const EntityManager* entities) {
  YAML::Node node;

  // Save Player 
  ///////////////////////////////////////////////////////
  node["player"]["position"]["x"] = entities->player.position.x;
  node["player"]["position"]["y"] = entities->player.position.y;
  node["player"]["position"]["z"] = entities->player.position.z;
  
  node["player"]["scale"]["x"] = entities->player.scale.x;
  node["player"]["scale"]["y"] = entities->player.scale.y;
  node["player"]["scale"]["z"] = entities->player.scale.z;
  
  node["player"]["color"]["r"] = entities->player.color.r;
  node["player"]["color"]["g"] = entities->player.color.g;
  node["player"]["color"]["b"] = entities->player.color.b;
  node["player"]["color"]["a"] = entities->player.color.a;
  
  node["player"]["active"] = entities->player.is_active;
  node["player"]["tries"]  = entities->player.tries;
  ///////////////////////////////////////////////////////
  
  std::ofstream file("assets/scenes/game.yaml");
  if(!file.is_open()) {
    printf("[ERROR]: Open file at \'assets/scenes/game.yaml\'\n");
    return;
  }

  // Copy the contents of the YAML file into the newly opened file
  file << node;
}

void deserialize_entities(EntityManager* entities) {
  YAML::Node node = YAML::LoadFile("assets/scenes/game.yaml");

  // Load Player 
  ///////////////////////////////////////////////////////
  if(!node["player"]) {
    printf("[SERIALIZE-ERROR]: could not find a player node\n");
  } 

  entities->player.position.x = node["player"]["position"]["x"].as<f32>();
  entities->player.position.y = node["player"]["position"]["y"].as<f32>();
  entities->player.position.z = node["player"]["position"]["z"].as<f32>();
  
  entities->player.scale.x = node["player"]["scale"]["x"].as<f32>();
  entities->player.scale.y = node["player"]["scale"]["y"].as<f32>();
  entities->player.scale.z = node["player"]["scale"]["z"].as<f32>();
  
  entities->player.color.r = node["player"]["color"]["r"].as<f32>();
  entities->player.color.g = node["player"]["color"]["g"].as<f32>();
  entities->player.color.b = node["player"]["color"]["b"].as<f32>();
  entities->player.color.a = node["player"]["color"]["a"].as<f32>();
  
  entities->player.is_active = node["player"]["active"].as<bool>();
  entities->player.tries     = node["player"]["tries"].as<u32>();
  ///////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////
