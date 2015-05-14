#ifndef TEXTFRAME_H
#define TEXTFRAME_H

#include "libs.h"
#include "types.h"
#include "video.h"

class TextFrame {
protected:
  SDL_Rect            offset;
  int                 rows_dist;
  stringstream        buffer;
  SDL_Color           default_font_color;
  SDL_Color           bg_color;
  SDL_Color           font_color;
  bool                shade;
  SDL_Surface*        word_surface;
  string              text;
  string::iterator    text_it;
  // 단어 처리에 쓰이는 변수
  char                ch;
  string              word;
  SDL_Rect            word_offset;

public:
  TextFrame();
  TextFrame(const SDL_Rect& offset, const int& rows_dist,
            const SDL_Color& def_color, const SDL_Color& bg_color,
            const bool& shade);
  void SetOffset(const SDL_Rect& offset);
  void SetDefaultFontColor(const SDL_Color& def_color);
  void SetRowDist(const int& rows_dist);
  void SetBgColor(const SDL_Color& bg_color);
  void SetShade(const bool& shade);
  void DrawBackground();
  void Draw();
  void Clear();
  TextFrame& operator = (const string& src);
  TextFrame& operator << (const TextFrame& src);
  TextFrame& operator << (const string& src);
  TextFrame& operator << (const stringstream& src);
  TextFrame& operator << (const int& src);
  TextFrame& operator << (const char& src);
  TextFrame& operator << (const float& src);
  TextFrame& operator << (const double& src);

protected:
  // 단어 분리해 넘김
  void SplitWord();
  // 태그 처리 및 출력
  void ProcessWord();
  void ProcessJosa();
  const bool HasJongSeong(const string& str);

};

#endif // TEXTFRAME_H
