#ifndef VIDEO_H
#define VIDEO_H

#include "libs.h"
#include "types.h"
#include "progopt.h"
#include "Tileset.h"
#include "Sight.h"
#include "TerrainTemplate.h"
#include "ObjectTemplate.h"

namespace video {
extern int screen_width;
extern int screen_height;
extern int screen_bpp;
extern bool fullscreen;
extern bool noframe;
extern bool videomemory;

extern SDL_Surface* screen;
extern SDL_Surface* screen_backup;
extern const int number_of_images;
extern vector<SDL_Surface*> image_surfaces;
extern vector<SDL_Surface*> tileset_surfaces;
extern vector<Tileset*> tilesets;
extern TTF_Font* font;
extern Uint32 video_options;

SDL_Surface* LoadImage(string filename);
const bool UnloadImage(SDL_Surface* surface);

const bool LoadVideoConfig();
const bool LoadFont();
const bool LoadTilesets();
const bool LoadImages();

const bool InitializeVideo();
void CleanUpVideo();

void DrawImage(SDL_Rect& rect, const int& image_id);
void DrawImage(const Coord& offset, const int& width, const int& height, const int& image_id);
void DrawPattern(SDL_Rect& rect, const int& image_id);
void DrawPattern(const Coord& offset, const int& width, const int& height, const int& image_id);
void DrawBox(const SDL_Rect& rect, const SDL_Color& color);
void DrawBox(const Coord& offset, const int& width, const int& height, const SDL_Color& color);
void DrawBorder(const SDL_Rect& rect, const int& thickness, const SDL_Color& color);
void DrawUTF8(const Coord& offset, const int& width, const SDL_Color& bg_color, const string& text);
void DrawGraph(SDL_Rect& rect, const SDL_Color& current_color, const SDL_Color& max_color, const int& current, const int& max);
void BackUpScreen();
void RestoreScreen();
const bool Refresh();
} // namespace video

#endif // VIDEO_H

