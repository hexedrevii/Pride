#include "pride/game.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

// Hidden stuff
// That's what the anon namespace does... probably
namespace
{
  static Uint64 now, last;
  static float delta = 0;
} // namespace

void Pride::Game::create_and_run()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("ERROR: SDL: Cannot initialise SDL.");
    exit(1);
  }

  SDL_Log("INFO: SDL: Initialised SDL.");

  this->m_window = SDL_CreateWindow(this->m_title.c_str(), this->m_size.x,
                                    this->m_size.y, this->m_flags);
  if (!this->m_window)
  {
    SDL_Log("ERROR: SDL: Cannot initialise SDL Window.");
    SDL_Quit();

    exit(1);
  }

  SDL_Log("INFO: SDL: Initialised SDL Window.");

  this->m_renderer = SDL_CreateRenderer(this->m_window, nullptr);
  if (!this->m_renderer)
  {
    SDL_Log("ERROR: RENDERER: Cannot initialise basic renderer.");

    SDL_DestroyWindow(this->m_window);
    SDL_Quit();

    exit(1);
  }

  SDL_Log("INFO: RENDERER: Initialised basic renderer.");

  if (!this->drawables.create(this->m_renderer))
  {
    exit(1);
  }

  SDL_Log("INFO: DRAWABLE: Created drawable.");

  if (!this->content.load_renderer(this->m_renderer))
  {
    SDL_Log(
        "ERROR: CONTENT_LOADER: Failed to load renderer, it does not exist.");
    exit(1);
  }

  SDL_Log("INFO: CONTENT_LOADER: Created content loader.");

  last = SDL_GetPerformanceCounter();

  this->initialise();
  while (this->m_run)
  {
    // Update, calculate dt
    now = SDL_GetPerformanceCounter();
    delta = (now - last) / (float)SDL_GetPerformanceFrequency();
    last = now;

    // Handle events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
        this->m_run = false;
        break;
      }

      this->event(event);
    }

    this->process(delta);

    // Render frame
    this->render();

    // Present the current framebuffer.
    SDL_RenderPresent(this->m_renderer);
  }

  // The game is now closing.
  SDL_Log("INFO: SDL: Game is closing.");
  this->leave();

  if (this->m_renderer)
  {
    SDL_DestroyRenderer(this->m_renderer);
    SDL_Log("INFO: SDL: Destroyed render pointer.");
  }

  if (this->m_window)
  {
    SDL_DestroyWindow(this->m_window);
    SDL_Log("INFO: SDL: Destroyed window pointer.");
  }

  SDL_Log("INFO: SDL: Quitting SDL.");
  SDL_Quit();
}
