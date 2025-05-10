#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

#include <string>

#include "content_loader.h"
#include "drawable.h"
#include "vec2.h"

namespace Pride
{
  class Game
  {
  public:
    Game(std::string title, Math::Vec2 size) : m_title(title), m_size(size)
    {
    }

    Game(std::string title, int width, int height)
    {
      this->m_title = title;
      this->m_size = Math::Vec2(width, height);
    }

    /// @brief Content manager for the window.
    ContentLoader content = ContentLoader();

    /// @brief Drawing manager.
    Drawable drawables = Drawable();

    /// @brief Creates the SDL_Window pointer.
    void create_and_run();

    void set_title(std::string title)
    {
      SDL_SetWindowTitle(this->m_window, title.c_str());
    }

    /// @brief Called when an SDL_Event happens.
    virtual void event(const SDL_Event &event) {};

    /// @brief Called once after the constructor.
    virtual void initialise() = 0;

    /// @brief Called every frame before render.
    virtual void process(float delta) = 0;

    /// @brief Called every frame after process.
    virtual void render() = 0;

    /// @brief Called once when the game is closing.
    virtual void leave() {};

    void close()
    {
      this->m_run = false;
    }

    /**
     * @brief Get the internal SDL_Renderer (advanced use only).
     * @warning Avoid direct manipulation unless necessary.
     * @return Raw SDL_Renderer pointer.
     */
    SDL_Renderer *get_raw_renderer() const
    {
      return this->m_renderer;
    }

    /**
     * @brief Get the internal SDL_Window (advanced use only).
     * @warning Avoid direct manipulation unless necessary.
     * @return Raw SDL_Window pointer.
     */
    SDL_Window *get_raw_window() const
    {
      return this->m_window;
    }

  private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    bool m_run = true;

  protected:
    SDL_WindowFlags m_flags = 0;

    Math::Vec2 m_size = Math::Vec2();
    std::string m_title = "Pride Game";
  };
} // namespace Pride
