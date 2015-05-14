#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "libs.h"
#include "types.h"

// ============================================================================
// Timer 클래스 정의
// ============================================================================
class Timer {
private:
  bool is_started;
  bool is_paused;

  int start_ticks;
  int paused_ticks;

  // 인터페이스
public:
  Timer(void);
  ~Timer(void);

  void Start(void);
  void Stop(void);
  void Pause(void);
  void Unpause(void);

  const bool& IsStarted(void) const;
  const bool& IsPaused(void) const;

  int GetTicks(void) const;
};

#endif // TIMER_H_INCLUDED
