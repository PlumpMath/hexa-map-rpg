#ifndef TIME_H
#define TIME_H

#include "libs.h"
#include <sstream>

using namespace std;

namespace rule {

extern const int second_in_tick;
extern const int round_in_tick;
extern const int minute_in_tick;
extern const int hour_in_tick;
extern const int day_in_tick;
extern const int month_in_tick;
extern const int year_in_tick;

extern const int tick_standard_act;
extern const int tick_minor_act;
extern const int tick_free_act;
extern const int tick_move_act;
extern const int tick_wait_act;

extern const int start_year;
extern const int unsigned long world_tick_start;
extern unsigned long int world_tick;

int GetWorldSecond();
int GetWorldMinute();
int GetWorldHour();
int GetWorldDay();
int GetWorldMonth();
int GetWorldYear();
string GetWorldTimeString();

} // namespace rule

#endif // TIME_H
