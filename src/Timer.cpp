#include "Timer.h"

Timer::Timer() {
  start_ticks= 0;
  paused_ticks= 0;
  is_started = false;
  is_paused = false;
}

Timer::~Timer() {
}

void Timer::Start() {
  is_started = true;
  is_paused = false;
  start_ticks = SDL_GetTicks();
}

void Timer::Stop() {
  is_started = false;
  is_paused = false;
}

void Timer::Pause() {
  if ((is_started) && (!is_paused)) {
    is_paused = true;
    paused_ticks = SDL_GetTicks() - start_ticks;
  }
}

void Timer::Unpause() {
  if (is_paused) {
    is_paused = false;
    start_ticks = SDL_GetTicks() - paused_ticks;
    paused_ticks = 0;
  }
}

const bool& Timer::IsStarted() const {
  return is_started;
}

const bool& Timer::IsPaused() const {
  return is_paused;
}

int Timer::GetTicks() const {
  if (is_started) {
    if (is_paused) {
      return paused_ticks;
    } else {
      return SDL_GetTicks() - start_ticks;
    }
  } else {
    return 0;
  }
}
