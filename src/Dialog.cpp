#include "Dialog.h"

using namespace video;

Dialog::Dialog(const SDL_Rect& offset, const int& rows_dist)
    : offset_(offset),
      rows_dist_(rows_dist),
      title_(""),
      content_(""),
      default_font_color_(color_black),
      bg_color_(color_white),
      font_color_(default_font_color_),
      word_surface_(NULL) {
}

Dialog::~Dialog() {
  if(word_surface_ != NULL) {
    SDL_free(word_surface_);
  }
}

void Dialog::set_title(const string& title) {
  title_ = title;
}

void Dialog::set_content(const string& content) {
  content_ = content;
}

// 단어 분리 루프. 텍스트 버퍼에서 단어를 분리해 단어 처리기로 넘김
void Dialog::SplitWord() {
  // 스트링 버퍼에서 단어 분리
  while(text_it_ != text_.end()) {
    // char 가져옴
    ch_ = *text_it_++;
    // 단어의 끝인가
    if (ch_ == '\n' || ch_ == ' ' || ch_ == '\t' ||
        ch_ == '/' || ch_ == '\\' || ch_ == '|') {
      if (!word_.empty()) {
        ProcessWord();
        word_.clear();
      }
      word_.push_back(ch_);
      ProcessWord();
      word_.clear();
    } else if (ch_ == '<') {
      if (!word_.empty()) {
        ProcessWord();
        word_.clear();
      }
      word_.push_back(ch_);
    } else if (ch_ == '>') {
      word_.push_back(ch_);
      ProcessWord();
      word_.clear();
    } else {
      word_.push_back(ch_);
    }
  }
  if (!word_.empty()) {
    ProcessWord();
    word_.clear();
  }
}

// 현재 단어의 길이를 조사해 문장줄에 담음. 한 줄을 넘길 경우 다음 문장줄에 저장.
void Dialog::ProcessWord() {
  // 태그 처리
  if (word_[0] == '<') {
    if (word_.compare("<default>") == 0) {
      font_color_ = default_font_color_;
      return;
    } else if (word_.compare("<black>") == 0) {
      font_color_ = color_black;
      return;
    } else if (word_.compare("<white>") == 0) {
      font_color_ = color_white;
      return;
    } else if (word_.compare("<red>") == 0) {
      font_color_ = color_red;
      return;
    } else if (word_.compare("<green>") == 0) {
      font_color_ = color_green;
      return;
    } else if (word_.compare("<blue>") == 0) {
      font_color_ = color_blue;
      return;
    } else {
      ;
    }
  }
  if (word_[0] == '\n') {
    word_offset_.x = offset_.x;
    word_offset_.y += rows_dist_;
    return;
  }
  word_surface_ = TTF_RenderUTF8_Shaded(font, word_.c_str(), font_color_, bg_color_);
  if (word_offset_.x+word_surface_->w >= offset_.w) {
    word_offset_.x = offset_.x;
    word_offset_.y += rows_dist_;
  }
  SDL_BlitSurface(word_surface_, NULL, screen, &word_offset_);
  word_offset_.x += word_surface_->w;
  SDL_FreeSurface(word_surface_);
}

void Dialog::Draw() {
  DrawBox(offset_, color_white);

  // 출력위치 초기화
  word_offset_.x = offset_.x;
  word_offset_.y = offset_.y;
  word_offset_.w = offset_.w;
  word_offset_.h = offset_.h;
  // 폰트 설정 초기화
  font_color_ = default_font_color_;
  // 서페이스 초기화
  word_surface_ = NULL;
  // 현재 텍스트 버퍼의 내용을 처리용 스트링 버퍼에 복사
  text_ = content_;
  text_it_ = text_.begin();
  // 단어 분리 루프 시작 (이후 단어 처리 및 출력으로 이어짐)
  SplitWord();

  Refresh();

  // 입력 대기
  bool is_key_pressed = false;
  SDL_Event event;
  while(!is_key_pressed) {
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym) {
      case SDLK_RETURN:
      case SDLK_KP_ENTER:
        is_key_pressed = true;
        break;

      default:
        break;
      }
    }
  }

  // 정리
  word_.clear();
  text_.clear();
}

void Dialog::set_offset(const SDL_Rect& offset) {
  offset_ = offset;
}
void Dialog::set_bg_color(const SDL_Color& bg_color) {
  bg_color_ = bg_color;
}

void Dialog::Clear() {
  title_.clear();
  content_.clear();
}
