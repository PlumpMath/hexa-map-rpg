#include "time.h"

using namespace std;

namespace rule {
const int second_in_tick    = 10;
const int round_in_tick     = second_in_tick * 6;
const int minute_in_tick    = second_in_tick * 60;
const int hour_in_tick      = second_in_tick * 3600;
const int day_in_tick       = second_in_tick * 86400;
const int month_in_tick     = second_in_tick * 2592000;
const int year_in_tick      = second_in_tick * 31104000;

const int tick_standard_act = 30;
const int tick_minor_act    = 10;
const int tick_free_act     = 0;
const int tick_move_act     = 20;
const int tick_wait_act     = 20;

const int start_year        = 1917;
const int unsigned long world_tick_start = (unsigned long int)
                                           0       * year_in_tick   +
                                           (4-1)   * month_in_tick  +
                                           (1-1)   * day_in_tick    +
                                           13      * hour_in_tick   +
                                           00      * minute_in_tick +
                                           00      * second_in_tick;
unsigned long int world_tick = world_tick_start;

int GetWorldSecond() {
  return world_tick % minute_in_tick / second_in_tick;
}
int GetWorldMinute() {
  return world_tick % hour_in_tick / minute_in_tick;
}
int GetWorldHour() {
  return world_tick % day_in_tick / hour_in_tick;
}
int GetWorldDay() {
  return world_tick % month_in_tick / day_in_tick + 1;
}
int GetWorldMonth() {
  return world_tick % year_in_tick / month_in_tick + 1;
}
int GetWorldYear() {
  return world_tick / year_in_tick + start_year;
}
string GetWorldTimeString() {
  stringstream ss;
  ss << GetWorldYear() << "년 " << GetWorldMonth() << "월 "
     << GetWorldDay() << "일 " << GetWorldHour() << "시 "
     << GetWorldMinute() << "분 " << GetWorldSecond() << "초";
  return ss.str();
}

} // namespace rule
