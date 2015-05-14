#include "StringScanner.h"

using namespace std;
using namespace video;

StringScanner::StringScanner()
{
}
StringScanner::~StringScanner()
{
}

string StringScanner::CombineKorean(const int a, const int b, const int c)
{
    int combine = 0xAC00 + 21*28*a + 28*b + c;
    unsigned char x0, x1, x2, x3;
    unsigned char x80, x81, x82;
    x0 = combine / 0x1000;
    x1 = combine / 0x100 % 0x10;
    x2 = combine / 0x10 % 0x10;
    x3 = combine % 0x10;
    x80 = 0xE0 + x0;
    x81 = 0x80 + x1*4 + x2/4;
    x82 = 0x80 + x2%4*16 + x3;
    string utf8;
    utf8.push_back(x80);
    utf8.push_back(x81);
    utf8.push_back(x82);
    return utf8;
}

int StringScanner::JasoConvAC(int a)
{
    if      (a ==  0) return  1;
    else if (a ==  1) return  2;
    else if (a ==  2) return  4;
    else if (a ==  3) return  7;
    else if (a ==  5) return  8;
    else if (a ==  6) return 16;
    else if (a ==  7) return 17;
    else if (a ==  9) return 19;
    else if (a == 10) return 20;
    else if (a == 11) return 21;
    else if (a == 12) return 22;
    else if (a == 14) return 23;
    else if (a == 15) return 24;
    else if (a == 16) return 25;
    else if (a == 17) return 26;
    else if (a == 18) return 27;
    else              return  0;
}
int StringScanner::JasoConvCA(int c)
{
    if      (c ==  1) return  0;
    else if (c ==  2) return  1;
    else if (c ==  4) return  2;
    else if (c ==  7) return  3;
    else if (c ==  8) return  5;
    else if (c == 16) return  6;
    else if (c == 17) return  7;
    else if (c == 19) return  9;
    else if (c == 20) return 10;
    else if (c == 21) return 11;
    else if (c == 22) return 12;
    else if (c == 23) return 14;
    else if (c == 24) return 15;
    else if (c == 25) return 16;
    else if (c == 26) return 17;
    else if (c == 27) return 18;
    else              return  0;
}
bool StringScanner::IsCPlaceable(int a)
{
    if      (a ==  1) return false;
    else if (a ==  4) return false;
    else if (a ==  8) return false;
    else if (a == 13) return false;
    else              return true;
}
int StringScanner::CombineCA(int c, int t)
{
    if      (c ==  1 && t ==  9) return  3;  // ㄳ
    else if (c ==  4 && t == 12) return  5;  // ㄵ
    else if (c ==  4 && t == 18) return  6;  // ㄶ
    else if (c ==  8 && t ==  0) return  9;  // ㄺ
    else if (c ==  8 && t ==  6) return 10;  // ㄻ
    else if (c ==  8 && t ==  7) return 11;  // ㄼ
    else if (c ==  8 && t ==  9) return 12;  // ㄽ
    else if (c ==  8 && t == 16) return 13;  // ㄾ
    else if (c ==  8 && t == 17) return 14;  // ㄿ
    else if (c ==  8 && t == 18) return 15;  // ㅀ
    else if (c == 17 && t ==  9) return 18;  // ㅄ
    else                         return -1;
}
int StringScanner::CombineBB(int b, int t)
{
    if      (b ==  8 && t ==  0) return  9;  // ㅘ
    else if (b ==  8 && t ==  1) return 10;  // ㅙ
    else if (b ==  8 && t == 20) return 11;  // ㅚ
    else if (b == 13 && t ==  4) return 14;  // ㅝ
    else if (b == 13 && t ==  5) return 15;  // ㅞ
    else if (b == 13 && t == 20) return 16;  // ㅟ
    else if (b == 18 && t == 20) return 19;  // ㅢ
    else                         return -1;
}
void StringScanner::DivideCA(int c, int& _c, int& _t)
{
    if      (c ==  3)
    {
        _c =  1;
        _t =  9;
    }
    else if (c ==  5)
    {
        _c =  4;
        _t = 12;
    }
    else if (c ==  6)
    {
        _c =  4;
        _t = 18;
    }
    else if (c ==  9)
    {
        _c =  8;
        _t =  0;
    }
    else if (c == 10)
    {
        _c =  8;
        _t =  6;
    }
    else if (c == 11)
    {
        _c =  8;
        _t =  7;
    }
    else if (c == 12)
    {
        _c =  8;
        _t =  9;
    }
    else if (c == 13)
    {
        _c =  8;
        _t = 16;
    }
    else if (c == 14)
    {
        _c =  8;
        _t = 17;
    }
    else if (c == 15)
    {
        _c =  8;
        _t = 18;
    }
    else if (c == 18)
    {
        _c = 17;
        _t =  9;
    }
    else
    {
        ;        ;
    }
}

void StringScanner::Backspace()
{
    int at = str.length();
    if (at <= 0)
    {
        return;
    }
    else if (at <= 2)
    {
        str.erase(at-1, 1);
    }
    else
    {
        if (0xE0 <= (unsigned char)str[at-3] && (unsigned char)str[at-3] <= 0xEF)
        {
            str.erase(at-3, 3);
        }
        else
        {
            str.erase(at-1, 1);
        }
    }
}

void StringScanner::Kor2BeolCombine(const int input_type)
{
    // input_type : 0 - 자음 입력
    //              1 - 모음 입력
    //              2 - 기타 입력 (숫자 등)
    //              3 - backspace
    if (input_type == 0 && combine_level == 0)
    {
        jaso_a        = jaso_t;
        combine       = jaso;
        combine_level = 1;
    }
    else if (input_type == 0 && combine_level == 1)
    {
        str           += combine;
        jaso_a        = jaso_t;
        combine       = jaso;
        combine_level = 1;
    }
    else if (input_type == 0 && combine_level == 2)
    {
        if (IsCPlaceable(jaso_t))
        {
            jaso_c        = JasoConvAC(jaso_t);
            combine       = CombineKorean(jaso_a, jaso_b, jaso_c);
            combine_level = 4;
        }
        else
        {
            str           += combine;
            jaso_a        = jaso_t;
            combine       = jaso;
            combine_level = 1;
        }
    }
    else if (input_type == 0 && combine_level == 3)
    {
        if (IsCPlaceable(jaso_t))
        {
            jaso_c        = JasoConvAC(jaso_t);
            combine       = CombineKorean(jaso_a, jaso_b, jaso_c);
            combine_level = 4;
        }
        else
        {
            str           += combine;
            jaso_a        = jaso_t;
            combine       = jaso;
            combine_level = 1;
        }
    }
    else if (input_type == 0 && combine_level == 4)
    {
        int temp = CombineCA(jaso_c, jaso_t);
        if (temp == -1)
        {
            str           += combine;
            jaso_a        = jaso_t;
            combine       = jaso;
            combine_level = 1;
        }
        else
        {
            jaso_c        = temp;
            combine       = CombineKorean(jaso_a, jaso_b, jaso_c);
            combine_level = 5;
        }
    }
    else if (input_type == 0 && combine_level == 5)
    {
        str           += combine;
        jaso_a        = jaso_t;
        combine       = jaso;
        combine_level = 1;
    }
    else if (input_type == 0 && combine_level == 6)
    {
        str           += combine;
        jaso_a        = jaso_t;
        combine       = jaso;
        combine_level = 1;
    }
    else if (input_type == 1 && combine_level == 0)
    {
        jaso_b        = jaso_t;
        combine       = jaso;
        combine_level = 6;
    }
    else if (input_type == 1 && combine_level == 1)
    {
        jaso_b        = jaso_t;
        combine       = CombineKorean(jaso_a, jaso_b, 0);
        combine_level = 2;
    }
    else if (input_type == 1 && combine_level == 2)
    {
        int temp = CombineBB(jaso_b, jaso_t);
        if (temp == -1)
        {
            str           += combine;
            jaso_b        = jaso_t;
            combine       = jaso;
            combine_level = 6;
        }
        else
        {
            jaso_b        = temp;
            combine       = CombineKorean(jaso_a, jaso_b, 0);
            combine_level = 3;
        }
    }
    else if (input_type == 1 && combine_level == 3)
    {
        str           += combine;
        jaso_b        = jaso_t;
        combine       = jaso;
        combine_level = 6;
    }
    else if (input_type == 1 && combine_level == 4)
    {
        combine       = CombineKorean(jaso_a, jaso_b, 0);
        str           += combine;
        jaso_a        = JasoConvCA(jaso_c);
        jaso_b        = jaso_t;
        combine       = CombineKorean(jaso_a, jaso_b, 0);
        combine_level = 2;
    }
    else if (input_type == 1 && combine_level == 5)
    {
        int temp;
        DivideCA(jaso_c, jaso_c, temp);
        combine       = CombineKorean(jaso_a, jaso_b, jaso_c);
        str           += combine;
        jaso_a        = temp;
        jaso_b        = jaso_t;
        combine       = CombineKorean(jaso_a, jaso_b, 0);
        combine_level = 2;
    }
    else if (input_type == 1 && combine_level == 6)
    {
        str           += combine;
        jaso_b        = jaso_t;
        combine       = jaso;
        combine_level = 6;
    }
    else if (input_type == 2 && combine_level == 0)
    {
        str           += jaso;
        combine       = "";
        combine_level = 0;
    }
    else if (input_type == 2 && combine_level != 0)
    {
        str           += combine;
        str           += jaso;
        combine       = "";
        combine_level = 0;
    }
    else if (input_type == 3 && combine_level == 0)
    {
        Backspace();
    }
    else if (input_type == 3 && combine_level != 0)
    {
        combine       = "";
        combine_level = 0;
    }
    else
    {
        ;
    }
}

void StringScanner::Kor2BeolScanKey()
{
    switch (event.key.keysym.sym)
    {
    case SDLK_0:
        jaso = "0";
        Kor2BeolCombine(2);
        break;
    case SDLK_1:
        jaso = "1";
        Kor2BeolCombine(2);
        break;
    case SDLK_2:
        jaso = "2";
        Kor2BeolCombine(2);
        break;
    case SDLK_3:
        jaso = "3";
        Kor2BeolCombine(2);
        break;
    case SDLK_4:
        jaso = "4";
        Kor2BeolCombine(2);
        break;
    case SDLK_5:
        jaso = "5";
        Kor2BeolCombine(2);
        break;
    case SDLK_6:
        jaso = "6";
        Kor2BeolCombine(2);
        break;
    case SDLK_7:
        jaso = "7";
        Kor2BeolCombine(2);
        break;
    case SDLK_8:
        jaso = "8";
        Kor2BeolCombine(2);
        break;
    case SDLK_9:
        jaso = "9";
        Kor2BeolCombine(2);
        break;
    case SDLK_SPACE:
        jaso   = " ";
        Kor2BeolCombine(2);
        break;
    case SDLK_a:
        jaso_t = 6;
        jaso   = "ㅁ";
        Kor2BeolCombine(0);
        break;
    case SDLK_c:
        jaso_t = 14;
        jaso   = "ㅊ";
        Kor2BeolCombine(0);
        break;
    case SDLK_d:
        jaso_t = 11;
        jaso   = "ㅇ";
        Kor2BeolCombine(0);
        break;
    case SDLK_e:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 4;
            jaso   = "ㄸ";
        }
        else
        {
            jaso_t = 3;
            jaso   = "ㄷ";
        }
        Kor2BeolCombine(0);
        break;
    case SDLK_f:
        jaso_t = 5;
        jaso   = "ㄹ";
        Kor2BeolCombine(0);
        break;
    case SDLK_g:
        jaso_t = 18;
        jaso   = "ㅎ";
        Kor2BeolCombine(0);
        break;
    case SDLK_q:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 8;
            jaso   = "ㅃ";
        }
        else
        {
            jaso_t = 7;
            jaso   = "ㅂ";
        }
        Kor2BeolCombine(0);
        break;
    case SDLK_r:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 1;
            jaso   = "ㄲ";
        }
        else
        {
            jaso_t = 0;
            jaso   = "ㄱ";
        }
        Kor2BeolCombine(0);
        break;
    case SDLK_s:
        jaso_t = 2;
        jaso   = "ㄴ";
        Kor2BeolCombine(0);
        break;
    case SDLK_t:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 10;
            jaso   = "ㅆ";
        }
        else
        {
            jaso_t = 9;
            jaso   = "ㅅ";
        }
        Kor2BeolCombine(0);
        break;
    case SDLK_v:
        jaso_t = 17;
        jaso   = "ㅍ";
        Kor2BeolCombine(0);
        break;
    case SDLK_w:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 13;
            jaso   = "ㅉ";
        }
        else
        {
            jaso_t = 12;
            jaso   = "ㅈ";
        }
        Kor2BeolCombine(0);
        break;
    case SDLK_x:
        jaso_t = 16;
        jaso   = "ㅌ";
        Kor2BeolCombine(0);
        break;
    case SDLK_z:
        jaso_t = 15;
        jaso   = "ㅋ";
        Kor2BeolCombine(0);
        break;

    case SDLK_b:
        jaso_t = 17;
        jaso   = "ㅠ";
        Kor2BeolCombine(1);
        break;
    case SDLK_h:
        jaso_t = 8;
        jaso   = "ㅗ";
        Kor2BeolCombine(1);
        break;
    case SDLK_i:
        jaso_t = 2;
        jaso   = "ㅑ";
        Kor2BeolCombine(1);
        break;
    case SDLK_j:
        jaso_t = 4;
        jaso   = "ㅓ";
        Kor2BeolCombine(1);
        break;
    case SDLK_k:
        jaso_t = 0;
        jaso   = "ㅏ";
        Kor2BeolCombine(1);
        break;
    case SDLK_l:
        jaso_t = 20;
        jaso   = "ㅣ";
        Kor2BeolCombine(1);
        break;
    case SDLK_m:
        jaso_t = 18;
        jaso   = "ㅡ";
        Kor2BeolCombine(1);
        break;
    case SDLK_n:
        jaso_t = 13;
        jaso   = "ㅜ";
        Kor2BeolCombine(1);
        break;
    case SDLK_o:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 3;
            jaso   = "ㅒ";
        }
        else
        {
            jaso_t = 1;
            jaso   = "ㅐ";
        }
        Kor2BeolCombine(1);
        break;
    case SDLK_p:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            jaso_t = 7;
            jaso   = "ㅖ";
        }
        else
        {
            jaso_t = 5;
            jaso   = "ㅔ";
        }
        Kor2BeolCombine(1);
        break;
    case SDLK_u:
        jaso_t = 6;
        jaso   = "ㅕ";
        Kor2BeolCombine(1);
        break;
    case SDLK_y:
        jaso_t = 12;
        jaso   = "ㅛ";
        Kor2BeolCombine(1);
        break;
    case SDLK_BACKSPACE:
        Kor2BeolCombine(3);
        break;
    default:
        break;
    }
}

void StringScanner::EngQwertyScanKey()
{
    switch (event.key.keysym.sym)
    {
    case SDLK_0:
        str += "0";
        break;
    case SDLK_1:
        str += "1";
        break;
    case SDLK_2:
        str += "2";
        break;
    case SDLK_3:
        str += "3";
        break;
    case SDLK_4:
        str += "4";
        break;
    case SDLK_5:
        str += "5";
        break;
    case SDLK_6:
        str += "6";
        break;
    case SDLK_7:
        str += "7";
        break;
    case SDLK_8:
        str += "8";
        break;
    case SDLK_9:
        str += "9";
        break;
    case SDLK_SPACE:
        str += " ";
        break;
    case SDLK_a:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "A";
        }
        else
        {
            str += "a";
        }
        break;
    case SDLK_b:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "B";
        }
        else
        {
            str += "b";
        }
        break;
    case SDLK_c:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "C";
        }
        else
        {
            str += "c";
        }
        break;
    case SDLK_d:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "D";
        }
        else
        {
            str += "d";
        }
        break;
    case SDLK_e:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "E";
        }
        else
        {
            str += "e";
        }
        break;
    case SDLK_f:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "F";
        }
        else
        {
            str += "f";
        }
        break;
    case SDLK_g:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "G";
        }
        else
        {
            str += "g";
        }
        break;
    case SDLK_h:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "H";
        }
        else
        {
            str += "h";
        }
        break;
    case SDLK_i:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "I";
        }
        else
        {
            str += "i";
        }
        break;
    case SDLK_j:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "J";
        }
        else
        {
            str += "j";
        }
        break;
    case SDLK_k:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "K";
        }
        else
        {
            str += "k";
        }
        break;
    case SDLK_l:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "L";
        }
        else
        {
            str += "l";
        }
        break;
    case SDLK_m:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "M";
        }
        else
        {
            str += "m";
        }
        break;
    case SDLK_n:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "N";
        }
        else
        {
            str += "n";
        }
        break;
    case SDLK_o:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "O";
        }
        else
        {
            str += "o";
        }
        break;
    case SDLK_p:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "P";
        }
        else
        {
            str += "p";
        }
        break;
    case SDLK_q:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "Q";
        }
        else
        {
            str += "q";
        }
        break;
    case SDLK_r:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "R";
        }
        else
        {
            str += "r";
        }
        break;
    case SDLK_s:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "S";
        }
        else
        {
            str += "s";
        }
        break;
    case SDLK_t:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "T";
        }
        else
        {
            str += "t";
        }
        break;
    case SDLK_u:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "U";
        }
        else
        {
            str += "u";
        }
        break;
    case SDLK_v:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "V";
        }
        else
        {
            str += "v";
        }
        break;
    case SDLK_w:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "W";
        }
        else
        {
            str += "w";
        }
        break;
    case SDLK_x:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "X";
        }
        else
        {
            str += "x";
        }
        break;
    case SDLK_y:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "Y";
        }
        else
        {
            str += "y";
        }
        break;
    case SDLK_z:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "Z";
        }
        else
        {
            str += "z";
        }
        break;
    case SDLK_BACKSPACE:
        Backspace();
        break;
    default:
        break;
    }
}

string StringScanner::Scan(int lang_mode, bool is_lang_mode_changeable,
                           int max_size, TextFrame& prompt,
                           const string& notice)
{
    // lang_mode   0: English (QWERTY)
    //             1: Korean  (2-Beolsik)
    this->lang_mode               = lang_mode;
    this->is_lang_mode_changeable = is_lang_mode_changeable;

    bool complete = false;
    to_refresh    = true;
    str           = "";
    combine       = "";
    combine_level = 0;

    BackUpScreen();
    while (!complete)
    {
        while (SDL_PollEvent(&event))
        {
            if ( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                case SDLK_TAB:
                    if (this->is_lang_mode_changeable)
                    {
                        if (this->lang_mode == 1)
                        {
                            if (combine_level)
                            {
                                str += combine;
                                combine       = "";
                                combine_level = 0;
                            }
                            this->lang_mode = 0;
                        }
                        else
                        {
                            this->lang_mode = 1;
                        }
                    }
                    break;

                case SDLK_ESCAPE:
                    complete = true;
                    break;

                case SDLK_RETURN:
                    complete = true;
                    break;

                default:
                    if (this->lang_mode == 0)
                    {
                        EngQwertyScanKey();
                        to_refresh = true;
                    }
                    else if (this->lang_mode == 1)
                    {
                        Kor2BeolScanKey();
                        to_refresh = true;
                    }
                    else
                    {
                        ;
                    }
                    break;
                }
            }
        }
        if (to_refresh)
        {
            if (str.length() > max_size)
                Backspace();
            RestoreScreen();
            prompt = notice;
            prompt << str << combine;
            prompt.Draw();
            SDL_Flip(screen);
            to_refresh = false;
        }
    }
    str += combine;
    if (str.length() > max_size)
        Backspace();
    return str;
}
