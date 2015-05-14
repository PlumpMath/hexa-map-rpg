#ifndef STRINGSCANNER_H
#define STRINGSCANNER_H

#include "libs.h"
#include "types.h"
#include "video.h"
#include "TextFrame.h"

using namespace std;

class StringScanner {
private:
  string        str;
  string        combine;
  string        jaso;
  int           jaso_a;
  int           jaso_b;
  int           jaso_c;
  int           jaso_t;
  int           combine_level;
  SDL_Event     event;
  Uint8*        key_state;
  int           lang_mode;
  bool          is_lang_mode_changeable;
  bool          to_refresh;

  string CombineKorean(const int a, const int b, const int c);
  int JasoConvAC(int a);
  int JasoConvCA(int c);
  bool IsCPlaceable(int a);
  int CombineCA(int c, int t);
  int CombineBB(int b, int t);
  void DivideCA(int c, int& _c, int& _t);
  void Backspace();
  void Kor2BeolCombine(const int input_type);
  void Kor2BeolScanKey();
  void EngQwertyScanKey();

public:
  StringScanner();
  ~StringScanner();
  string Scan(int lang_mode, bool is_lang_mode_changeable,
              int max_size, TextFrame& prompt, const string& notice);
};

#endif // STRINGSCANNER_H

