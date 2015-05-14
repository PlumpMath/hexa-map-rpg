#include "Video.h"

using namespace std;

namespace video {

int screen_width   = 1024;
int screen_height  = 768;
int screen_bpp     = 32;
bool fullscreen    = true;
bool noframe       = false;
bool videomemory   = false;

const int number_of_images = 10;

SDL_Surface* screen = NULL;
SDL_Surface* screen_backup = NULL;
TTF_Font* font = NULL;
vector<SDL_Surface*> image_surfaces = vector<SDL_Surface*>();
vector<SDL_Surface*> tileset_surfaces = vector<SDL_Surface*>();
vector<Tileset*> tilesets = vector<Tileset*>();
Uint32 video_options = 0;

SDL_Surface* LoadImage(string filename) {
  SDL_Surface* loaded_image = NULL;
  SDL_Surface* optimized_image = NULL;

  loaded_image = IMG_Load(filename.c_str());

  if (loaded_image != NULL) {
    optimized_image = SDL_DisplayFormatAlpha(loaded_image);
    SDL_FreeSurface(loaded_image);
    return optimized_image;
  } else {
    cerr << "[오류] " << filename << " 파일을 불러오지 못했습니다." << endl;
    return false;
  }
}

const bool UnloadImage(SDL_Surface* surface) {
  if (surface == NULL) {
      return false;
  } else {
    SDL_FreeSurface(surface);
    return true;
  }
}

const bool LoadVideoConfig() {
  ifstream f;
  string   config_item_key;
  cout << "Loading video config data..." << endl;
  f.open(config_video_path.c_str());
  f >> config_item_key >> screen_width;
  cout << config_item_key << " = " << screen_width << endl;
  f >> config_item_key >> screen_height;
  cout << config_item_key << " = " << screen_height << endl;
  f >> config_item_key >> screen_bpp;
  cout << config_item_key << " = " << screen_bpp << endl;
  f >> config_item_key >> fullscreen;
  cout << config_item_key << " = " << fullscreen << endl;
  f >> config_item_key >> noframe;
  cout << config_item_key << " = " << noframe << endl;
  f >> config_item_key >> videomemory;
  cout << config_item_key << " = " << videomemory << endl;
  f.close();
  // 비디오 옵션 플래그 값 만들기
  if (videomemory) {
    if (fullscreen) {
      video_options = (SDL_HWSURFACE | SDL_FULLSCREEN);
    } else {
      if (noframe) {
        video_options = (SDL_HWSURFACE | SDL_NOFRAME);
      } else {
        video_options = (SDL_HWSURFACE);
      }
    }
  } else {
    if (fullscreen) {
      video_options = (SDL_SWSURFACE | SDL_FULLSCREEN);
    } else {
      if (noframe) {
        video_options = (SDL_SWSURFACE | SDL_NOFRAME);
      } else {
      video_options = (SDL_SWSURFACE);
      }
    }
  }
  return true;
}

const bool LoadFont() {
  ifstream f;
  string   config_item_key;
  string   ttf_file;
  int      ttf_size;
  cout << "Loading font config data..." << endl;
  f.open(config_font_path.c_str());
  f >> config_item_key >> ttf_file;
  cout << config_item_key << " = " << ttf_file << endl;
  f >> config_item_key >> ttf_size;
  cout << config_item_key << " = " << ttf_size << endl;
  f.close();
  font = TTF_OpenFont(ttf_file.c_str(), ttf_size);
  return true;
}

const bool LoadImages() {
  ifstream f;
  string   config_item_key;
  string   image_path;
  cout << "Loading image config data..." << endl;
  f.open(config_image_path.c_str());
  SDL_Surface* surface = NULL;
  for (int i = 0; i<number_of_images; ++i) {
    f >> config_item_key >> image_path;
    cout << config_item_key << " = " << image_path << endl;
    image_surfaces.push_back(surface);
    image_surfaces[i] = LoadImage(image_path);
  }
  f.close();
  return true;
}

const bool LoadTilesets() {
  ifstream     f;
  string       config_item_key;
  string       image_path;
  int          tile_width;
  int          tile_height;
  int          cols;
  int          rows;
  int          cols_dist;
  int          extra_cols_dist;
  int          rows_dist;
  int          height_dist;
  int          x_modifier;
  int          y_modifier;
  SDL_Surface* surface = NULL;

  cout << "Loading tileset config data..." << endl;
  f.open(config_tileset_path.c_str());
  for (int i = 0; i<number_of_tileset_types; ++i) {
    f >> config_item_key >> image_path;
    cout << config_item_key << " = " << image_path << endl;
    f >> config_item_key >> tile_width;
    cout << config_item_key << " = " << tile_width << endl;
    f >> config_item_key >> tile_height;
    cout << config_item_key << " = " << tile_height << endl;
    f >> config_item_key >> cols;
    cout << config_item_key << " = " << cols << endl;
    f >> config_item_key >> rows;
    cout << config_item_key << " = " << rows << endl;
    f >> config_item_key >> cols_dist;
    cout << config_item_key << " = " << cols_dist << endl;
    f >> config_item_key >> extra_cols_dist;
    cout << config_item_key << " = " << extra_cols_dist << endl;
    f >> config_item_key >> rows_dist;
    cout << config_item_key << " = " << rows_dist << endl;
    f >> config_item_key >> height_dist;
    cout << config_item_key << " = " << height_dist << endl;
    f >> config_item_key >> x_modifier;
    cout << config_item_key << " = " << x_modifier << endl;
    f >> config_item_key >> y_modifier;
    cout << config_item_key << " = " << y_modifier << endl;
    surface = LoadImage(image_path);
    tileset_surfaces.push_back(surface);
    tilesets.push_back(new Tileset((TilesetType)i,
                                   tile_width, tile_height,
                                   cols, rows,
                                   cols_dist, extra_cols_dist,
                                   rows_dist, height_dist,
                                   x_modifier, y_modifier));
  }
  return true;
}

const bool InitializeVideo() {
  LoadVideoConfig();
  screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, video_options);
  if (screen == NULL) {
    cerr << "[오류] 비디오 모드 설정에 실패했습니다." << endl;
    return false;
  }
  TTF_Init();
  LoadFont();
  LoadImages();
  LoadTilesets();
  // 스크린 백업 서페이스
  screen_backup = SDL_CreateRGBSurface(SDL_SWSURFACE, screen_width, screen_height, screen_bpp, 0, 0, 0, 0);
  return true;
}

void CleanUpVideo() {
  SDL_FreeSurface(screen_backup);
  for (int i = 0; i < number_of_images; ++i) {
    UnloadImage(image_surfaces[i]);
  }
  for (int i = 0; i < number_of_tileset_types; ++i) {
    UnloadImage(tileset_surfaces[i]);
    delete tilesets[i];
  }
  TTF_CloseFont(font);
  TTF_Quit();
}

void DrawImage(SDL_Rect& rect, const int& image_id) {
  SDL_BlitSurface(image_surfaces[image_id], NULL, screen, &rect);
}

void DrawImage(const Coord& offset, const int& width, const int& height, const int& image_id) {
  SDL_Rect rect;
  rect.w = width;
  rect.h = height;
  SDL_BlitSurface(image_surfaces[image_id], NULL, screen, &rect);
}

void DrawPattern(SDL_Rect& rect, const int& image_id) {
  SDL_Rect _rect = rect;
  for(_rect.y = rect.y; _rect.y<rect.h+rect.y; _rect.y += image_surfaces[image_id]->h) {
    for(_rect.x = rect.x; _rect.x<rect.w+rect.x; _rect.x += image_surfaces[image_id]->w) {
      SDL_BlitSurface(image_surfaces[image_id], NULL, screen, &_rect);
    }
  }
}

void DrawPattern(const Coord& offset, const int& width, const int& height, const int& image_id) {
  SDL_Rect _rect;
  _rect.w = width;
  _rect.h = height;
  for(_rect.y = offset.y(); _rect.y<height+offset.y(); _rect.y += image_surfaces[image_id]->h) {
    for(_rect.x = offset.x(); _rect.x<width+offset.x(); _rect.x += image_surfaces[image_id]->w) {
      SDL_BlitSurface(image_surfaces[image_id], NULL, screen, &_rect);
    }
  }
}

void DrawBox(const SDL_Rect& rect, const SDL_Color& color) {
  SDL_Rect _rect = rect;
  Uint32 converted_color(SDL_MapRGB(screen->format, color.r, color.g, color.b));
  SDL_FillRect(screen, &_rect, converted_color);
}

void DrawBox(const Coord& offset, const int& width, const int& height, const SDL_Color& color) {
  SDL_Rect rect;
  rect.x = offset.x();
  rect.y = offset.y();
  rect.w = width;
  rect.h = height;
  Uint32 converted_color(SDL_MapRGB(screen->format, color.r, color.g, color.b));
  SDL_FillRect(screen, &rect, converted_color);
}

void DrawBorder(const SDL_Rect& rect, const int& thickness, const SDL_Color& color) {
  Uint32 converted_color(SDL_MapRGB(screen->format, color.r, color.g, color.b));
  SDL_Rect _rect;
  _rect.x = rect.x;
  _rect.y = rect.y;
  _rect.w = thickness;
  _rect.h = rect.h;
  SDL_FillRect(screen, &_rect, converted_color);
  _rect.w = rect.w;
  _rect.h = thickness;
  SDL_FillRect(screen, &_rect, converted_color);
  _rect.x = rect.x + rect.w - thickness;
  _rect.w = thickness;
  _rect.h = rect.h;
  SDL_FillRect(screen, &_rect, converted_color);
  _rect.x = rect.x;
  _rect.y = rect.y + rect.h - thickness;
  _rect.w = rect.w;
  _rect.h = thickness;
  SDL_FillRect(screen, &_rect, converted_color);
}

void DrawUTF8(const Coord& offset, const int& width,
                       const SDL_Color& bg_color, const string& text) {
  // 단어 입력 루틴
  vector<string> word_vector; // 단어 벡터
  string word;                   // 단어 버퍼
  char ch;
  auto text_it = text.begin();
  while(text_it != text.end()) {
    // char 가져옴
    ch = *text_it++;
    // 단어의 끝 :
    if (ch == '\n' || ch == ' ' || ch == '\t') {
      if (!word.empty()) {
        word_vector.push_back(word);
        word.clear();
      }
      word.push_back(ch);
      word_vector.push_back(word);
      word.clear();
    } else if (ch == '<') {
      if (!word.empty()) {
        word_vector.push_back(word);
        word.clear();
      }
      word.push_back(ch);
    } else if (ch == '>') {
      word.push_back(ch);
      word_vector.push_back(word);
      word.clear();
    }
    // 단어가 계속될 때 :
    else {
      word.push_back(ch);
    }
  }
  if (!word.empty())
    word_vector.push_back(word);

  // 단어 출력 루틴
  int marginHeight = TTF_FontHeight(font);    // 줄간격
  SDL_Color font_color = color_black;
  SDL_Surface* word_surface = NULL; // 개별 글자 렌더링 서페이스
  SDL_Rect rect;
  rect.x = offset.x();
  rect.y = offset.y();
  auto word_vector_it = word_vector.begin();
  while(word_vector_it != word_vector.end()) {
    // 태그 처리
    if ((*word_vector_it)[0] == '<') {
      if (word_vector_it->compare("<black>") == 0) {
        font_color = color_black;
        word_vector_it++;
        continue;
      } else if (word_vector_it->compare("<white>") == 0) {
        font_color = color_white;
        word_vector_it++;
        continue;
      } else if (word_vector_it->compare("<red>") == 0) {
        font_color = color_red;
        word_vector_it++;
        continue;
      } else if (word_vector_it->compare("<green>") == 0) {
        font_color = color_green;
        word_vector_it++;
        continue;
      } else if (word_vector_it->compare("<blue>") == 0) {
        font_color = color_blue;
        word_vector_it++;
        continue;
      } else {
      }
    }
    if ((*word_vector_it)[0] == '\n') {
      rect.x = offset.x();
      rect.y += marginHeight;
      word_vector_it++;
      continue;
    } else if ((*word_vector_it)[0] == ' ') {
      word_surface = TTF_RenderUTF8_Solid(font, " ", font_color);
      rect.x += word_surface->w;
      word_vector_it++;
      SDL_FreeSurface(word_surface);
      continue;
    } else {
      word_surface = TTF_RenderUTF8_Shaded(font, word_vector_it->c_str(), font_color, bg_color);
      if (rect.x >= width + offset.x()) {
        rect.x = offset.x();
        rect.y += marginHeight;
      }
      SDL_BlitSurface(word_surface, NULL, screen, &rect);
      rect.x += word_surface->w;
      word_vector_it++;
      SDL_FreeSurface(word_surface);
      continue;
    }
  }
}
void DrawGraph(SDL_Rect& rect,
               const SDL_Color& current_color, const SDL_Color& max_color,
               const int& current, const int& max) {
  DrawBox(rect, max_color);
  if (current < 0)
    return;
  DrawBox(Coord(rect.x, rect.y),
          rect.w*((double)current/(double)max),
          rect.h,
          current_color);
}

void BackUpScreen() {
  SDL_BlitSurface(screen, NULL, screen_backup, NULL);
}
void RestoreScreen() {
  SDL_BlitSurface(screen_backup, NULL, screen, NULL);
}
const bool Refresh() {
  if (SDL_Flip(screen)==-1)
    return false;
  else
    return true;
}

} // namespace video
