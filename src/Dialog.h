#ifndef DIALOG_H
#define DIALOG_H

#include "libs.h"
#include "types.h"
#include "video.h"

using namespace std;

class Dialog
{
protected:
  // 텍스트 버퍼의 전체 출력 위치 및 범위, 줄간격
  SDL_Rect offset_;
  int      rows_dist_;

  // 현재 입력된, 출력되고 남은 텍스트를 저장하는 버퍼
  string title_;
  string content_;

  // 폰트의 종류와 색, 출력방식
  SDL_Color default_font_color_;
  SDL_Color bg_color_;
  SDL_Color font_color_;

  // 자주 사용되는 서페이스 포인터들
  SDL_Surface* word_surface_;

  // 단어 분리 과정에서 아직 남아있는 처리용 스트링 버퍼
  string text_;
  string::iterator text_it_;

  // 단어 처리에 쓰이는 변수
  char ch_;
  string word_;
  SDL_Rect word_offset_;

public:
  Dialog(const SDL_Rect& offset, const int& rows_dist);
  virtual ~Dialog();

private:
  // 단어 분리해 넘김
  void SplitWord();
  // 태그 처리 및 출력
  void ProcessWord();

public:
  void set_offset(const SDL_Rect& offset);
  void set_bg_color(const SDL_Color& bg_color);
  void set_title(const string& title);
  void set_content(const string& content);
  void Draw();
  void Clear();
};

#endif // DIALOG_H

