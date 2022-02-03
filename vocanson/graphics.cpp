#include "graphics.hpp"

MainWindow::MainWindow() {
  this-> window = NULL; // Affichage fenêtre
  this-> renderer = NULL; // Surface fenêtre
}

MainWindow::~MainWindow() {
  SDL_DestroyRenderer(renderer); // Destruction renderer
  SDL_DestroyWindow(window); // Destruction fenêtre
}

void MainWindow::init(const char *name, int width, int height) {
  // Init window & randerer
  if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer) < 0) {
    printf("Erreur lors de la creation d'un renderer : %s\n", SDL_GetError());
    return;
  }
  SDL_SetWindowTitle(window, name);
}

SDL_Renderer *MainWindow::getRenderer() {
    return this-> renderer;
}

void rendererReset(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void printRectOnRenderer(SDL_Rect rect, SDL_Renderer* renderer, int r, int g, int b) {
  rect.x = (rect.x + 1) * TILE_SIZE -1;
  rect.y = (rect.y + 1) * TILE_SIZE -1;
  rect.w = TILE_SIZE;
  rect.h = TILE_SIZE;
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void printImgOnRenderer(const char* file, SDL_Renderer* renderer, SDL_Rect pos, int angle) {
  SDL_Surface* img = IMG_Load(file);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
  pos.x = (pos.x + 1) * TILE_SIZE -1;
  pos.y = (pos.y + 1) * TILE_SIZE -1;
  pos.w = TILE_SIZE;
  pos.h = TILE_SIZE;
  SDL_RenderCopyEx(renderer, texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
  SDL_FreeSurface(img);
  SDL_DestroyTexture(texture);
}


Playground::Playground(SDL_Renderer* newRenderer) {
  this-> renderer = newRenderer;
  eraseAndWalls();
}

Playground::~Playground() {}

void Playground::eraseAndWalls() {
  rendererReset(this-> renderer); // Clear the window
  for (int i = 0; i < GRID_WIDTH+1; i++) {
    for (int j = 0; j < GRID_HEIGHT+1; j++) {
      if ((i+j)%2 == 0) printRectOnRenderer({i, j}, this-> renderer, FIRST_FLOOR_TILE_COLOR);
      else printRectOnRenderer({i, j}, this-> renderer, SECOND_FLOOR_TILE_COLOR);
    }
  }
  SDL_SetRenderDrawColor(this-> renderer, WALL_COLOR, 255);
  for (int i = 0; i < TILE_SIZE-1; i++) {
    SDL_Rect rect = {i, i, SCREEN_WIDTH-(i+1)*2, SCREEN_HEIGHT-(i+1)*2};
    SDL_RenderDrawRect(this-> renderer, &rect);
  }
}
