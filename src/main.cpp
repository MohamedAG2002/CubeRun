#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <cstdio>

struct Game {
  GLFWwindow* window = nullptr; 

  bool is_running    = true;
  float last_time    = 0.0f; 
  float delta_time   = 0.0f;
};

bool game_init(Game* game) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  game->window = glfwCreateWindow(1280, 720, "Cube Run", nullptr, nullptr);
  if(!game->window) {
    printf("[ERROR]: Failed to create GLFW window\n");
    return false; 
  } 
  else {
    glfwMakeContextCurrent(game->window);
  }

  if(!gladLoadGL(glfwGetProcAddress)) {
    printf("[ERROR]: Could not load GLAD\n");
    return false;
  } 
  else {
    glfwMakeContextCurrent(game->window);
  }

  return true;
}

void game_shutdown(Game* game) {
  glfwDestroyWindow(game->window);
  glfwTerminate();
}

void game_proccess_events(Game* game) {

}

void game_update(Game* game) {
  game->delta_time = glfwGetTime() - game->last_time;
  game->last_time  = glfwGetTime();
}

void game_render(Game* game) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 1.0f, 1.0f, 0.5f);


  glfwSwapBuffers(game->window);
}

void game_run(Game* game) {
  while(!glfwWindowShouldClose(game->window)) {
    game_proccess_events(game);
    game_update(game);
    game_render(game);

    glfwPollEvents();
  }
}

int main() {
  Game game;
  if(!game_init(&game)) {
    return -1;
  }
  
  game_run(&game);
  game_shutdown(&game);
}
