#include "selene.h"

mat4x4 world;
mat4x4 view;

void selene_init(int width, int height, Uint32 flags) {
  CORE = (Selene*) malloc(sizeof(Selene));
  CORE->_running = SELENE_TRUE;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    CORE->_running = SELENE_FALSE;
    fprintf(stderr, "Failed to init SDL...\n");
    exit (EXIT_FAILURE);
  }

  if (TTF_Init() < 0) {
    fprintf(stderr, "Failed to init TTF...\n");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  CORE->_window = selene_create_window("Selene", width, height, flags);

  if (CORE->_window == NULL) {
    CORE->_running = SELENE_FALSE;
    fprintf(stderr, "Failed to create Window...\n");
    exit (EXIT_FAILURE);
  }
  
  CORE->_context = SDL_GL_CreateContext(CORE->_window->_window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    CORE->_running = SELENE_FALSE;
    fprintf(stderr, "Failed to init GLEW...\n");
    exit (EXIT_FAILURE);
  }
  
  glViewport(0, 0, CORE->_window->_width, CORE->_window->_height);

  if ( SDL_GL_SetSwapInterval(1) < 0) {
    printf("Your hardware don't support Vsync\n");
  }

  CORE->_keyArray = SDL_GetKeyboardState(NULL);

  printf("%d\n", sizeof(CORE->_keyArray));

  CORE->_default_shader = selene_create_shader("src/shaders/basic.shader");
  CORE->_current_shader = CORE->_default_shader;

  mat4x4_identity(view);

  selene_init_primitives();

  //selene_init_texture_manager();
}

void selene_init_data() {

}

sel_bool selene_is_running() {
  return CORE->_running;
}

void selene_poll_event() {
  SDL_PollEvent(&(CORE->_event));
}

void selene_clear_screen() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void selene_swap_window() {
  SDL_GL_SwapWindow(CORE->_window->_window);
}

int selene_key_down(const char * key) {
  return CORE->_keyArray[SDL_GetScancodeFromName(key)];
}

int selene_key_up(const char * key) {
  return !(CORE->_keyArray[SDL_GetScancodeFromName(key)]);
}

void selene_use_default_shader() {

  mat4x4_ortho(world, 0.0, (float) selene_get_window_width(), (float) selene_get_window_height(), 0.0, 0.0, 1.0);

  selene_use_shader(CORE->_default_shader);

  
  selene_send_uniform(CORE->_default_shader, "world", 16, *world);

  selene_send_uniform(CORE->_default_shader, "view", 16, *view);
}

void selene_translate_camera(int x, int y) {
  mat4x4_translate(view, x, y, 0);
  //selene_send_uniform(CORE->_default_shader, "view", 16, *view);
}

void selene_scale_camera(float width, float height) {
  mat4x4_scale_aniso(view, view, width, height, 0.0f);
  //selene_send_uniform(CORE->_default_shader, "view", 16, *view);
}

void selene_terminate() {
  SDL_GL_DeleteContext(CORE->_context);
  selene_destroy_window(CORE->_window);
  //free(CORE->_keyArray);
  selene_delete_shader(CORE->_default_shader);
  selene_destroy_font(CORE->_current_font);
  free((void*)CORE);
  SDL_Quit();
}
