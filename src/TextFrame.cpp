#include "TextFrame.h"

using namespace video;

TextFrame::TextFrame() {
}

TextFrame::TextFrame(const SDL_Rect& offset, const int& rows_dist,
                     const SDL_Color& def_color, const SDL_Color& bg_color,
                     const bool& shade)
    : offset(offset),
      rows_dist(rows_dist),
      default_font_color(def_color),
      bg_color(bg_color),
      shade(shade),
      word_surface(NULL) {
}

TextFrame& TextFrame::operator = (const string& src) {
  buffer.str("");
  buffer << src;
  return *this;
}
TextFrame& TextFrame::operator << (const TextFrame& src) {
  buffer << src.buffer;
  return *this;
}
TextFrame& TextFrame::operator << (const string& src) {
  buffer << src;
  return *this;
}
TextFrame& TextFrame::operator << (const stringstream& src) {
  buffer << src;
  return *this;
}
TextFrame& TextFrame::operator << (const int& src) {
  buffer << src;
  return *this;
}
TextFrame& TextFrame::operator << (const char& src) {
  buffer << src;
  return *this;
}
TextFrame& TextFrame::operator << (const float& src) {
  buffer << src;
  return *this;
}
TextFrame& TextFrame::operator << (const double& src) {
  buffer << src;
  return *this;
}

// 단어 분리 루프. 텍스트 버퍼에서 단어를 분리해 단어 처리기로 넘김
void TextFrame::SplitWord() {
  // 스트링 버퍼에서 단어 분리
  while(text_it != text.end()) {
    // char 가져옴
    ch = *text_it++;
    // 단어의 끝인가
    if (ch == '\n' || ch == ' ' || ch == '\t' || ch == '/' || ch == '\\' || ch == '|') {
      if (!word.empty()) {
        ProcessWord();
        word.clear();
      }
      word.push_back(ch);
      ProcessWord();
      word.clear();
    } else if (ch == '<') {
      if (!word.empty()) {
        ProcessWord();
        word.clear();
      }
      word.push_back(ch);
    } else if (ch == '>') {
      word.push_back(ch);
      ProcessWord();
      word.clear();
    } else if (ch == '}') {
      word.push_back(ch);
      ProcessJosa();
      ProcessWord();
      word.clear();
    } else {
      word.push_back(ch);
    }
  }
  if (!word.empty()) {
    ProcessWord();
    word.clear();
  }
}

// 현재 단어의 길이를 조사해 문장줄에 담음. 한 줄을 넘길 경우 다음 문장줄에 저장.
void TextFrame::ProcessWord() {
  // 태그 처리
  if (word[0] == '<') {
    if (word.compare("<default>") == 0) {
      font_color = default_font_color;
      return;
    } else if (word.compare("<black>") == 0) {
      font_color = color_black;
      return;
    } else if (word.compare("<white>") == 0) {
      font_color = color_white;
      return;
    } else if (word.compare("<red>") == 0) {
      font_color = color_red;
      return;
    } else if (word.compare("<green>") == 0) {
      font_color = color_green;
      return;
    } else if (word.compare("<blue>") == 0) {
      font_color = color_blue;
      return;
    } else {
      ;
    }
  }
  if (word[0] == '\n') {
    word_offset.x = offset.x;
    word_offset.y += rows_dist;
    return;
  }
  word_surface = shade ? TTF_RenderUTF8_Shaded(font, word.c_str(), font_color, bg_color) :
                        TTF_RenderUTF8_Blended(font, word.c_str(), font_color);
  if (word_offset.x+word_surface->w >= offset.w+offset.x) {
    word_offset.x = offset.x;
    word_offset.y += rows_dist;
  }
  SDL_BlitSurface(word_surface, NULL, screen, &word_offset);
  word_offset.x += word_surface->w;
  SDL_FreeSurface(word_surface);
}

void TextFrame::Draw() {
  // 출력위치 초기화
  word_offset.x = offset.x;
  word_offset.y = offset.y;
  word_offset.w = offset.w;
  word_offset.h = offset.h;
  // 폰트 설정 초기화
  font_color = default_font_color;
  // 서페이스 초기화
  word_surface = NULL;
  // 현재 텍스트 버퍼의 내용을 처리용 스트링 버퍼에 복사
  text = buffer.str();
  text_it = text.begin();
  // 단어 분리 루프 시작 (이후 단어 처리 및 출력으로 이어짐)
  SplitWord();
  // 정리
  word.clear();
  text.clear();
}

void TextFrame::ProcessJosa() {
  auto check_it = text_it;
  for (int i = 0; i<8; ++i) {
    --check_it;
    if (check_it == text.begin())
    return;
  }

  string josa_str("가");
  auto josa_it = text_it;
  josa_it -= 2;
  josa_str[2] = *josa_it--;
  josa_str[1] = *josa_it--;
  josa_str[0] = *josa_it--;
  if (!(*josa_it == '{'))
    return;

  string check_str("가");
  check_str[0] = *check_it++;
  check_str[1] = *check_it++;
  check_str[2] = *check_it;

  auto word_it = word.end();
  word_it -= 5;
  if (josa_str.compare("은") == 0 || josa_str.compare("는") == 0) {
    if (HasJongSeong(check_str)) {
      const string sample("은");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    } else {
      const string sample("는");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    }
  } else if (josa_str.compare("이") == 0 || josa_str.compare("가") == 0) {
    if (HasJongSeong(check_str)) {
      const string sample("이");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    } else {
      const string sample("가");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    }
  } else if (josa_str.compare("을") == 0 || josa_str.compare("를") == 0) {
    if (HasJongSeong(check_str)) {
      const string sample("을");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    } else {
      const string sample("를");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    }
  } else if (josa_str.compare("와") == 0 || josa_str.compare("과") == 0) {
    if (HasJongSeong(check_str)) {
      const string sample("와");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    } else {
      const string sample("과");
      *word_it++ = sample[0];
      *word_it++ = sample[1];
      *word_it++ = sample[2];
      word.erase(word_it, word.end());
    }
  } else {
    ;
  }
}

// 받침이 있는지 검사하는 함수
const bool TextFrame::HasJongSeong(const string& str) {
  unsigned char x80 = (unsigned char)str.c_str()[0];
  if (!(234 <= x80 && x80 <= 237)) return false;
  unsigned char x81 = (unsigned char)str.c_str()[1];
  unsigned char x82 = (unsigned char)str.c_str()[2];
  unsigned char x0  = x80 - 0xE0;
  unsigned char x1  = x81 / 4 - 32;
  unsigned char x2  = (x81 % 4 * 4) + (x82 / 16 - 8);
  unsigned char x3  = x82 % 16;
  unsigned int combine = x0 * 0x1000 + x1 * 0x100 + x2 * 0x10 + x3;
  return (combine - 0xAC00) % 28;
}

void TextFrame::SetOffset(const SDL_Rect& offset) {
  this->offset = offset;
}
void TextFrame::SetDefaultFontColor(const SDL_Color& def_color) {
  this->default_font_color = def_color;
}
void TextFrame::SetRowDist(const int& rows_dist) {
  this->rows_dist = rows_dist;
}
void TextFrame::SetBgColor(const SDL_Color& bg_color) {
  this->bg_color = bg_color;
}
void TextFrame::SetShade(const bool& shade) {
  this->shade = shade;
}

void TextFrame::Clear() {
  buffer.str("");
}
void TextFrame::DrawBackground() {
  DrawBox(offset, bg_color);
}
